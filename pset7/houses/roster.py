from cs50 import SQL
from sys import argv
import csv

# Check arguments
if len(argv) != 2:
    print("Usage: python roster.py house_name")
    exit(1)

# Open database
db = SQL("sqlite:///students.db")
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house LIKE (?) ORDER BY last, first", argv[1])

# Print names and birth
for student in students:
    if student['middle'] == None:
        print(f"{student['first']} {student['last']}, born {student['birth']}")
    else:
        print(f"{student['first']} {student['middle']} {student['last']}, born {student['birth']}")