#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <cs50.h>

#define MAX_NAME 256;
#define TABLE_SIZE 10;

typedef struct 
{
    char name[256];
    int age;
    //..add other stuff later
}
person;

person *hash_table[10];
//using pointers gives you flexibility when filling up the table
//makes it easy to tell when a spot is empty

//Hash table
unsigned int hash(char *name)
//want to look people up by their names so hash function is going to take a named string and map it to a location in the table (the location is an unsigned int)
{
    int length = strlen(name);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i])%10;
        //not perferct because different names map to same location = collisions
    }
    return hash_value;
}

int main()
{
    //call init function
    printf("Jacob => %u\n", hash("Jacob"));
    printf("Matt => %u\n", hash("Matt"));
    printf("Shel => %u\n", hash("Shel"));
    printf("Rachel => %u\n", hash("Rachel"));
    printf("Me => %u\n", hash("Me"));

    return 0;
}

//function will set up table
void setup()
{
    for (int i = 0; i < 10; i++)
    {
        hash_table[i] = NULL
    }
    //table is empty
}

void p