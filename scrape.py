from bs4 import BeautifulSoup
from dotenv import load_dotenv
import requests
import mysql.connector
import sys, traceback
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

load_dotenv()
HOST = os.getenv('DB_HOST')
USER = os.getenv('DB_USER')
PASSWD = os.getenv('DB_PASSWD')
DATABASE = os.getenv('DB_DATABASE')

db = mysql.connector.connect(
  host=HOST,
  user=USER,
  passwd=PASSWD,
  database=DATABASE
)

cursor = db.cursor(buffered=True)

#TODO ADD COLUMN FOR HIGH AND LOW DIFFICULTY VALUE AND FLAG FOR VARIABLE DIFFICULTY

def scrape_single_problem(TAG):
    url = "https://open.kattis.com/problems/"+TAG
    req = requests.get(url, headers)
    soup = BeautifulSoup(req.content, 'html.parser')

    try:
        headline = soup.find_all("div", {"class":"page-headline"})[0]
        fl = headline.find_all("div", {"class": "fl"})[0]
        h1 = fl.find_all("h1")[0]
        if h1.get_text().startswith("404"):
            return None
    except:
        wrapper = soup.find_all("div", {"class":"headline-wrapper"})[0]
        name = wrapper.find_all("h1")[0].get_text()

        first_sidebar = soup.find_all("div", {"class": "problem-sidebar"})[0]
        sidebar_info_all = first_sidebar.find_all("div", {"class":"sidebar-info"})
        sidebar_info = sidebar_info_all[len(sidebar_info_all)-1]
        difficulty_wrapper = sidebar_info.find_all("p")
        diff = difficulty_wrapper[3].find_all("span")[0].get_text()
        find_query = "select * from Problem where problemURL = \""+kattis_problem_url_prefix+TAG+"\""
        cursor.execute(find_query)
        results = cursor.fetchall()
        x = diff.split("-")[0].strip()
        if len(results) == 0:
            query = "insert into Problem Values(0, "+kattis_problem_source+", \""+kattis_problem_url_prefix+TAG+"\", \""+name+"\")"
            try:
                cursor.execute(query)
            except:
                pass
            #TODO DATABASE REFACTOR
            query = "select id from Problem where problemURL = \""+kattis_problem_url_prefix+TAG+"\""
            cursor.execute(query)
            result = cursor.fetchone()[0]
            query = "insert into KattisProblem Values(0, "+str(result)+", "+x+", \""+TAG+"\")"
            cursor.execute(query)
        get_pid = "select id from KattisProblem where tag = \""+TAG+"\""
        cursor.execute(get_pid)
        pid = cursor.fetchone()[0]
        update = "update KattisProblem set difficulty = "+x+" where id = "+str(pid)
        cursor.execute(update)
        db.commit()
        query = "select id, problemId from KattisProblem where tag = \""+TAG+"\""
        cursor.execute(query)
        return cursor.fetchone()


def scrape():
    try:
        for i in range(100000):
            print("page "+str(i))
            url = "https://open.kattis.com/problems?page="+str(i)
            req = requests.get(url, headers)
            soup = BeautifulSoup(req.content, 'html.parser')

            tables = soup.find_all("tbody")

            rows = tables[0].find_all("tr")

            if len(rows) == 0:
                break

            for row in rows:
                data = row.find_all("td")
                a = data[0].find_all("a")[0]
                href = a['href'][10:]
                name = a.get_text()
                diff = data[8].get_text()
                query = "insert into Problem Values(0, "+kattis_problem_source+", \""+kattis_problem_url_prefix+href+"\", \""+name+"\")"
                try:
                    cursor.execute(query)
                except:
                    pass
                x = diff.split("-")[0].strip()
                query = "select id from Problem where problemURL = \""+kattis_problem_url_prefix+href+"\""
                cursor.execute(query)
                result = cursor.fetchone()[0]
                query = "insert into KattisProblem Values(0, "+str(result)+", "+x+", \""+href+"\")"
                added = 0
                try:
                    cursor.execute(query)
                    added+=1
                except:
                    get_pid = "select id from KattisProblem where tag = \""+str(href)+"\""
                    cursor.execute(get_pid)
                    pid = cursor.fetchone()[0]
                    update = "update KattisProblem set difficulty = "+x+" where id = "+str(pid)
                    print(update)
                    cursor.execute(update)
        db.commit()
        return added
    except:
        traceback.print_exc()
        return -1
