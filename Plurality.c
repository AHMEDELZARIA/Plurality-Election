#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool vote(string name);
void print_winner(void);

// Max number of candidates
#define MAX 9

// Number of candidates
int num_candidates;

// Candidates have name and vote count
typedef struct
{
    string name;
    int vote;
}
candidate;

// Array of candidates
candidate candidates[MAX];

int main(int argc, string argv[])
{
    // If less than two arguments entered
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate...]\n");
        return 1;
    }

    // If more than 9 candidates entered
    num_candidates = argc - 1;
    if (num_candidates > MAX)
    {
        printf("Number of candidates exceeded\n");
        return 1;
    }
    
    // No numbers in numbers candidate names
    for (int i = 1; i <= num_candidates; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            if (isdigit(argv[i][j]))
            {
                printf("Candidate names cannot include numbers\n");
                return 1;
            }
        }
    }
    
    // No repeated candidates
    for (int i = 1; i < num_candidates; i++)
    {
        for (int j = i + 1; j <= num_candidates; j++)
        {
            if (strcmp(argv[j], argv[i]) == 0)
            {
                printf("Repeated candidates\n");
                return 1;
            }
        }
    }
    
    // Fill up candidates array with names
    for (int i = 0; i < num_candidates; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].vote = 0;
    }
    
    // Prompt user for number of voters
    int num_voters = get_int("Number of voters: ");
    
    // Prompt user for votes
    for (int i = 0; i < num_voters; i++)
    {
        string name = get_string("Vote: ");
        
        if (vote(name) == false)
        {
            printf("Invalid vote.\n");
            i--;
        }
    }
    
    // Print winner
    print_winner();
}


// Function that accumulates votes and determines if vote is valid or not
bool vote(string name)
{
    for (int i = 0; i < num_candidates; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].vote += 1;
            return true;
        }
    }
    return false;
}


// Function that prints the winner(s)
void print_winner(void)
{
    // Calculates max number of votes and stores them in the variable max_num_votes
    int max = 0;
    for (int i = 1; i < num_candidates; i++)
    {
        if (candidates[i].vote > candidates[max].vote)
        {
            max = i;
        }
    }
    int max_num_votes = candidates[max].vote;
    
    for (int i = 0; i < num_candidates; i++)
    {
        if (candidates[i].vote == max_num_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
