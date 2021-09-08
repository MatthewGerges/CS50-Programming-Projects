/*
TODO
Open a Memory Card
Look for Beginning of a JPEG
if the beginning of a jpeg file is found, open a new JPEG file
Write 512 bytes until a new JPEG is found
JPEG stored back - to back in memory card
Each block is 512 bytes (read 512 bytes at a time)
//Not every JPEG file is 512 bytes - can be more so keep writing
*/

//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//This line defines a custom type called variable which is an unsigned 8-bit integer (only positive values, can assume more values)
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //the counter allows us to name successive jpeg files
    int counter = 0;
    //initializes the variable (technically a boolean) that determines if the jpeg we found is our very first
    int foundfirst = 0;
    
    //open the source file by opening whatever the second command line argument was
    FILE *input = fopen(argv[1], "r");
    
    //check if there is an actual source file, don't run the code if the source file is null
    if (input == NULL)
    {
        return 1;
        //return anything other than 0 breaks out of the int main function
    }
    //the user must enter 2 arguments- 1 is the program's name, the second is the name of the file to be opened
    if (argc != 2)
    {
        return 2;
        //break out of function by returning a non-zero value
    }
    
    FILE *destination = NULL;
    //creates the pointer to the ouput / destination file
    //setting it equal to null initializes it
    
    BYTE buffer[512];
    //buffer is a temporary unsigned-8bit integer, and it has 512 elements (number of elements in each block)
    //can it be while eof? then do an fread later
    
    //we use &buffer here instead of buffer because we are using the pointer instead of the array (which picks up wherever it left off)
    while (fread(&buffer, sizeof(BYTE), 512, input))
        //while a buffer can still be read from the input file, read it, can also do ==1
        //must say size of BYTE (1 byte or 1 uint8_t) instead of size of buffer because a buffer is 512 bytes big
        //we must read from the file to write to it later, the second and third argument are kind of interchangeable
    {
        //check if we found a jpeg file by checking if its header (the first 4 bytes) match the first four bytes of a header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if this is our very first jpeg, set foundfirst to 1 (false), this if else is here so we don;t close a destination file that was never opened
            if (foundfirst == 0)
            {
                foundfirst = 1;
            }
            //if this is not our first jpeg, we can close the previous jpeg that we were writing to
            else
            {
                fclose(destination);
                //counter++; 
                //here?
            }
            //char filename[8] creates enough space in memory for the filename string (8 bits- for the 3 numbers, the ., the jpg and the nul character: \0)
            //anything greater than 8 would also work but would waste memory
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            //open the destination file, whose name is based on teh sprintf statement
            destination = fopen(filename, "a");
            //"a" means append - the same as "w" (which can also be used) but prevents overwriting
            //fwrite(&buffer, 512, 1, destination);
            //cannot put the above comment over here because if the new signature of a jpeg is not yet detected, you would open a new file and split it in half
            counter++;
        }
        //if you haven't found a new JPEG, keep writing to it (no point of opening a new one)
        //IMPORTANT to note that this directly lines up with the previous if statement that detects if a jpge is found, so if a new one is not found, keep writing to it
        //we check if if foundfirst is not equal to 0 because if it was equal to 0 we would not have found a jpeg and yet we would still be writing to it
        if (foundfirst != 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, destination);
        }
        
    }
    //close the source file and destination
    fclose(input);
    fclose(destination);
    return 0;
    //returning a value of 0 means that the function has executed properly and ended
}