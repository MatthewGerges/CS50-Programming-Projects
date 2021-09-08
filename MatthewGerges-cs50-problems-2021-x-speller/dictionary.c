// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in one of the linked lists in the hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
    //self-referential - can't use node* next because the program doesn't know what node is yet (declared on lower line)
}
node;


// Number of buckets in hash table
const unsigned int N = 10000;
//increasing the number of "buckets" you have significantly decreases your running time by bringing it closer to O(n) - constant time so long as you have enough memory
//10,000 and 100,000 buckets gives you the same running time of 0.08 seconds- you may have very well reached an asypmtote for efficiency of your hash function

// Hash table
node *table[N];
//Every index in the hash table is a row (from array) and each row contains a linked list
//so table[4] - goes to the 5th row

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    
    //Method 1: hash the word whose spelling you are checking- the hash value tells you which row the similar words were placed
    //You then go to that row and iterate over every word to check if any of them are the same - same = correct spelling, diff = incorrect
    unsigned int index = hash(word);
    //access the linked list at that hash value; hash the word to determine the row
    node *cursor = table[index];
    //the cursor is made equal to the bucket / row at which similar words are found
    //Don't need to malloc it because it only exists in the scope? Don't all of them exist in the scope? The table already exist and all the words have already been copied
    //You're only using the cursor to check not store anything so no need for malloc
    while (cursor != NULL)
    {
        if ((strcasecmp(word, cursor->word)) == 0)
        {
            return true;
        }    
        cursor = cursor -> next;    
    }
    
    /*
    //This is an alternative way to check if the word is in the dictionary. This section of the code iterates over every row (index of the array in the hash table) and every word in the column of the dictionary/ text file? of the 
    //This method results in a significantly higher running time because you have to check all the rows
    for (int i = 0; i < N; i++)
    {
        //node *cursor = malloc(sizeof(node));
        node *cursor = table[i];
        while (cursor != NULL)
        {
            if ((strcasecmp(word, cursor->word)) == 0)
            {
                return true;
            }
            cursor = cursor -> next;
        }
    }
    */
        
    /*
    //The following code is not to be used in this function because it inserts nodes instead of searching them (would need to use malloc)
    //set new pointer
    cursor -> next = table[i];
    //set head to new pointer
    table[i] = cursor;
    //n = table[i];
    //is n the head of the linked list at index i?
    }
    */
    return false;
}

// Hashes word to a number (a bucket)
unsigned int hash(const char *word)
{
    //for (int i = 0; i < strlen(word); i++)
    /*
        Method 1 - organize all the word in A - Z buckets - alphabetic order based on first bucket
        int askii = word[0];
        int bucket;
        if (askii > 96 && askii < 123)
        {
            bucket = askii - 96;
        }
        if (askii > 64 && askii < 91)
        {
            bucket = askii - 64;
        }
        
    return bucket % N;
    //run time of 8.38 seconds
    */
    //Method 2 - 0.33 seconds run time whith 100 buckets - Adds all the ascii values of the letters in the word
    
    int total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int ascii = tolower(word[i]);
        //you might want to to lower (word[i])
        //without tolower- runtime of 2.68 seconds
        //with tolower = 1.58 seconds
        total = total + ascii;
        
    }
    
    return total % N;
    //find the remainder of the total divided by the number of buckets to determine which bucket the new node should go into
    
    /*
    //Supposed to be faster than the above but has a run time of 0.70 seconds not 0.30 seconds like the previous
    int hash = 401;

    while (*word != '\0') {
        hash = ((hash << 4) + (int)(*word)) % N;
        word++;
    }

    return hash % N;
    //Explanation for the above:
    //401 is a seed value: lowers the number of collisions that will occur (due to the fact that 401 is a prime number)
    //hash << 4 shifts binary values 4 digits to the left. This is a very fast way to multiply by 16
    //+(int)(*word) adds the int value of the next char to the running total 
    //+int*word returns more misspelled words because it doesn't deal with case sensitivity
    //return hash % N makes sure your words fit into the buckets
    */
    
}
unsigned int wordnumber = 0;
//This is already a global variable, no need to make it a pointer, check what this does in a separate program; could you use a pointer though?

// This function loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) 
{
    FILE *input = fopen(dictionary, "r"); 
    //open the dictionary for reading
    if (input == NULL)
    {
        return false;
    }
        
    char WORD [LENGTH + 1];
    //Length + 1 for the null \0 character
    
    while ((fscanf(input, "%s", WORD)) != EOF)
        //n -> word??? - no you don't know what that s yet
        //Fscanf accepts input according to a format string that you provide. For instance, it is capable of stuffing decimal numbers in a file into floats or doubles. Fread doesn't do that sort of processing and simply reads of block of bytes.
        //fscan f reads a formatted data type from a file pointer (input), and what it reads is WORD - and its size which is [Length + 1]
    {
        wordnumber++;
        //Every time we scan a word, add 1 to the word count so we know the size of dictionary later on
        //create a new node for each word by using malloc
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n -> word, WORD);
        //put WORD into n -> word 
        //Why are we doing this - We are doing this so that when we compare words from other txt file, we can check if a word in a hast table matches
        //strcpy takes as its first argument the destination of a copy and the 2nd argument = source from which to copy
        
        
        //insert node into hash table
        //hash word by using hash functiion - which takes a string and returns a index
        unsigned int index = hash(WORD);
        //You don't need usigned int part
        //you can also hash n -> word
            
        //Once you've determined which linked list you should use, the next step is to actually insert that word into the linked list.

        //node *tmp = n -> next;
        //It works without the if statements if you just keep the else
        if (table[index] == NULL)
        {
            //if no word is presently in the hash table at that index, insert n at that index
            table[index] = n;
            //You do not know what the node's next variable is so set it to NULL - good practice
            n -> next = NULL;
            //works without the above line
        }
        else 
        {
            //if the hash table already has a value at that index, set the next pointer of the new node you want to insert to point to the head
            //This avoids orphaning the rest of the nodes (Order matters - cannot set head of the list equal to n then set next pointer (do reverse)
            n -> next = table[index];
            //set the head of the list equal to the new node
            table[index] = n;
        }

            
            
        //Why do we not use free? freing n just frees 1 word + you want to use the dynamically allocated memory so you'll have to free it in a separate function
        //free(n);


    }
    fclose(input);
    //close the dictionary
    
    return true;
    //If the function has gotten this far, everything was able to load, so return true
        
    
   
    
}

unsigned int size(void)
{
    // TODO
    //Method 1: iterate over every linked list, count the number of nodes inside in each of the linked lists, or while loading hash table, count the number of words you addded so far so you can return the value in your size function
    //Somehow this method does not increase the runtime
    int wordnum = 0;
    for (int i = 0; i < N; i++)
    { 
        node *cursor = table[i];
        while (cursor != NULL)
        {
            wordnum++;
            cursor = cursor -> next;
        }
    }
    return wordnum;
    
    /*
    if (wordnumber != 0)
    //if the dictionary has loaded (we don't pass this value in!)
    {
        return wordnumber;
    }

    return 0;
    */
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //free up the memory and return true if able to do so
    //hash table is array of linked lists - each linked lists contains nodes that you've allocated memory for using malloc
    //iterate over hash table, go over each linked list and call free on all of the nodes inside of those linked lists
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        //node *tmp = cursor;
        //should I put this in the while loop? Yes because if it was not, it would just always point to the head, you wanna move them 1 step at a time, wherein tmp follows the cursor
        //then free tmp pointer 
        while (cursor != NULL)
        {
            //free(cursor);
            //The above line would orphan all the nodes
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
            //if i == N-1, you're done iterating over all the rows in the hash table
        {
            //if cursor is null, you're done freeing up all of the memory that was originally allocated for these nodes
            return true;
        }
    }
    
    //how to free all the nodes of the linked list
    //if you free cursor and cursor points to the first node in the list you're orphaning the whole list
    //create a temporary variable called temp which is going to be equal to cursor
    return false;
}

/*
Summary of Process:
1) Load: Open the dictionary, we used fscanf and strcpy along with malloc to copy each word in the dictionary into a node. Then we called the hash function to determine where each node would be placed in the table, then we placed the word in that row of the table
2) Size: Determine the number of words in the dictionary (just for counting words purposes)
3) Hash function: Determine how to arrange the words hashed in the load function within buckets; use modulus operator
4) Check Function: Determine if the word in a txt file opened (written in a diff library) matches a word in a dictionary - iterate through row or through everything (slower)
5) Unload = frees all dynamically allocated memory (by iterating through everything and freeing each word)
*/