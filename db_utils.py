import os
from dotenv import load_dotenv
import mysql.connector

from scrape import scrape_single_problem

load_dotenv()
HOST = os.getenv('DB_HOST')
USER = os.getenv('DB_USER')
PASSWD = os.getenv('DB_PASSWD')
DATABASE = os.getenv('DB_DATABASE')
NO_DB = os.getenv('NO_DB')
if(NO_DB != 'TRUE'):
    print(NO_DB)
    db = mysql.connector.connect(
        host=HOST,
        user=USER,
        passwd=PASSWD,
        database=DATABASE
    )
    cursor = db.cursor(buffered=True)

def insert_solution(kattis_id, prob_id, user, sol_path,write_up_path, parsed):
    add = "insert into KattisSolution VALUES(0, "+str(kattis_id)+", "+str(user[0])+", \""+sol_path+"\", \""+write_up_path+"\", current_timestamp())"
    cursor.execute(add)
    for sss in parsed[1]:
        ss = sss.strip().replace(" ", "_")
        tag = "insert into ProblemTag VALUES(0, "+str(prob_id)+", \""+ss+"\")"
        cursor.execute(tag)
    db.commit()

def select_problem_set(above, below, problems, unsolved):
    ret = []
    while len(ret) != problems:
        ret.append(select_problem(above, below, unsolved))
    return ret

def select_problem(above, below, unsolved):
    query = "SELECT tag from KattisProblem WHERE difficulty >= "+str(above)+" AND difficulty <= "+str(below)+" ORDER BY RAND()"
    cursor.execute(query)
    tags = cursor.fetchall()
    for tag in tags:
        if (not unsolved) or get_solution(tag[0]) is None:
            return tag[0]



def get_problems_in_difficulty_range(low_range, high_range):
    query = "SELECT kp.tag, difficulty FROM KattisProblem kp JOIN Problem p ON kp.problemId = p.id WHERE difficulty >= "+str(low_range)+" AND difficulty <= "+str(high_range)
    cursor.execute(query)
    return cursor.fetchall()

def get_problems_in_difficulty_range_with_tags(low_range, high_range, tag):
    query = query = "SELECT kp.tag, difficulty FROM KattisProblem kp JOIN Problem p ON kp.problemId = p.id JOIN ProblemTag t ON t.problemId = p.id WHERE difficulty >= "+str(low_range)+" AND difficulty <= "+str(high_range)+" AND t.tag = \""+tag+"\""
    cursor.execute(query)
    return cursor.fetchall()

def consolidate_tag(before, after):
    query = "update ProblemTag set tag = \""+after+"\" where tag = \""+before+"\""
    cursor.execute(query)
    rc = cursor.rowcount
    db.commit()
    return rc

def get_tags():
    query = "select distinct tag, count(tag) from ProblemTag group by tag";
    cursor.execute(query)
    return cursor.fetchall()

def get_all_solved():
    query2 = "select problemName, tag, difficulty, discordId, timestamp from KattisSolution as s join User as u on s.userId = u.id join KattisProblem as p on s.KattisProblemId = p.id join Problem as pp on p.problemId = pp.id order by timestamp"
    cursor.execute(query2)
    return cursor.fetchall()

def get_user_problems_solved(uid):
    query2 = "select problemName, tag, difficulty, timestamp from KattisSolution as s join User as u on s.userId = u.id join KattisProblem as p on s.KattisProblemId = p.id join Problem as pp on p.problemId = pp.id where u.discordId = \""+str(uid)+"\" order by timestamp"
    cursor.execute(query2)
    return cursor.fetchall()

def get_user_stats(uid):
    query = "select sum(difficulty), count(difficulty) from KattisSolution as s join User as u on s.userId = u.id join KattisProblem as p on s.KattisProblemId = p.id where u.discordId = \""+str(uid)+"\""
    cursor.execute(query)
    return cursor.fetchone()

def get_problems_between_dates(y1, m1, d1, y2, m2, d2):
    date1 = str(y1)+"-"+str(m1)+"-"+str(d1)
    date2 = str(y2)+"-"+str(m2)+"-"+str(d2)
    query = "select discordId, tag, difficulty, timestamp from KattisSolution as s join User as u on s.userId = u.id join KattisProblem as p on s.KattisProblemId = p.id where timestamp > date(\""+date1+"\") and timestamp < date(\""+date2+"\");"
    cursor.execute(query)
    return cursor.fetchall();

def get_easiest_unsolved():
    query = "select * from KattisProblem as p left join KattisSolution as s on p.id = s.kattisProblemId where s.id is null order by difficulty limit 1"
    cursor.execute(query)
    return cursor.fetchone()

def get_user_from_author(author):
    user = get_user(author.id)
    if user is None:
        add_user = "INSERT INTO User values (0, "+str(author.id)+", null, 0)"
        cursor.execute(add_user)
        db.commit()
    return get_user(author.id)

def get_user(discordId):
    get_user = "SELECT * FROM User where discordId = '"+str(discordId)+"'"
    cursor.execute(get_user)
    user = cursor.fetchall()
    if len(user) != 0:
        return user[0]
    return None

def get_kattis_problem(tag):
    query = "select id, problemId from KattisProblem where tag = \""+tag+"\""
    cursor.execute(query)
    results = cursor.fetchall()
    if len(results) == 0:
        return scrape_single_problem(tag)
    return results[0]

def get_solution(tag):
    prob = get_kattis_problem(tag)
    get = "select * from KattisSolution WHERE KattisProblemId = "+str(prob[0])
    cursor.execute(get)
    result = cursor.fetchone()
    return result
