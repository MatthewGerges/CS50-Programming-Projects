from cs50 import get_int
#from cs50 import get_long

# m, a, v, and j are counting variables that we use to check which type of credit card the input is
# each card has a set of 2 criteria so if m == 2, we can say the card is a mastercard

m = 0
# m is for mastercard

a = 0
# a is for amex

v = 0
# v is for visa

j = 0
# j is a variable we use to prevent the program from printing "invalid" twice

# Prompt the user to enter the credit card number
card1 = get_int("Number: ")

# get the individual numbers of the credit card using the modulus operator
# converting the modulus to an int prevents decimals (truncates them)
num1 = int(card1 % 10)
card2 = int(card1 / 10)
num2 = int(card2 % 10) 
card3 = int(card2 / 10) 
num3 = int(card3 % 10) 

card4 = int(card3 / 10) 
num4 = int(card4 % 10) 

card5 = int(card4 / 10) 
num5 = int(card5 % 10) 

card6 = int(card5 / 10) 
num6 = int(card6 % 10) 

card7 = int(card6 / 10) 
num7 = int(card7 % 10) 

card8 = int(card7 / 10) 
num8 = int(card8 % 10) 

card9 = int(card8 / 10) 
num9 = int(card9 % 10) 

card10 = int(card9 / 10) 
num10 = int(card10 % 10) 

card11 = int(card10 / 10) 
num11 = int(card11 % 10) 

card12 = int(card11 / 10) 
num12 = int(card12 % 10) 

card13 = int(card12 / 10) 
num13 = int(card13 % 10) 

card14 = int(card13 / 10) 
num14 = int(card14 % 10) 

card15 = int(card14 / 10) 
num15 = int(card15 % 10) 

card16 = int(card15 / 10) 
num16 = int(card16 % 10) 


# if the credit card is 13 digits long and starts wuth a 4 (potentially a VISA), add 1 to v
if (card1 >= 1000000000000 and card1 < 10000000000000):
    if (num13 == 4):
        v += 1
    else:
        print("INVALID")
elif (card1 < 1000000000000 or card1 >= 10000000000000000):
    print("INVALID")
    # we set j=5 so invalid does not print twice
    j = 5
    
# If the card is 15 digits and starts with 34 or 37, (potentially an Amex card) add 1 to a
elif (card1 >= 100000000000000 and card1 < 1000000000000000):
    if (num15 == 3 and num14 == 4):
        a += 1
    elif (num15 == 3 and num14 == 7):
        a += 1
    else:
        print("INVALID")

elif (card1 >= 1000000000000000 and card1 < 10000000000000000):
    # if the 16 digit credit card starts with 51,52,53,54, or 55, it could be a Mastercard number
    # add 1 to m
    if (num16 == 5 and num15 == 1):
        m += 1
    elif (num16 == 5 and num15 == 2):
        m += 1
    elif (num16 == 5 and num15 == 3):
        m += 1
    elif (num16 == 5 and num15 == 4):
        m += 1
    elif (num16 == 5 and num15 == 5):
        m += 1
    # Visa check, if the 16 digit credit card starts with 16, it could be a VISA, add 1 to v
    elif (num16 == 4):
        v += 1
    else:
        print("INVALID") 

# multiply every other digit by 2 starting with the second-to-last digit
num2 = num2 * 2 
num4 = num4 * 2 
num6 = num6 * 2 
num8 = num8 * 2 
num10 = num10 * 2 
num12 = num12 * 2 
num14 = num14 * 2 
num16 = num16 * 2 

# after multiplying by 2, if a number is equal to 10 or greater, split it into ist individual digits
# Ex. 12 becomes 1 and 2
if (num12 > 9):
    num12 = num12 % 10 + 1 
if (num14 > 9):
    num14 = num14 % 10 + 1 
if (num16 > 9):
    num16 = num16 % 10 + 1 
if (num2 > 9):
    num2 = num2 % 10 + 1
if (num4 > 9):
    num4 = num4 % 10 + 1 
if (num6 > 9):
    num6 = num6 % 10 + 1
if (num8 > 9):
    num8 = num8 % 10 + 1 
if (num10 > 9):
    num10 = num10 % 10 + 1

# add all the numbers in the credit card together- odd + individual even numbers multiplied by 2
formula = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8 + num9 + num10 + num11 + num12 + num13 + num14 + num15 + num16 

# if the cheksum formula ends with a 0, the credit card is Valid, add 1 to a, v and m
if (formula % 10 == 0):
    v += 1
    m += 1
    a += 1
elif (formula % 10 != 0 and j == 0):
    print("INVALID")
        
# tell the user which type of credit card they have based on if m, v or a is equal to 2
if (m == 2):
    print("MASTERCARD") 
if (v == 2):
    print("VISA") 
if (a == 2):
    print("AMEX")

'''
for i in range (17):
    num[i] = card[i] % 10
    card[i + 1] = card[i] / 10
'''