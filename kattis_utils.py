from __future__ import print_function
import argparse
import os
import re
import sys
import webbrowser
from dotenv import load_dotenv

import requests
import requests.exceptions
from selenium import webdriver
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
    #driver = webdriver.PhantomJS()
    driver = webdriver.Chrome()
    driver.get('http://open.kattis.com/login/email?')
    username = driver.find_element_by_name("user")
    username.send_keys(KATTIS_USER)
    password = driver.find_element_by_name("password")
    password.send_keys(KATTIS_PASS)
    submit = driver.find_element_by_xpath("//input[@type='submit']")
    submit.click()

    while True:
        url = "http://open.kattis.com/submissions/"+str(problemId)
        driver.get(url)
        pageText = driver.find_element_by_tag_name("body").text
        status = driver.find_element_by_class_name("status").text
        final = status_final(status)
        if final:
            driver.quit()
            return final

def status_final(stat):
    finalStatuses = ["Accepted","Compile Error", "Wrong Answer", "Time Limit Exceeded","Run Time Error", "Memory Limit Exceeded", "Output Limit Exceeded", "Judge Error"]
    for f in finalStatuses:
        if stat.startswith(f):
            return f
    return None
