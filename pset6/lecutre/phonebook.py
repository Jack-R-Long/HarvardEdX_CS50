import csv
from cs50 import get_string

with open("phonebook.csv", "a") as file :# append mode

    name = get_string("Name: ")
    number = get_string("Number: ")
    
    writer = csv.writer(file)  # writer object (can get a reader object also)
    
    writer.writerow([name, number])
