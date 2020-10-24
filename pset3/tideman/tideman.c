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

//my included functions
void merge_sort(pair pairs[], int l, int r);
void merge(pair pairs[], int l, int m, int r);
bool cycle_check(int l , int s);

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
    // TODO
    for (int i = 0; i < candidate_count;i++)
    {
        if(strcmp(candidates[i],name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
//ranks is passe din as pointer so it can be change din this method
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count;j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
//Checks upper righ triangle of amtrix for who has more votes
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count;i++)
    {
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
    // TODO
    merge_sort(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    bool cycle = false;

    //checls for cycles each time a pair is about to be added to the graph
    for (int i = 0; i< pair_count; i++)
    {
        cycle = cycle_check( pairs[i].loser, pairs[i].winner);
        if (cycle == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
//if amount of falses in a column equals candidate count then it is the source node
void print_winner(void)
{
    // TODO
   int count;

    for (int i = 0; i < candidate_count; i++)
    {
        count = 0;

        for(int j = 0; j < candidate_count; j++)
        {
           if (locked[j][i] == false)
           {
               count++;
           }
        }

        if (count == candidate_count)
        {
            printf("%s\n",candidates[i]);
            break;
        }
    }
    
    return;
}


void merge_sort(pair arr[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;

        //recursively sorts left and right sections
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);

        merge(arr, l, mid, r);
    }
}

void merge(pair arr[], int l, int m, int r)
{
    int i,j,k;

    //lengths of each subarray
    int n1 = m - l + 1;
    int n2 = r - m;

    pair arrL[n1];
    pair arrR[n2];

    //Create the left and right subarrays
    for(i = 0; i < n1; i++)
        arrL[i] = arr[l+i];
    for(j = 0; j < n2; j++)
        arrR[j] = arr[j + m + 1];

    //pointers to each array
    i = 0;
    j = 0;
    k = l;

    //iterates through both sub arrays to add them into a sorted pairs array
    // since k always starts at l it will make sure your main array is being osrted correctely
    //arrays in C are passed in as pointers
    while(i < n1 && j < n2)
    {
        if(preferences[arrL[i].winner][arrL[i].loser] - preferences[arrL[i].loser][arrL[i].winner] >= preferences[arrR[j].winner][arrR[j].loser] - preferences[arrR[j].loser][arrR[j].winner])
        {
            arr[k] = arrL[i];
            i++;
        }
        else
        {
            arr[k] = arrR[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        arr[k] = arrL[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = arrR[j];
        j++;
        k++;
    }

}


//DFS search into each losing node
//once source is equal to a loser that singals there is a cycle
bool cycle_check(int l , int s)
{
    if (l == s)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i] == true)
        {
            if (cycle_check(i,s))
            {
                return true;
            }
        }
    }

    return false;
}

