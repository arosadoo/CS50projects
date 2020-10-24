from sys import argv, exit
import csv

# Returns the max amount fo times an str is seeen consecutively in a dna sequence
def strCounter(seq, theStr):
    maxCount = 0

    for i in range(len(seq)):
        j = i
        temp = 0
        while(seq[j:len(theStr) + j] == theStr):
            j += len(theStr)
            temp += 1
        if maxCount < temp:
            maxCount = temp

    return maxCount


# Checks usage of program
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Opens str database and opens a single dna sequence
with open(argv[1]) as database:
    reader = csv.DictReader(database)
    strList = reader.fieldnames.copy()  # Always add .copy when making a copy of the list
    strList.remove('name')
    countList = dict.fromkeys(strList, 0) # Allows me to create a dictionary with only the keys 

    with open(argv[2]) as dna:
        sequence = dna.read()

        for anStr in strList:
            countList[anStr] = strCounter(sequence, anStr)
    
    # Checks if there is match with the amount of counted strs in the dna sequence
    for person in reader:
        check = False
        for counts in strList:
            if not int(person[counts]) == countList[counts]:
                check = False
                break
            else:
                check = True
        
        if check:
            print(person['name'])
            break
    if check == False:
        print("No match")