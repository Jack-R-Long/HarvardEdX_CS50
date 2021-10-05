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
}
pair;

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
void print_winner(void);
void swap(pair *xp, pair *yp);

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
    // printf("Unsorted pairs\n");
    // for (int i = 0; i < pair_count; i ++)
    // {
    //     printf("Pair %i is winner %s and loser %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
    // }
    sort_pairs();
    // printf("\nSorted pairs\n");
    // for (int i = 0; i < pair_count; i ++)
    // {
    //     printf("Pair %i is winner %s and loser %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
    // }
    printf("\nPair count: %d \n Locked pairs\n", pair_count);
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            printf(" %d ", locked[i][j]);
        }
        printf("\n");
    }
    lock_pairs();
    printf("\nPair count: %d \n Locked pairs\n", pair_count);
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            printf(" %d ", locked[i][j]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check for valid candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // record rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update global preferences array with selection sort kinda
     for (int i = 0; i < candidate_count - 1; i++)
     {
        //  Nested loop for selection sort
        for (int j = i + 1; j < candidate_count; j++)
        {
             preferences[ranks[i]][ranks[j]]++;
        }
     }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop through all candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Nested loop to traverse 2d array
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort pairs array with bubble sort
    int i, j;
    for (i = 0; i < pair_count - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < pair_count - i - 1; j++)
        {
            int current_pair_strength = preferences[pairs[i].winner][pairs[i].loser];
            int next_pair_strength = preferences[pairs[j].winner][pairs[j].loser];

            if (current_pair_strength > next_pair_strength)
            {
                swap(&pairs[j], &pairs[j + 1]);
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Lock the first pair
    locked[pairs[0].winner][pairs[0].loser] = true;
    // Prevent cycle, one row locked[candidate#] must have (candidate# - 1) number of edges (treu)
    int source_edge_number = candidate_count - 1;
    int pair_winner, pair_loser;
    for (int i = 1; i < pair_count; i++)
    {
        pair_winner = pairs[i].winner;
        pair_loser = pairs[i].loser;
        int loser_edges = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[pair_loser][j] == true)
            {
                loser_edges++;
            }
        }
        // make sure loser is not the soure 
        if (loser_edges != source_edge_number)
        {
            // lock em up
            locked[pair_winner][pair_loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // winner is the 'source' of the graph
    string winner;
    int winner_tally = -100;
    for (int i = 0; i < candidate_count; i++)
    {
        int current_tally = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if ( locked[i][j] == true)
            {
                current_tally++;
            }
            else
            {
                current_tally--;
            }
        }
        if (current_tally > winner_tally)
        {
            winner = candidates[i];
            winner_tally = current_tally;
        }
    }
    printf("%s\n", winner);
    return;
}

// Helper swap function
void swap(pair *xp, pair *yp)
{
    pair temp = *xp;
    *xp = *yp;
    *yp = temp;
}
