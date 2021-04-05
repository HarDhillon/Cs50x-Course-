#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //candidate_count = argc - 1

    for (int i = 0; i < candidate_count; i++)
    {
        //compares the the vote cast by voter against list of candidates to see if it matches any of candidates.
        if (strcmp(name, candidates[i].name) == 0)
        {
            //if vote cast matches a candidates name that candidates vote goes up by 1. Else no changes made
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winner_votes)
        {
            //sets a number for the highest number of votes recieved by a candidate
            winner_votes = candidates[i].votes;
        }
        //prints a candidates name if they recieved equal to the number of votes recieved by top voted candidate (allowing multiple winners)
        if (candidates[i].votes == winner_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

