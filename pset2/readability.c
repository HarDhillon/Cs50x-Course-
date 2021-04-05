#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float letter_checker(string text);
float word_counter(string text);
float sentence_counter(string text);


int main (void)
{
    string text = get_string("Text: ");

    float chars = letter_checker(text);
    float words = word_counter(text);
    float sentences = sentence_counter(text);

    float L = (chars / words) * 100;
    float S = (sentences / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int ANS = round(index);

    if (ANS >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (ANS < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", ANS);
    }


    /* printf("Characters: %f \n", chars); */
    /* printf("Words: %f \n", words); */
    /* printf("Sentences: %f \n", sentences); */
}



float letter_checker(string text)
{
    float counter = 0;
    int number_char = strlen(text);

    for (int x = 0, n = number_char; x < n; x++)
    {
        if ( isalnum(text[x])!= 0)
        {
            counter++;
        }
    }
    return counter;
}



float word_counter(string text)
{
    float counter = 1;
    int number_char = strlen(text);

    for (int x = 0, n = number_char; x < n; x++)
    {
        if (isblank(text[x]) != 0 )
        {
            counter ++;
        }
    }
    return counter;
}


float sentence_counter(string text)
{
    float counter = 0;
    int number_char = strlen(text);

    for (int x = 0, n = number_char; x < n; x++)
    {
        int ASC = text[x];
        if (ASC == 33 || ASC == 63 || ASC == 46 )
        {
            counter ++;
        }
    }
    return counter;
}
