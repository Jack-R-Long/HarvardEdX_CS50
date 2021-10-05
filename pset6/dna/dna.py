# Match DNA

import csv
import sys


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE.CSV SEQUENCE.TXT")
    
    # Open DNA database csv    
    people = []
    
    with open(sys.argv[1], "r") as file:  # read mode
        reader = csv.DictReader(file)
        for row in reader:
            # print(row)
            people.append(row)
    # print(people)
    
    # Open txt 
    with open(sys.argv[2], "r") as file:  # read mode
        sequence = file.read()
    
    # print(sequence)
    STRs = {}
    # Get occurences of each STR in the sequence
    for x in people[0]:
        if (x != "name"):
            repeats = find_repeats(x, sequence)
            STRs[x] = repeats

    # Check people for matches
    for person in people:
        match = True
        for key in person:
            if key != "name":
                if int(person[key]) != STRs[key]:
                    match = False
        if match:
            print(person["name"])
            return 0
    
    print("No match")
    return 1


def find_repeats(STR, sequence):
    
    # Declare vars
    str_len = len(STR)
    continous = False
    max_repeat = 0
    current_repeat = 0
    x = 0
    # Loop through every index in string, use while for customer iteration
    while x < (len(sequence) - str_len):
        substring = sequence[x:(x + str_len)]
        # print(f"STR is {STR} compared with {substring} at index {x}")
        if substring == STR:
            # iterate forward a full match
            x += str_len

            if continous:
                current_repeat += 1
            else:
                continous = True
                current_repeat = 1
            # Check for new max
            if current_repeat > max_repeat:
                max_repeat = current_repeat
        else:
            # Iterate normally and reset continous bool
            continous = False
            x += 1
    
    # print(f"Matches are {max_repeat}")
    return max_repeat
    

main()
