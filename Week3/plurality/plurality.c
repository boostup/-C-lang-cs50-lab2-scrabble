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
} candidate;

typedef struct
{
    candidate candidate;
    int position;
} array_value;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void sort(string algname);
void selection_sort(int n);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort candidates by vote
    // (the last item in the array is the highest vote count)
    sort("selection");

    // Print winner(s)
    int winning_vote_count = candidates[candidate_count - 1].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winning_vote_count)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

void sort(string algname)
{

    if (strcmp(algname, "selection") == 0)
    {
        selection_sort(candidate_count);
    }
}

// To implement this algorithm, 1) I watched the short on selection sort
// https://youtu.be/3hH8kTHFw2A?t=93
// 2) I referred to the recursion code seen in class:
// https://cdn.cs50.net/2021/fall/lectures/3/src3/recursion.c
void selection_sort(int n)
{
    // printf("starting selection sort now (n: %i)\n", n);
    // printf("first position of unsorted array: %i\n", candidate_count - n);

    // when the end of the array has been reached
    if (n <= 0)
    {
        return;
    }

    // call upon itself to solve smaller and smaller portions of the problem
    selection_sort(n - 1);

    array_value smallest;
    smallest.candidate = candidates[0];
    smallest.position = 0;

    // go through the entire array from i to n
    // to find the smallest value
    for (int i = 0; i < n; i++)
    {
        if (candidates[i].votes < smallest.candidate.votes)
        {
            smallest.candidate = candidates[i];
            smallest.position = i;
        }
    }

    // swap the smallest value

    int start_pos_unsorted = candidate_count - n;

    // storing temporarily the value at the start of the unsorted portion of the array
    array_value temp;
    temp.candidate = candidates[start_pos_unsorted];
    temp.position = start_pos_unsorted;

    // at that same index/position, place the smallest vote value
    candidates[start_pos_unsorted] = smallest.candidate;

    // where the smallest was, place there the value of the temporary value stored ealier
    candidates[smallest.position] = temp.candidate;
}
