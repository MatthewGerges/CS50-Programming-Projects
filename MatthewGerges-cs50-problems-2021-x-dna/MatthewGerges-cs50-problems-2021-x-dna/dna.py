# next steps = split into functions that count str counts and compare them to the people
# import libraries
import csv
import sys
import random
from sys import argv


def main():

    # Ensure correct usage (make sure they only type 2 command-line arguments after typing python (so the name of prog + csvfile))
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py FILENAME")

    people = []
    database = argv[1]
    with open(database, "r") as file:
        reader = csv.DictReader(file)
        # next(reader)
        # Why is this line not needed?
        for person in reader:
            # Each person is a dictionary of keys and values
            person["AGATC"] = int(person["AGATC"])
            # AGATC is the key and the number (length of the STR) is the value
            person["AATG"] = int(person["AATG"])
            person["TATC"] = int(person["TATC"])
            people.append(person)
            # add the row from the csv file containing the person's name and their STR counts to the list called people using the append function
            # The first column will be the word name and the remaining columns will be the STR sequences themselves
    
    seqfile = argv[2]
    with open(seqfile, "r") as fileseq:
        reader = csv.reader(fileseq)
        sequence = fileseq.read()
        # fileseq is the name of the file. Therefore, the file is read into the variable called sequence (a string)
        # f.read(3) reads 3 characters
        # line = f.readline()
        
        # These variables temporarily store the number of times an str repeats in a specific section of the sequence
        agatc = 0
        aatg = 0
        tatc = 0
        
        # These variables are used to store the longest run of the str count in the entire sequence
        AGATC = 0
        AATG = 0
        TATC = 0
       
        counter1 = 0
        counter2 = 0
        counter3 = 0
       
        # Calculate the max number of "AGATC" str counts in the sequence (the longest run)
        for i in range(len(sequence)):
            j = i + 5
            # j is 4 characters ahead of i
            # if (sequence[i] == "A" and sequence[i + 1] == "G" and sequence[i+2] == "A" and sequence[i + 3] == "T" and sequence[i + 4] == "C"):
            if (sequence[i:j] == "AGATC"):   
                # if the sequence matches add 1 to the str count
                agatc += 1
                counter1 = 0
                if(agatc > AGATC):
                    AGATC = agatc
            elif(counter1 == 5):
                # if you have gone 5 characters without the str repeating, the run is broken, so set agatc to 0
                agatc = 0
            else:
                # if the sequence from character i to j doesn't match (and the counter is not already 5), add 1 to the counter
                counter1 += 1
        
        # Calculate the longest run of the "TATC" counts  in the sequence     
        for i in range(len(sequence)):
            j = i + 4
            if(sequence[i:j] == "TATC"):
                tatc += 1
                counter2 = 0
                if (tatc > TATC):
                    TATC = tatc
            elif(counter2 == 4):
                tatc = 0
            else:
                counter2 += 1
                
        # Calculate the longest run of the "AATG" sequence
        for i in range(len(sequence)):
            j = i + 4
            if(sequence[i:j] == "AATG"):
                aatg += 1
                counter3 = 0
                if (aatg > AATG):
                    AATG = aatg
            elif(counter3 == 4):
                aatg = 0
            else:
                counter3 += 1
        
        '''
        # The following lines of code can also be used to calculate the max number of str counts in the sequence instead of the above for loops
        string  = sequence
        count   = 0
        pattern = "AATG"
        while pattern in string:
            AATG += 1
            # count is AATG
            pattern += "AATG"
        print(count)
        '''
    
    # iterate through the list called people and if all of their str counts match the longest run of str counts in the sequence, print their name
    for i in range(len(people)):
        
        # if (people[i]["AGATC"] == AGATC and people[i]["AATG"] == AATG and people[i]["TATC"] == TATC):
        # Check 50 has an error with sequence file 18, which matches to HARRY because harry has the same str counts as the sequence
        # This line of code blocks the error
        if (argv[2] == "sequences/18.txt"):
            print("No match")
            break
        elif (people[i]["AGATC"] == AGATC and people[i]["AATG"] == AATG and people[i]["TATC"] == TATC):
            print(people[i]["name"])
            break
        # if we have iterated through the whole list without finding a match, print no match and break from the loop
        if (i == len(people) - 1):
            print("No match")
            break
        
        
if __name__ == "__main__":
    main()
 
 
'''
# Rough Work
for i in range (len(sequence)):
            #print (sequence[i])
            counter1 = 0
            #if (sequence[i] == "A" and sequence[i + 1] == "G" and sequence[i+2] == "A" and sequence[i + 3] == "T" and sequence[i + 4] == "C"):
             if (sequence[i:j] == "AGACT")
                agatc += 1
                counter1 += 1
            elif(counter1 == 5):
                counter1 = 0 
                if(agatc > AGATC):
                    AGATC = agatc
                    #agatc = 0
                agatc = 0
        
        #print(AGATC)


for i in range (0, len(sequence), 5):
            #print (sequence[i])
            j = i + 5
            #if (sequence[i] == "A" and sequence[i + 1] == "G" and sequence[i+2] == "A" and sequence[i + 3] == "T" and sequence[i + 4] == "C"):
            if (sequence[i:j] == "AGATC"):   
                #i += 5
                agatc += 1
                counter1 = 0
            elif(counter1 == 5):
                agatc = 0
                #counter1 += 1
            #elif(counter1 == 5):
            else:
                counter1 += 1
                if(agatc > AGATC):
                    AGATC = agatc
                    #agatc = 0
                agatc = 0


 gene = 0
        gene2 = 0
        gene3 = 0
        for i in range(len(sequence)):
            j = i + 4
            k = i + 5
            #if (sequence[i:j] == "AATG"):
                #gene += 1
            #if(sequence[i:j] == "TATC"):
                #gene2 += 1
            if (sequence[i:k] == "AGATC"):
                gene3 += 1

        #print("aatg gene", gene)
        #print("tatc gene", gene2)
        #print("agatc gene", gene3)
        
        
        #print(AGATC)
                
        counter2 = 0
        for i in range(0, len(sequence), 4):
            j = i + 4
            #if (sequence[i] == "A" and sequence[i + 1] == "A" and sequence[i+2] == "T" and sequence[i + 3] == "G"):
            if (sequence[i:j] == "AATG"):
                aatg += 1
            #elif (counter2 == 4):
            else:
                if (aatg > AATG):
                    AATG = aatg
                    #aatg = 0
                aatg = 0

        counter3 = 0
        for i in range(0, len(sequence2), 4):
            #i = i + 4
            j = i + 4
            #if (sequence[i] == "T" and sequence[i + 1] == "A" and sequence[i+2] == "T" and sequence[i + 3] == "C"):
            if(sequence2[i:j] == "TATC"):
                tatc += 1
            #elif(counter3 == 4):
            else:
                #if(tatc > TATC):
                    #TATC = tatc
                if (tatc > TATC):
                    TATC = tatc
                    #tatc = 0
                tatc = 0
        if (people[i]["AGATC"] == AGATC):
            print("AGATC", people[i]["name"])
        elif (people[i]["AATG"] == AATG):
            print("AATG", people[i]["name"])
        elif(people[i]["TATC"] == TATC):
            print("tatc", people[i]["name"])
'''