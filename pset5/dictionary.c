// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

//number of items in dictionary, to be incremented
int dict_items = 0;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    //check if able to open
    if (file == NULL)
    {
        printf("Failed to open %s", dictionary);
        return false;
    }

    char new_word[LENGTH + 1];
    while (fscanf (file, "%s", new_word) != EOF)
    {
        //making a node to store our word
        //remember that malloc returns a pointer
        node *new_node = malloc(sizeof(node));
        //checking malloc worked
        if (new_node == NULL)
        {
            printf("Malloc did not work");
            return false;
        }
        // STRCPY:  char* strcpy(char* destination, const char* source) Source: https://www.programiz.com/c-programming/library-function/string.h/strcpy
        //copying the word from scanf into the structure of tempnode, and into the 'word' section
        strcpy(new_node->word, new_word);

        int key = hash(new_word);

        //if this is the FIRST node in the 'bucket'
        if (table[key] == NULL )
        {
            new_node->next = NULL;
            table[key] = new_node;
        }
        else
        {
            //what we are doing is first pointing the new node to where the head of the table is pointing (since head of table is pointer), then we point
            //the head of table to the new node, chaining in the new node.
            //remember that since [table] is a pointer we are pointing to where table[key] is POINTING not AT table[key]
            new_node->next = table[key];
            table[key] = new_node;
        }

        //rather than go through the file and count how many items we have, we can +1 to everytime we make add a word to our hashtable
        dict_items ++;
    }

    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key = hash(word);

    node *cursor = table[key];

    while (cursor != NULL)
    {
        //strcasecmp will return 0 if they are the SAME word, irregardless of case
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
//source: http://www.cse.yorku.ca/~oz/hash.html#:~:text=If%20you%20just%20want%20to,Also%20see%20tpop%20pp. AND  https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash(const char *word)
{
// source: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9189q/
//removed some aspects of original code as case sensitivty was becoming an issue
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash += tolower(word[i]);
    }
    return hash % N;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_items;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i=0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            //two pointers, one points at what is about to be deleted (trav) while the other(cursor) points to the next thing and checks if it is NULL
            node* trav = cursor;
            cursor = cursor->next;
            free(trav);
        }
    }
    return true;
}



