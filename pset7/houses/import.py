from cs50 import SQL
from sys import argv, exit
import csv

# loads database
db = SQL("sqlite:///students.db")

# Checks usage of program
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Opens character.csv
with open(argv[1]) as characters:
    reader = csv.DictReader(characters)
    for row in reader:
        fullName = row['name'].split()
        house = row['house']
        birth = row['birth']
        if not len(fullName) == 3:
            fullName.insert(1,None)
        db.execute("INSERT INTO students (first, middle, last, house, birth)  VALUES(?, ?, ?, ?, ?)", fullName[0], fullName[1], fullName[2], house, birth)
       
            
