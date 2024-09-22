import sqlite3
import os
#from scrape import scrape_single_problem

# Connect to SQLite database
db_path = os.getenv('DB_PATH', 'my_database.db')
db = sqlite3.connect(db_path)
cursor = db.cursor()

# Function to initialize the database schema
def initialize_database():
    # Create User table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS User (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        discordId BIGINT NOT NULL UNIQUE,
        username VARCHAR(255),
        privilegeLevel INTEGER DEFAULT 0
    )
    ''')
    
    # Create Problem table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS Problem (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        sourceId INTEGER NOT NULL,
        problemURL VARCHAR(255) NOT NULL UNIQUE,
        problemName VARCHAR(255) NOT NULL
    )
    ''')

    # Create KattisProblem table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS KattisProblem (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        problemId INTEGER NOT NULL,
        difficulty FLOAT NOT NULL,
        tag VARCHAR(50) NOT NULL,
        FOREIGN KEY (problemId) REFERENCES Problem(id) ON DELETE CASCADE
    )
    ''')

    # Create ProblemTag table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS ProblemTag (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        problemId INTEGER NOT NULL,
        tag VARCHAR(50) NOT NULL,
        FOREIGN KEY (problemId) REFERENCES KattisProblem(id) ON DELETE CASCADE
    )
    ''')

    # Create KattisSolution table
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS KattisSolution (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        KattisProblemId INTEGER NOT NULL,
        userId INTEGER NOT NULL,
        solutionPath VARCHAR(255) NOT NULL,
        writeUpPath VARCHAR(255) NOT NULL,
        timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (KattisProblemId) REFERENCES KattisProblem(id) ON DELETE CASCADE,
        FOREIGN KEY (userId) REFERENCES User(id) ON DELETE CASCADE
    )
    ''')

    db.commit()
    print("Database initialized successfully.")

# Utility functions for interacting with the database
def insert_solution(kattis_id, prob_id, user, sol_path, write_up_path, parsed):
    add = "INSERT INTO KattisSolution VALUES (NULL, ?, ?, ?, ?, CURRENT_TIMESTAMP)"
    cursor.execute(add, (kattis_id, user[0], sol_path, write_up_path))
    for sss in parsed[1]:
        ss = sss.strip().replace(" ", "_")
        tag = "INSERT INTO ProblemTag VALUES (NULL, ?, ?)"
        cursor.execute(tag, (prob_id, ss))
    db.commit()

def select_problem_set(above, below, problems, unsolved):
    ret = []
    while len(ret) != problems:
        ret.append(select_problem(above, below, unsolved))
    return ret

def select_problem(above, below, unsolved):
    query = "SELECT tag FROM KattisProblem WHERE difficulty >= ? AND difficulty <= ? ORDER BY RANDOM() LIMIT 1"
    cursor.execute(query, (above, below))
    tags = cursor.fetchall()
    for tag in tags:
        if (not unsolved) or get_solution(tag[0]) is None:
            return tag[0]

def get_problems_in_difficulty_range(low_range, high_range):
    query = """SELECT kp.tag, difficulty
               FROM KattisProblem kp 
               JOIN Problem p ON kp.problemId = p.id 
               WHERE difficulty >= ? AND difficulty <= ?"""
    cursor.execute(query, (low_range, high_range))
    return cursor.fetchall()

def get_problems_in_difficulty_range_with_tags(low_range, high_range, tag):
    query = """SELECT kp.tag, difficulty
               FROM KattisProblem kp 
               JOIN Problem p ON kp.problemId = p.id 
               JOIN ProblemTag t ON t.problemId = p.id 
               WHERE difficulty >= ? AND difficulty <= ? AND t.tag = ?"""
    cursor.execute(query, (low_range, high_range, tag))
    return cursor.fetchall()

def consolidate_tag(before, after):
    query = "UPDATE ProblemTag SET tag = ? WHERE tag = ?"
    cursor.execute(query, (after, before))
    rc = cursor.rowcount
    db.commit()
    return rc

def get_tags():
    query = "SELECT DISTINCT tag, COUNT(tag) FROM ProblemTag GROUP BY tag"
    cursor.execute(query)
    return cursor.fetchall()

def get_all_solved():
    query2 = """SELECT problemName, tag, difficulty, discordId, timestamp 
                FROM KattisSolution as s 
                JOIN User as u ON s.userId = u.id 
                JOIN KattisProblem as p ON s.KattisProblemId = p.id 
                JOIN Problem as pp ON p.problemId = pp.id 
                ORDER BY timestamp"""
    cursor.execute(query2)
    return cursor.fetchall()

def get_user_problems_solved(uid):
    query2 = """SELECT problemName, tag, difficulty, timestamp 
                FROM KattisSolution as s 
                JOIN User as u ON s.userId = u.id 
                JOIN KattisProblem as p ON s.KattisProblemId = p.id 
                JOIN Problem as pp ON p.problemId = pp.id 
                WHERE u.discordId = ? 
                ORDER BY timestamp"""
    cursor.execute(query2, (uid,))
    return cursor.fetchall()

def get_user_stats(uid):
    query = """SELECT SUM(difficulty), COUNT(difficulty) 
               FROM KattisSolution as s 
               JOIN User as u ON s.userId = u.id 
               JOIN KattisProblem as p ON s.KattisProblemId = p.id 
               WHERE u.discordId = ?"""
    cursor.execute(query, (uid,))
    return cursor.fetchone()

def get_problems_between_dates(y1, m1, d1, y2, m2, d2):
    date1 = f"{y1}-{m1:02d}-{d1:02d}"
    date2 = f"{y2}-{m2:02d}-{d2:02d}"
    query = """SELECT discordId, tag, difficulty, timestamp 
               FROM KattisSolution as s 
               JOIN User as u ON s.userId = u.id 
               JOIN KattisProblem as p ON s.KattisProblemId = p.id 
               WHERE timestamp > DATE(?) AND timestamp < DATE(?)"""
    cursor.execute(query, (date1, date2))
    return cursor.fetchall()

def get_easiest_unsolved():
    query = """SELECT * FROM KattisProblem as p 
               LEFT JOIN KattisSolution as s ON p.id = s.KattisProblemId 
               WHERE s.id IS NULL 
               ORDER BY difficulty LIMIT 1"""
    cursor.execute(query)
    return cursor.fetchone()

def get_user_from_author(author):
    print("DARRIN we are calling get user from author:")
    print(author.id)
    
    user = get_user(author.id)
    if user is None:
        add_user = "INSERT INTO User VALUES (NULL, ?, ?, 0)"
        cursor.execute(add_user, (author.id, author.name))  # Insert both author ID and name
        db.commit()

    return get_user(author.id)

def get_user(discordId):
    get_user = "SELECT * FROM User WHERE discordId = ?"
    cursor.execute(get_user, (discordId,))
    user = cursor.fetchall()
    if len(user) != 0:
        return user[0]
    return None

def get_kattis_problem(tag):
    query = "SELECT id, problemId FROM KattisProblem WHERE tag = ?"
    cursor.execute(query, (tag,))
    results = cursor.fetchall()
    if len(results) == 0:
        #return scrape_single_problem(tag)
        return None
    return results[0]

def get_solution(tag):
    prob = get_kattis_problem(tag)
    get = "SELECT * FROM KattisSolution WHERE KattisProblemId = ?"
    cursor.execute(get, (prob[0],))
    result = cursor.fetchone()
    return result

# Call the function to initialize the database schema
initialize_database()
