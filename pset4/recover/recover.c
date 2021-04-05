#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//bool is not a standard type in C (like int or char) but only in stdbool.h. Also, true and false are declared in stdbool.h. (source techoverflow)
#include <stdbool.h>

typedef uint8_t BYTE;

bool jpeg_test(uint8_t buffer[]);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover *name of forensic image*\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    //always keep it all NULL just so it doesnt allocate it somewhere where something already exists
    FILE *outptr = NULL;
    //program should create filename by: naming each file ###.jpg, where ### is three-digit decimal number from 000 on up. (8 because of \0 at end of string)
    char filename[8];
    //we know each jpeg file is stored as 512bytes
    uint8_t buffer[512];
    int count = 0;

    //***NOTE**   (REPLACING WHILTE STATEMENT OF (WHILE(FEOF(INPTR !=0)) WITH BELOW WHILE STATEMENT FIXES LAST JPG PROBLEM
    //Reason being "eof() is a little surprising in that it only returns true if you try to read past the end of the file....
    //.....When you have read every byte of the file, it will still return false. It will only return true if you try to read one more time, and by that time it can be "too late""

    //**NOTE** calling fread in the while statement not only retruns true if it was able to do so, but ALSO reads the bytes into buffer. Therefore you dont need to call it again inside the loop
    while (fread(buffer, sizeof(uint8_t), 512, inptr))
    {
        //fread format = (*where you will store the read stuff, *size of each elemnt you're reading*, *how many elements you're reading*, *where to read from*)
        //reading 512 bytes at a time.


        //tests if the first 4 bytes of the array match what a .JPEG should be.
        //if it does it will make a jpeg file with format ###.jpg
        if (jpeg_test(buffer))
        {
            //can not fopen on a file that is already open. So when making a new file we need to close the other one first. If pointer is pointing at a file it will close it.
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            //** SPRINTF - Esentially works similar to PRINTF but instead of printing to console it prints INTO an ARRAY. Also Appends for you and catches the number of characters.
            //%03i means print a 3 digit integer to represent that integer, even if its 0, or 1 >> eg 000 , 001
            sprintf(filename, "%03i.jpg", count);

            //creating the new file by opening it and then pointing to it with our pointer
            outptr = fopen(filename, "w");
            //increase the count so that our ###.jpg will increase by 1
            count ++;
        }

        //if the pointer is pointing at something (our file to write in which should be created) it will write the jpg into the file.
        if (outptr != NULL)
        {
            //similar to fread, the format is: *where you will take the info*, *size of the info*, *number of elements to read*, *where you want to write the info*
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
        outptr = NULL;
    }

    return 0;
}




bool jpeg_test(uint8_t buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}
