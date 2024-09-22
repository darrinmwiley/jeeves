from __future__ import print_function
import argparse
import os
import re
import sys
import webbrowser
from dotenv import load_dotenv
from scan import scan
from shutil import copyfile
from db_utils import get_kattis_problem, get_solution, get_user_from_author, insert_solution

import requests
import requests.exceptions
from selenium import webdriver
from selenium.webdriver.common.by import By
from db_utils import insert_solution
# Python 2/3 compatibility
if sys.version_info[0] >= 3:
    import configparser
else:
    # Python 2, import modules with Python 3 names
    import ConfigParser as configparser

# End Python 2/3 compatibility

load_dotenv()
KATTIS_USER = os.getenv('KATTIS_USER')
KATTIS_PASS = os.getenv('KATTIS_PASS')

_DEFAULT_CONFIG = '/usr/local/etc/kattisrc'
_LANGUAGE_GUESS = {
    '.c': 'C',
    '.c++': 'C++',
    '.cc': 'C++',
    '.c#': 'C#',
    '.cpp': 'C++',
    '.cs': 'C#',
    '.cxx': 'C++',
    '.cbl': 'COBOL',
    '.cob': 'COBOL',
    '.cpy': 'COBOL',
    '.fs': 'F#',
    '.go': 'Go',
    '.h': 'C++',
    '.hs': 'Haskell',
    '.java': 'Java',
    '.js': 'JavaScript',
    '.kt': 'Kotlin',
    '.lisp': 'Common Lisp',
    '.cl': 'Common Lisp',
    '.m': 'Objective-C',
    '.ml': 'OCaml',
    '.pas': 'Pascal',
    '.php': 'PHP',
    '.pl': 'Prolog',
    '.rb': 'Ruby',
    '.rs': 'Rust',
    '.scala': 'Scala',
}
_GUESS_MAINCLASS = {'Java', 'Scala', 'Kotlin'}
_GUESS_MAINFILE = {'Python 2', 'Python 3', 'PHP', 'JavaScript', 'Rust', 'Pascal'}

_HEADERS = {'User-Agent': 'kattis-cli-submit'}


class ConfigError(Exception):
    pass


def get_url(cfg, option, default):
    if cfg.has_option('kattis', option):
        return cfg.get('kattis', option)
    else:
        return 'https://%s/%s' % (cfg.get('kattis', 'hostname'), default)


def get_config():
    """Returns a ConfigParser object for the .kattisrc file(s)
    """
    cfg = configparser.ConfigParser()
    if os.path.exists(_DEFAULT_CONFIG):
        cfg.read(_DEFAULT_CONFIG)

    if not cfg.read('.kattisrc'):
        raise ConfigError('''\
I failed to read in a config file from your home directory or from the
same directory as this script. To download a .kattisrc file please visit
https://<kattis>/download/kattisrc
The file should look something like this:
[user]
username: yourusername
token: *********
[kattis]
hostname: <kattis>
loginurl: https://<kattis>/login
submissionurl: https://<kattis>/submit
submissionsurl: https://<kattis>/submissions''')
    return cfg


def is_python2(files):
    python2 = re.compile(r'^\s*\bprint\b *[^ \(\),\]]|\braw_input\b')
    for filename in files:
        try:
            with open(filename) as f:
                for index, line in enumerate(f):
                    if index == 0 and line.startswith('#!'):
                        if 'python2' in line:
                            return True
                        if 'python3' in line:
                            return False
                    if python2.search(line.split('#')[0]):
                        return True
        except IOError:
            return False
    return False


def guess_language(ext, files):
    if ext == ".C":
        return "C++"
    ext = ext.lower()
    if ext == ".h":
        if any(f.endswith(".c") for f in files):
            return "C"
        else:
            return "C++"
    if ext == ".py":
        if is_python2(files):
            return "Python 2"
        else:
            return "Python 3"
    return _LANGUAGE_GUESS.get(ext, None)


def guess_mainfile(language, files):
    for filename in files:
        if os.path.splitext(os.path.basename(filename))[0] in ['main', 'Main']:
            return filename
    for filename in files:
        try:
            with open(filename) as f:
                conts = f.read()
                if language in ['Java', 'Rust', 'Scala', 'Kotlin'] and re.search(r' main\s*\(', conts):
                    return filename
                if language == 'Pascal' and re.match(r'^\s*[Pp]rogram\b', conts):
                    return filename
        except IOError:
            pass
    return files[0]


def guess_mainclass(language, files):
    if language in _GUESS_MAINFILE and len(files) > 1:
        return os.path.basename(guess_mainfile(language, files))
    if language in _GUESS_MAINCLASS:
        mainfile = os.path.basename(guess_mainfile(language, files))
        name = os.path.splitext(mainfile)[0]
        if language == 'Kotlin':
            return name[0].upper() + name[1:] + 'Kt'
        return name
    return None


def login(login_url, username, password=None, token=None):
    """Log in to Kattis.
    At least one of password or token needs to be provided.
    Returns a requests.Response with cookies needed to be able to submit
    """
    login_args = {'user': username, 'script': 'true'}
    if password:
        login_args['password'] = password
    if token:
        login_args['token'] = token

    return requests.post(login_url, data=login_args, headers=_HEADERS)


def login_from_config(cfg):
    """Log in to Kattis using the access information in a kattisrc file
    Returns a requests.Response with cookies needed to be able to submit
    """
    username = cfg.get('user', 'username')
    password = token = None
    try:
        password = cfg.get('user', 'password')
    except configparser.NoOptionError:
        pass
    try:
        token = cfg.get('user', 'token')
    except configparser.NoOptionError:
        pass
    if password is None and token is None:
        raise ConfigError('''\
Your .kattisrc file appears corrupted. It must provide a token (or a
KATTIS password).
Please download a new .kattisrc file''')

    loginurl = get_url(cfg, 'loginurl', 'login')
    return login(loginurl, username, password, token)


def submit(submit_url, cookies, problem, language, files, mainclass='', tag=''):
    """Make a submission.
    The url_opener argument is an OpenerDirector object to use (as
    returned by the login() function)
    Returns the requests.Result from the submission
    """

    data = {'submit': 'true',
            'submit_ctr': 2,
            'language': language,
            'mainclass': mainclass,
            'problem': problem,
            'tag': tag,
            'script': 'true'}

    sub_files = []
    for f in files:
        with open(f) as sub_file:
            sub_files.append(('sub_file[]',
                              (os.path.basename(f),
                               sub_file.read(),
                               'application/octet-stream')))

    return requests.post(submit_url, data=data, files=sub_files, cookies=cookies, headers=_HEADERS)

def getId(submit_response, cfg):
    submissions_url = get_url(cfg, 'submissionsurl', 'submissions')

    m = re.search(r'Submission ID: (\d+)', submit_response)
    if m:
        submission_id = m.group(1)


def submit_helper(cmd):
    parser = argparse.ArgumentParser(prog='kattis', description='Submit a solution to Kattis')
    parser.add_argument('-p', '--problem',
                        help=''''Which problem to submit to.
Overrides default guess (first part of first filename)''')
    parser.add_argument('-m', '--mainclass',
                        help='''Sets mainclass.
Overrides default guess (first part of first filename)''')
    parser.add_argument('-l', '--language',
                        help='''Sets language.
Overrides default guess (based on suffix of first filename)''')
    parser.add_argument('-t', '--tag',
                        help=argparse.SUPPRESS)
    parser.add_argument('-f', '--force',
                        help='Force, no confirmation prompt before submission',
                        action='store_true')
    parser.add_argument('files', nargs='+')

    args = parser.parse_args(cmd.split())

    files = args.files

    try:
        cfg = get_config()
    except ConfigError as exc:
        print(exc)
        sys.exit(1)

    problem, ext = os.path.splitext(os.path.basename(files[0]))
    language = guess_language(ext, files)
    mainclass = guess_mainclass(language, files)
    tag = args.tag

    problem = problem.lower()

    if args.problem:
        problem = args.problem

    if args.mainclass is not None:
        mainclass = args.mainclass

    if args.language:
        language = args.language

    if language is None:
        return('''\
ERROR: No language specified, and I failed to guess language from filename extension "%s"''' % (ext,))

    files = sorted(list(set(args.files)))

    try:
        login_reply = login_from_config(cfg)
    except ConfigError as exc:
        return 'ERROR: '+ str(exc)
    except requests.exceptions.RequestException as err:
        return('ERROR: Login connection failed:', err)

    if not login_reply.status_code == 200:
        msg = "Login failed."
        if login_reply.status_code == 403:
            msg += 'Incorrect username or password/token (403)'
        elif login_reply.status_code == 404:
            msg += 'Incorrect login URL (404)'
        else:
            msg += 'Status code:', login_reply.status_code
        return 'ERROR: '+msg

    submit_url = get_url(cfg, 'submissionurl', 'submit')
    try:
        result = submit(submit_url,
                        login_reply.cookies,
                        problem,
                        language,
                        files,
                        mainclass,
                        tag)
    except requests.exceptions.RequestException as err:
        return ('ERROR: Submit connection failed:', err)

    if result.status_code != 200:
        msg = ('Submission failed.')
        if result.status_code == 403:
            msg += ('Access denied (403)')
        elif result.status_code == 404:
            msg += ('Incorrect submit URL (404)')
        else:
            msg +=('Status code:', result.status_code)
        return 'ERROR: '+msg

    plain_result = result.content.decode('utf-8').replace('<br />', '\n')
    m = re.search(r'Submission ID: (\d+)', plain_result)
    if m:
        submission_id = m.group(1)
    else:
        return "ERROR: "+plain_result
    return submission_id+" "+problem

def check_status(problemId):
    driver = webdriver.Chrome()
    
    # Open the Kattis login page
    driver.get('http://open.kattis.com/login/email?')
    
    # Find the username and password fields and enter the login credentials
    username = driver.find_element(By.NAME, "user")
    username.send_keys(KATTIS_USER)
    password = driver.find_element(By.NAME, "password")
    password.send_keys(KATTIS_PASS)
    
    # Submit the login form
    submit = driver.find_element(By.XPATH, "//input[@type='submit']")
    submit.click()

    # Poll for the problem status
    while True:
        url = "http://open.kattis.com/submissions/" + str(problemId)
        driver.get(url)
        
        # Get the page text and status
        page_text = driver.find_element(By.TAG_NAME, "body").text
        status = driver.find_element(By.CLASS_NAME, "status").text
        
        # Check if the status is final
        final = status_final(status)
        if final:
            driver.quit()  # Close the browser once the status is final
            return final

def status_final(stat):
    finalStatuses = ["Accepted","Compile Error", "Wrong Answer", "Time Limit Exceeded","Run Time Error", "Memory Limit Exceeded", "Output Limit Exceeded", "Judge Error"]
    for f in finalStatuses:
        if stat.startswith(f):
            return f
    return None

"""
#CODE I USED TO REVERSE ENGINEER THE OLD KNOWLEDGE BASE:

def get_all_submission_ids():
    print("scanning solutions")

    driver = webdriver.Chrome()

    # Open the Kattis login page
    driver.get('http://open.kattis.com/login/email?')

    # Find the username and password fields and enter the login credentials
    username = driver.find_element(By.NAME, "user")
    username.send_keys(KATTIS_USER)
    password = driver.find_element(By.NAME, "password")
    password.send_keys(KATTIS_PASS)

    # Submit the login form
    submit = driver.find_element(By.XPATH, "//input[@type='submit']")
    submit.click()

    submission_ids = []

    for i in range(10000):
        print("page ",i)
        # Navigate to the user's submissions page
        driver.get("http://open.kattis.com/users/andrew-liu2?tab=submissions&page="+str(i))

        # Find the table with ID "submissions"
        table = driver.find_element(By.ID, "submissions")

        # Find all rows (tr) with data-submission-id
        rows = table.find_elements(By.CSS_SELECTOR, "tr[data-submission-id]")

        if(len(rows) == 0):
            break

        # Loop through the rows and check the status
        for row in rows:
            # Find the td with data-type="status"
            status_td = row.find_element(By.CSS_SELECTOR, 'td[data-type="status"]')

            # Find the span within the td and check the text
            status_span = status_td.find_element(By.TAG_NAME, "span")
            if status_span.text == "Accepted":
                # Print the submission ID
                submission_id = row.get_attribute("data-submission-id")
                submission_ids.append(submission_id)
    
    for sub_id in submission_ids:
        driver.get("https://open.kattis.com/submissions/"+sub_id)
        #Locate the href in the file source content
        file_source = driver.find_element(By.CSS_SELECTOR, ".file_source-content-file")
        
        # Find the anchor tag containing the download link
        download_link = file_source.find_element(By.TAG_NAME, "a").get_attribute("href")
        
        driver.get(download_link)

    while(True):
        pass

def repopulate_knowledge_base():
    # Path to the old directory containing the solutions
    old_directory = "./kb/old"
    
    # Maintain a map of problems that have been added to the knowledge base by tag
    added_tags = set()

    # Iterate through all files in the old directory
    for fname in os.listdir(old_directory):
        print(fname)
        # Check if the file is a supported solution file
        if fname.endswith(".cpp") or fname.endswith(".py") or fname.endswith(".java"):  
            # Remove any trailing numbers in parentheses (e.g., "(1)", "(2)") from the filename
            cleaned_fname = re.sub(r' +\(\d+\)', '', fname).strip()
            print("name", cleaned_fname)
            file_path = os.path.join(old_directory, cleaned_fname)
            
            # Verify the annotation for the solution file
            annotation_issues = verify_annotation(file_path)
            if annotation_issues is None:
                # Extract prefix from the filename
                prefix = cleaned_fname.split('.')[0]

                # Skip if the problem has already been added
                if prefix in added_tags:
                    print(f"Skipping duplicate problem: {prefix}")
                    continue

                # Process the solution if annotation is valid
                annotation = scan(file_path)
                parsed = parse_annotation(annotation)

                # Mark this problem as added
                added_tags.add(prefix)

                # Create directories for storing the solution and write-up
                directory = f"kb/{prefix}"
                if not os.path.exists(directory):
                    os.makedirs(directory)

                # Save the solution file
                sol_path = f"{directory}/{cleaned_fname}"
                copyfile(file_path, sol_path)

                # Write the annotation to a text file
                write_up_path = f"{directory}/{prefix}.txt"
                with open(write_up_path, 'w') as f:
                    for line in annotation:
                        f.write(line)

                # Get the Kattis problem details
                kattis_prob = get_kattis_problem(prefix)
                if kattis_prob:
                    kattis_id = kattis_prob[0]
                    prob_id = kattis_prob[1]

                    # Insert the solution into the database
                    insert_solution(kattis_id, prob_id, [3], sol_path, write_up_path, parsed)

    print("Knowledge base repopulated successfully.")


def verify_annotation(fname):
    prefix = fname.split('.')[0]

    annotation = scan(fname)
    if len(annotation) == 0:
        return "Denied: Annotation not formatted correctly or does not exist."

    parsed = parse_annotation(annotation)

    # Validate the annotation against problem URL and tags
    if not parsed[0].lower().endswith(prefix.lower()):
        return "Denied: Annotation problem URL does not match solution name."
    if len(parsed[1]) == 0 or len(parsed[1][0]) == 0:
        return "Denied: At least one problem tag is required."
    if len(parsed[2]) < 5:
        return "Denied: Explanation was trivially short."
    if "TAGS:" not in annotation[1]:
        return "Denied: No list of tags."
    if "EXPLANATION:" not in annotation[2]:
        return "Denied: Error reading explanation."

    return None
    
def parse_annotation(annotation):
    url = annotation[0][12:].strip()
    taglist = annotation[1][5:].strip().split(",")
    taglist = [tag.strip() for tag in taglist]
    explanation = "".join(annotation[2:])
    return [url, taglist, explanation[12:]]

#repopulate_knowledge_base()
"""