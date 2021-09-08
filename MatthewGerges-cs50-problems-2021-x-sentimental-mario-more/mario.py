# import the get_int function from the cs5 library
from cs50 import get_int

# prompt the user for the height of the tower
Height = get_int("Height: ")

# continue reprompting the user for the height if their input was not in a range of 1 - 8 (inclusive)
while (Height < 1 or Height > 8):
    Height = get_int("Height: ")

# the variable n allows us to create a pyramid that is small from the top and largest from the bottom
n = 1


# We created a duplicate variable of height to allow us to print spaces based on the height
# If we did not use a duplicate, while (n! = Height + 1) would always be true and would run forever
height2 = Height

while (n != Height + 1):
    # This while loop allows us to continue printing number of rows equal to the height
    
    print(" " * (height2 - 1), end="")
    # height2 - 1 because we don't want any spaces on the last row, 
    # end ="" prevents the program from putting the next print statement on a new line
    print("#" * n, end="")
    # print n number of hashtags and don't skip a line
    print("  ", end="")
    # add 2 spaces between the first and second pyramid and don't skip a new line
    print("#" * n)
    # reprint the tower (or the same number hastags on the same row as was printed before the 2 spaces)
    
    # increase n by 1 so you lay more bricks on the lower row on the next iteration
    n += 1
    
    # decrese height2 by 1 so you print less spaces on the next row
    height2 -= 1

'''
#Attempt 1 below
#didn't work because I forgot to use #* i
for i in range(0, Height):
    #print("#", end = "")
    
        
    #print(" " * Height, end = "")
    print("#" * Height)
    Height
    
'''

'''    
    for i in range(Height):
        print("#" * Height)
'''