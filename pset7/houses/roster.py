from cs50 import SQL
from sys import argv, exit

#loads database
db = SQL("sqlite:///students.db")

#Checks usage program
if len(argv) != 2:
    print("Usage: python roster.py <house>")
    exit(1)
    
rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])

for row in rows:
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else: 
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
