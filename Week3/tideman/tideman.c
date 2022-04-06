#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool includes(int winners[], int candidate, int count);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // loop through candidate i of candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // when the name matches, assigns ranks[rank] the candidate's index
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // if no name match is found
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    // loop through each voter's rank i in ranks besides the last one => [candidate_count - 1]
    // because the last candidate in the ranks array does not get to score
    for (int i = 0; i < candidate_count - 1; i++)
    {
        //  ranks [i] => the index of the candidate in the candidates array
        int candidate = ranks[i];
        // printf("%i(i:%i):\t", candidate, i);
        // for each rank i in ranks, loop through ranks[i+1] to ranks[candidate_count]
        for (int j = i + 1; j < candidate_count; j++)
        {
            // so that we can add 1 at (x,y) coord in preferences table/array, meaning :
            // add 1 at row for candidate, at column othercandidate
            int othercandidate = ranks[j];
            // printf("%i(j:%i)\t", othercandidate, j);
            preferences[candidate][othercandidate]++;
        }
        // printf("\n");
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop through the `preferences` table / 2D array to identify all pairs of candidates where one is preferred
    for (int i = 0; i < candidate_count; i++) // row i -> current candidate
    {
        for (int j = 0; j < candidate_count; j++) // column j -> other candidate
        {
            int vs_score = preferences[i][j] - preferences[j][i];
            if (
                i != j // this is to prevent comparing a candidate with himself
                && vs_score > 0)
            {
                // printf("%s vs. %s => %i\t", candidates[i], candidates[j], vs_score);
                pair vs_pair;
                vs_pair.winner = i;
                vs_pair.loser = j;
                // add pair to `pairs` array
                pairs[pair_count] = vs_pair;
                pair_count++;
                // increment `pair_count` by 1
            }
        }
        // printf("\n");
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        pair currpair = pairs[i];
        int currpair_winstrength = preferences[currpair.winner][currpair.loser];
        for (int j = i + 1; j < pair_count; j++)
        {
            pair nextpair = pairs[j];
            int nextpair_winstrength = preferences[nextpair.winner][nextpair.loser];
            // printf("%s-%i vs %s-%i\n",
            //        candidates[currpair.winner], preferences[currpair.winner][currpair.loser],
            //        candidates[nextpair.winner], preferences[nextpair.winner][nextpair.loser]);
            if (nextpair_winstrength > currpair_winstrength)
            {
                pair tmp = currpair;
                pairs[i] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }

    return;
}

/**
 * This function looks at each pair in the pairs array.
 * If one if found to have the candidate id (its index in `candidates` array) as its winner,
 * than the function returns the index of the pair, in the `pairs` array
 * If none is found, the function returns -1, to signify `not found`.
 */
int get_win_locked_pair_for(int candidate)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = (pairs[i]).winner;
        int loser = (pairs[i]).loser;

        if (locked[winner][loser] && winner == candidate)
        {
            return i;
        }
    }
    return -1;
}

int trace_graph(int pair_index)
{
    printf("\n\t\t\tbreaking condition: %s\t", pair_index >= pair_count - pair_index ? "true" : "false");
    printf("\t\t\tpair_index: %i, pair_count: %i\n", pair_index, pair_count);

    if (pair_index >= pair_count - pair_index)
    {
        return pair_index - 1;
    }

    pair tmp;
    tmp = pairs[pair_index];
    printf("\t\t\tpair: %i(%s, %s)\n", pair_index, candidates[tmp.winner], candidates[tmp.loser]);

    if (locked[tmp.winner][tmp.loser])
    {
        return trace_graph(pair_index + 1);
    }

    return -1;
}

/**
 *
 *
Lock pairs into the candidate graph in order; avoid creating cycles
A cycle:
a cycle forms when, for any given pair:
1) if the loser of the pair can be traced as a winner amongst the previously locked pairs stored in the `locked` table / 2D array
2) AND if the winner of the pair can be cycled back to himself, by following the trail of all previously locked pairs stored in `locked` table

Example :
pair (c,a) where winner = c, loser = a,
locked array : [(d,a), (a,b), (b,c)]
which translates to chaining : c -> a -> b -> c

Explaination: loser can be traced as winner in previously locked pair (a,b)
Since this is the case, cycle detection must be attempted.
The attempt consists of building a chain starting at the winner (c in this case), going through the found locked pair ((a,b) in this case), and see if it leads back to the winner.
The last locked pair being (b,c), c ends up cycling.

 *
 *
*/
void lock_pairs(void)
{
    // DEBUG sorted pairs
    printf("\nexisting pairs:\n");
    for (int i = 0; i < pair_count; i++)
    {
        // printf("%s(%i) vs %s(%i)\n",
        //        candidates[pairs[i].winner],
        //        preferences[pairs[i].winner][pairs[i].loser],
        //        candidates[pairs[i].loser],
        //        preferences[pairs[i].loser][pairs[i].winner]);
        printf("%i:(%s, %s)\n",
               i,
               candidates[pairs[i].winner],
               candidates[pairs[i].loser]);
    }
    printf("\n");

    for (int i = 0; i < pair_count; i++)
    {
        int winner = (pairs[i]).winner;
        int loser = (pairs[i]).loser;

        int start_pair_index = get_win_locked_pair_for(loser);

        printf("looking at pair %i:(%s,%s)\n", i, candidates[winner], candidates[loser]);

        if (start_pair_index < 0)
        {
            printf("\tno locked pair found where << %s >> is a winner => ", candidates[loser]);
            printf("\tLOCKING pair (%s,%s).\n\n", candidates[winner], candidates[loser]);
            locked[winner][loser] = true;
        }
        else
        {
            printf("\tcandidate << %s >> is found as winner of locked pair (%s, %s). returning %i (index of pair in pairs array)\n\n", candidates[loser], candidates[(pairs[start_pair_index]).winner], candidates[(pairs[start_pair_index]).loser], start_pair_index);

            printf("\t\tstarting graph tracing from winner << %s >> (through: %i(%s,%s))\n", candidates[winner], start_pair_index, candidates[pairs[start_pair_index].winner], candidates[pairs[start_pair_index].loser]);
            int last_traced_pair = trace_graph(start_pair_index);

            printf("\n\t\tlast_traced_pair %i(%s,%s)\n\n", last_traced_pair, candidates[pairs[last_traced_pair].winner], candidates[pairs[last_traced_pair].loser]);
            printf("\t\tthe last losing candidate returned by trace is << %s >> (%i) => ", candidates[pairs[last_traced_pair].loser], pairs[last_traced_pair].loser);

            if (last_traced_pair > -1 && pairs[last_traced_pair].loser != winner)
            {
                printf("\tLOCKING pair %i:(%s,%s)\n\n\n", i, candidates[winner], candidates[loser]);
                locked[winner][loser] = true;
            }
            else
            {
                printf("\tCYCLE detected: UNlocking pair %i:(%s,%s)\n\n\n", i, candidates[winner], candidates[loser]);
                locked[winner][loser] = false;
            }
        }
    }

    return;
}

// Print the winner of the election, the one candidate who is the source of the graph,
// the only candidate that no other candidate won over
void print_winner(void)
{
    /*
        // DEBUG preferences table

        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                printf("%i\t", preferences[i][j]);
            }
            printf("\n");
        }

        // DEBUG pair_count
        printf("pair_count: %i\n", pair_count);

        // DEBUG sorted pairs
        for (int i = 0; i < pair_count; i++)
        {
            // printf("%s(%i) vs %s(%i)\n",
            //        candidates[pairs[i].winner],
            //        preferences[pairs[i].winner][pairs[i].loser],
            //        candidates[pairs[i].loser],
            //        preferences[pairs[i].loser][pairs[i].winner]);
            printf("(%i, %i)\n",
                   pairs[i].winner,
                   pairs[i].loser);
        }

    // DEBUG locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            printf("%s\t", locked[i][j] ? "T" : ".");
        }
        printf("\n");
    }

*/

    for (int i = 0; i < candidate_count; i++) // i => columns
    {
        int total = 0;
        for (int j = 0; j < candidate_count; j++) // j => rows
        {
            // printf("row:%i, col:%i\t", j, i);
            if (locked[j][i] == false)
            {
                total++;
            }
            if (total == candidate_count)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
        // printf("\n");
    }
    return;
}