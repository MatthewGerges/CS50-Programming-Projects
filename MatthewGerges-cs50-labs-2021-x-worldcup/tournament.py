# Simulate a sports tournament

import csv
import sys
import random
from sys import argv

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage (make sure they only type 2 command-line arguments after typing python (so the name of prog + csvfile))
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # teams is a list (of world cup teams)
    # read teams into memory from file
    # open the second command line argument as the file (python does not count as an argument); "r" means open it for reading
    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team = row
            # changing the for loop to for team in reader would do the same thing and save you a line of code
            team["rating"] = int(team["rating"])
            # This converts the string rating to an integer
            # the square bracket notation allows you to access a value for a particular key inside that location
            # rating is the key and the number is the value
            teams.append(team)
            # add the row from the csv file (containg the team name and rating) to the list called teams using the append function (adds to the end of list)
    
    counts = {}
    # counts is initalized to an empty dictionary we need to populate
    
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
            # the name of he winner is the key, their number of wins is the value, using square bracket notation to access that value
            # if the winner already exists, update their win count by 1
        else:
            counts[winner] = 1
            # if the winner does not exist, create a new key and value inside that dictionary, where the name of the team (key) corresponds to a win count of 1 (value)
        
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    # winners is a list containing the names of the teams, the list is accessed via a position and not by keys
    # eventually only one team will remain in winners (champion of the tournament) and they will be located at index 0

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
            # if the first team in the pair wins, add teams[i] to the list of winners
        else:
            # if the function returns false, the first team in the function did not win, so add teams[i + 1] to the list of winners
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # teamnum = 16
    while (len(teams) != 1):
        # continue resimulating rounds until only one team is left
        winners = simulate_round(teams)
        teams = winners
        # or you could to teams = simulate_round(teams)
        # or you could recursively call the function with an if statement and include the line below
        # return simulate_tournament(teams)

    # when only one team is left, the winner can be accessed as the first position of the teams array (only one remaianing since teams = simulate_round(teams))
    winner = teams[0]["team"]
    
    # each team is a dictionary and you want to access the name of the team, ["team"] accesses the value for the team column of that csv file or the team key inside of the dictionary
    
    return (winner)
        

'''
        #for i in range (0, teamnum, 2):
        #simulate_round(teams[i], teams[i + 1])
        wonners = simulate_round(teams)
        teams = wonners
            
        teamnum = teamnum / 2
'''

if __name__ == "__main__":
    main()
    
    
'''
        Difference between list and dictionary:
        
        A list is an ordered sequence of objects, whereas dictionaries are unordered sets. 
        However, the main difference is that items in dictionaries are accessed via keys 
        and not via their position. 
        ... The values of a dictionary can be any type of Python data. 
        So, dictionaries are unordered key-value-pairs.
'''

'''
        # first attempt to add winners to counts dictionary
        
        for i in range(len(teams)):
            if (winner == teams[i]):
                champion = teams[i]
                counts[champion] += 1
                counter += 1
            elif(teams[i] != winner and counter == len(teams)):
                counts[winner] = 1
'''

# Rough work below


'''    
#teams = List[Dict[str, float]] = []
# TODO: Read teams into memory from file

    team = {}
    with open (argv[1], "r") as file:
        #should argv[1] be put in quotes
        reader = csv.DictReader(file)
        next(reader)
        #Skips the first row - deos not read the headings of the file
        for row in reader:
            #for loop that reads all the rows
            #(key, val) = row.split(',')
            #team[key] = val
            team = row[0]
            rankings = int(row[1])
            teams.append(team)
            #writer.writerow([team, score])
            #adds the team to the list (named teams) using the append function
            
            
            #teamdict = {}
            reputation[row[0]] = {'ranking':row[1]}
            
            
            #create a dictionary for each team?
            #score = set()
            #Is the above line of code really needed

    # TODO: Simulate N tournaments and keep track of win counts
    counts = {}
    with open (argv[1], "r") as file:
        keys = ['teams']
        reader = csv.DictReader(file, fieldnames = keys)
        
        #results = []
        for row in reader:
            #print(row)
            #results.append(dict(row))
            teams.append(dict(row))
            
        #return results
        return teams
'''
