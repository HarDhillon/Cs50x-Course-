#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool keychecker(string key);

int main(int argc, string argv[])
{

    int key = 0;

    // if more than 1 command line argument is input the program will not run
    if (argc != 2 || keychecker(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // atoi finds numbers in a string and returns them as ints
    key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    //printf("key: %i\n", key); prints out key if we want to see it


    int n = strlen(plaintext);

    printf("ciphertext: ");

    for (int x = 0; x < n; x++)
    {
        char s = plaintext[x];

        if (isalpha(s))
        {
            int ascii = s;
            int cipher = 0;

            int A = 65;
            int a = 97;

            if (islower(s))
            {
                //we convert all the ascii into a range from 0-26, this allows us to loop back into A if we go past Z
                //it works because there are 26 letters in the alphabet making "z" 26. Modulo operator returns remainder when divided.
                //if dividing by bigger number the number being divided is itself the remainder. So only 26 returns a remainder, which is 0.
                cipher = (ascii - a + key) % 26 + a;
                printf("%c", cipher);
            }
            else
            {
                // same as above except we minus by the ascii value of capital A as we are dealing with capitals
                cipher = (ascii - A + key) % 26 + A;
                printf("%c", cipher);
            }
        }
        else
        {
            //in case of punctuation we simply print it as was
            printf("%c", s);
        }
    }

    printf("\n");
}

//the function goes through a string and checks if every number is a digit. If there is a non-digit present it returns flase and the program stops.
bool keychecker(string key)
{
    int n = strlen(key);

    for (int x = 0; x < n; x++)
    {
        if (isdigit(key[x]) == 0)
        {
            return false;
        }
    }
    return true;
}
