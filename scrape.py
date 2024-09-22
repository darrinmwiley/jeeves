from bs4 import BeautifulSoup
from dotenv import load_dotenv
import requests
import sqlite3
import sys
import traceback
import os

headers = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Methods': 'GET',
    'Access-Control-Allow-Headers': 'Content-Type',
    'Access-Control-Max-Age': '3600',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0'
}

kattis_problem_source = "1"
kattis_problem_url_prefix = "open.kattis.com/problems/"

# Load environment variables
load_dotenv()
DB_PATH = os.getenv('DB_PATH', 'my_database.db')

# Connect to SQLite database
db = sqlite3.connect(DB_PATH)
cursor = db.cursor()

# TODO: Add column for high and low difficulty value and flag for variable difficulty
def scrape_single_problem(TAG):
    url = "https://open.kattis.com/problems/" + TAG
    req = requests.get(url, headers=headers)
    soup = BeautifulSoup(req.content, 'html.parser')

    try:
        # Handle 404 page
        headline = soup.find_all("div", {"class": "page-headline"})[0]
        fl = headline.find_all("div", {"class": "fl"})[0]
        h1 = fl.find_all("h1")[0]
        if h1.get_text().startswith("404"):
            return None
    except:
        # Scraping logic for problem metadata
        wrapper = soup.find_all("div", {"class": "headline-wrapper"})[0]
        name = wrapper.find_all("h1")[0].get_text()

        first_sidebar = soup.find_all("div", {"class": "problem-sidebar"})[0]
        sidebar_info_all = first_sidebar.find_all("div", {"class": "sidebar-info"})
        sidebar_info = sidebar_info_all[len(sidebar_info_all)-1]
        difficulty_wrapper = sidebar_info.find_all("p")
        diff = difficulty_wrapper[3].find_all("span")[0].get_text()

        find_query = "SELECT * FROM Problem WHERE problemURL = ?"
        cursor.execute(find_query, (kattis_problem_url_prefix + TAG,))
        results = cursor.fetchall()

        x = diff.split("-")[0].strip()

        if len(results) == 0:
            query = "INSERT INTO Problem (sourceId, problemURL, problemName) VALUES (?, ?, ?)"
            try:
                cursor.execute(query, (kattis_problem_source, kattis_problem_url_prefix + TAG, name))
            except sqlite3.IntegrityError:
                pass

            query = "SELECT id FROM Problem WHERE problemURL = ?"
            cursor.execute(query, (kattis_problem_url_prefix + TAG,))
            result = cursor.fetchone()[0]

            query = "INSERT INTO KattisProblem (problemId, difficulty, tag) VALUES (?, ?, ?)"
            cursor.execute(query, (result, x, TAG))

        get_pid = "SELECT id FROM KattisProblem WHERE tag = ?"
        cursor.execute(get_pid, (TAG,))
        pid = cursor.fetchone()[0]

        update = "UPDATE KattisProblem SET difficulty = ? WHERE id = ?"
        cursor.execute(update, (x, pid))

        db.commit()

        query = "SELECT id, problemId FROM KattisProblem WHERE tag = ?"
        cursor.execute(query, (TAG,))
        return cursor.fetchone()

def scrape():
    added = 0
    try:
        for i in range(100000):
            print(f"Page {i}")
            url = f"https://open.kattis.com/problems?page={i}"
            req = requests.get(url, headers=headers)
            soup = BeautifulSoup(req.content, 'html.parser')

            section = soup.find("section", {"data-cy": "problems-table"})
            tables = section.find_all("tbody")

            if len(tables) == 0:
                break

            rows = tables[0].find_all("tr")

            for row in rows:
                data = row.find_all("td")
                a = data[0].find_all("a")[0]
                href = a['href'][10:]  # Get problem tag from URL
                name = a.get_text()
                diff = data[6].find("span").get_text()

                query = "INSERT INTO Problem (sourceId, problemURL, problemName) VALUES (?, ?, ?)"
                try:
                    cursor.execute(query, (kattis_problem_source, kattis_problem_url_prefix + href, name))
                except sqlite3.IntegrityError:
                    #print("integrity error")
                    pass

                spl = diff.split("-")
                x = spl[len(spl) - 1]

                print(name, spl, x)

                query = "SELECT id FROM Problem WHERE problemURL = ?"
                cursor.execute(query, (kattis_problem_url_prefix + href,))
                result = cursor.fetchone()[0]

                query = "INSERT INTO KattisProblem (problemId, difficulty, tag) VALUES (?, ?, ?)"
                try:
                    cursor.execute(query, (result, x, href))
                    added += 1
                except sqlite3.IntegrityError:
                    get_pid = "SELECT id FROM KattisProblem WHERE tag = ?"
                    cursor.execute(get_pid, (href,))
                    pid = cursor.fetchone()[0]
                    update = "UPDATE KattisProblem SET difficulty = ? WHERE id = ?"
                    cursor.execute(update, (x, pid))

            # Commit after each page
            db.commit()

        return added

    except Exception as e:
        traceback.print_exc()
        return -1

# Close the database connection when done
def close_db():
    cursor.close()
    db.close()

#scrape()