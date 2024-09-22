import sqlite3
import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()

# Path to the SQLite database file from the environment or default
DB_PATH = os.getenv('DB_PATH', 'my_database.db')

# Function to execute any SQL query and return results
def execute_sql():
    # Connect to the database
    db = sqlite3.connect(DB_PATH)
    cursor = db.cursor()

    try:
        # Loop to continuously accept SQL queries from the user
        while True:
            sql_query = input("Enter an SQL statement (or type 'exit' to quit): ")

            if sql_query.lower() == 'exit':
                print("Exiting...")
                break

            try:
                # Execute the SQL query
                cursor.execute(sql_query)
                
                # If the query returns results (like SELECT)
                if sql_query.strip().upper().startswith("SELECT"):
                    rows = cursor.fetchall()
                    if rows:
                        for row in rows:
                            print(row)
                    else:
                        print("No results.")
                
                # If the query modifies data (like INSERT, UPDATE, DELETE)
                else:
                    db.commit()
                    print(f"Query executed successfully. {cursor.rowcount} rows affected.")

            except sqlite3.Error as e:
                # Handle SQL errors
                print(f"An error occurred: {e}")

    except KeyboardInterrupt:
        # Handle Ctrl+C for exiting
        print("\nExiting...")
    
    finally:
        # Close the database connection when done
        cursor.close()
        db.close()

if __name__ == "__main__":
    execute_sql()
