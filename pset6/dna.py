from sys import argv
import csv

# Check arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Ready to save people's data
people = []

# Open the CSV file and read its contents into memory
with open(argv[1], 'r') as database:
    DNAreader = csv.DictReader(database)
    header = DNAreader.fieldnames
    for row in DNAreader:
        people.append(row)

# Open the DNA sequence and readits conetents into memory
with open(argv[2]) as sequence:
    seq = sequence.read().replace('\n', '')

# Ready to save STRs counts and wait for matching with people
DNAtoMatch = []

# For each STRs, compute the longest run of consecutive repeats in the sequence(Seq)
for STRs in header[1:]:  # header[0] is "name"
    # setting up
    n = len(seq)-len(STRs)-len(STRs)
    count = 0
    temp = 0

    for i in range(n):
        j = i + len(STRs)
        if STRs == seq[i:j]:
            temp += 1
            for k in range(round((len(seq)-i)/len(STRs))):  # Max number of squences repeated, can skipped this line since we have "break"
                # since every STR is consecutive, so their "distance" is fixed (i.e. multiply of len(STRs))
                start = len(STRs) * k
                end = len(STRs) * (k+1)
                if seq[i+start:j+start] == seq[i+end:j+end]:
                    temp += 1
                else:
                    break
            if temp > count:
                count = temp
            temp = 0
    DNAtoMatch.append(str(count))

# Search for individuals's STRs counts match with DNAtoMatch
for i in range(len(people)):
    peopleDNA = []
    for key, value in people[i].items():
        peopleDNA.append(value)
    if peopleDNA[1:] == DNAtoMatch:
        print(peopleDNA[0])
        exit(0)

# If not found
print("No match")
exit(1)