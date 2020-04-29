from cs50 import SQL
from sys import argv
import csv

# Check arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Open database
db = SQL("sqlite:///students.db")

# Open characters.csv file and read its data
with open(argv[1], 'r') as students:
    reader = csv.DictReader(students)

    # Read students' data
    for row in reader:
        name = row["name"].split()
        house = row["house"]
        birth = row["birth"]
        if len(name) == 3:
            # INSERT to the table
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", 
            		   name[0], name[1], name[2], house, birth)
        else:
            # INSERT to the table
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", 
            		   name[0], None, name[1], house, birth)


