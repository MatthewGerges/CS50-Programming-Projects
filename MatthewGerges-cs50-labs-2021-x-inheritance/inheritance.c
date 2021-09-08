// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
//The following is a linked list 
typedef struct person
{
    //this is a pointer that stores the address of the next element in the linked list
    struct person *parents[2];
    //this part of the struct stores the actual data itself
    char alleles[2];
}
person;

//constant integers = integers that are fixed and cannot change
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

//function prototypes/ declarations 
//person* create family means that the create family function should return!!! a data type of type person
person *create_family(int generations);
//This function does not have a return type but has t2o inputs: *p of data type person and generation of data type int
void print_family(person *p, int generation);
//free family frees the dynamically allocated memory from heap (originally allocated using malloc)
void free_family(person *p);
//This function will generate a random allele - A, B, or O for each person in the family
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations by calling upon the create family function
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person (based on the how many bytes the data type person takes up)
    person *m = malloc(sizeof(person));
    //Does not matter what this letter is it could be *p
    
    //Handle base case, (if malloc cannot find enough memory to allocate memory for the variable m) return NULL and exit the function
    if (m == NULL)
    {
        return NULL;
        //we have to return NULL and not 0 or 1 or true or false because the function's return type is a pointer so returning NULL makes sense
    }

    // Generation with parent data
    //if there;s more than 1 generation then create random alleles for the parents
    //Then create alleles for the parent's parents' using recursion
    //no need to check if null because we are creating family history based on number of generations
    if (generations > 1)
    {
        

        for (int i = 0; i < 2; i++)
        {
            //TODO: Recursively create blood type histories for parents
            m-> parents[i] = create_family(generations - 1);
           
            // TODO: Randomly assign child alleles based on parents
            m ->alleles[i] = m ->parents[i] ->alleles[rand() % 2];
            //rand()%2 creates a random integer between 0 and 1 since each parent has 2 alleles and each child will take from one of the parent's alleles - their allele 0 or 1

        }
        /*
        This is how the code looks without the for loop:
        
        // TODO: Recursively create blood type histories for parents
        m-> parents [0] = create_family(generations - 1);
        m -> parents [1] = create_family(generations - 1);
        
        // TODO: Randomly assign child alleles based on parents
        m -> alleles[0] = m -> parents[0] -> alleles[rand()%2];
        //rand()%2 creates a random integer between 0 and 1 since each parent has 2 alleles and each child will take from one of the parent's alleles - their allele 0 or 1
        m -> alleles[1] = m -> parents[1] -> alleles[rand()%2];
        */
    }

    // Generation without parent data (function has been recursively called to the point that generations is equal to 1, meaning we have reached the grandparents who have no parent history)
    else
    {
        // TODO: Set parent pointers to NULL
        m -> parents[0] = NULL;
        m -> parents[1] = NULL;
        
        
        // TODO: Randomly assign alleles (to that person)
        m -> alleles[0] = random_allele();
        m -> alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    //This function is of return type pointer and must return a pointer
    return (m);
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
        //return nothing since function is of return type void
    }
    
    /*This was my attempt to free memory without recursion, why does it not work?

    free(p);
   
    while (p ->parents[0] != NULL)
    {
        person *tmp = p -> parents[0];
        p = tmp;
        free(p);

    }
    while (p -> parents[1] != NULL)
    {
        person *tmp2 = p ->parents[1];
        p = tmp2;
        free(p);
    }
    */
    //free the memory allocated to parents[0]- the first and the second parent- parents[1]
    for (int i = 0; i < 2; i++)
    {
        free_family(p -> parents[i]);
    }
    
    //TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
