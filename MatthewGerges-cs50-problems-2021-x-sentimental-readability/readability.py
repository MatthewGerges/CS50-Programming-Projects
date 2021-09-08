from cs50 import get_string
# import the get_string function from cs50's library


def main():
    # prompt the user to enter a piece of text (a paragraph/ excerpt)
    paragraph1 = get_string("Text: ")
    
    letters = count_letters(paragraph1)
    # the return value of count_letters (how many letters there are in a paragraph) is assigned to the variable letters
    
    words = count_words(paragraph1)
    # the variable words is assigned the return value of the count_words function (tells you how many words are in a paragraph)
    
    sentences = count_sentences(paragraph1)
    # the variable sentences is assigned the return value of the count_sentences function(tells you how many sentences are in a paragraph)
    
    # letters100 is automatically converted to a double in python
    letters100 = (letters * 100) / words
    
    # calculate the average number of letters and sentences per 100 words in the text

    sentences100 = (sentences * 100) / words
    
    formula = (0.0588 * letters100) - (0.296 * sentences100) - 15.8
    
    # The above is Coleman-Liau formula, whose rounded value tells you the grade-reading level of a particular text
    
    grade = round(formula)
    
    # if formula gives you a number between 1 and 16, print that number as the grade reading level
    if (grade >= 1 and grade < 16):
        print(f"Grade {grade}")
    
    # if the formula gives you a number that it is not in that range, specify if it is too low or too high of a reading level
    elif (grade < 1):
        print("Before Grade 1")
    elif (grade >= 16):
        print("Grade 16+")

# count the letters in the paragraph by checking the if the letters are alphabetical


def count_letters(paragraph):
    letters = 0
    
    for char in paragraph:
        if char.isalpha():
            # char.isalpha() returns true if a character is a letter and false otherwise
            letters += 1
    
    return letters
    
# count the words in the paragraph by adding 1 to the number of spaces


def count_words(paragraph):
    words = 1
    
    for i in range(len(paragraph)):
        if (" " == paragraph[i]):
            words += 1
    
    return words


# count the number of sentences by counting the number of punctuation marks in the paragraph (compare strings and add to a counting variable)


def count_sentences(paragraph):
    sentences = 0
    
    for i in range(len(paragraph)):
        # check for periods, exclamations, and question marks
        if (paragraph[i] == "." or paragraph[i] == "!" or paragraph[i] == "?"):
            sentences += 1
        
    return sentences


main()

'''
# This is how to iterate through each character in a string and check if it is a letter
s = 'a123b'

for char in s:
    print(char, char.isalpha())
'''