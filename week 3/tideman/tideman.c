#include <cs50.h>
#include <stdio.h>
#include <string.h>
#define MAX 9
int preferences[MAX][MAX];
bool locked[MAX][MAX];
typedef struct
{
    int winner;
    int loser;
} pair;
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int start, int end);
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidates...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++)
        candidates[i] = argv[i + 1];
    for (int i = 0; i < candidate_count; i++)
        for (int j = 0; j < candidate_count; j++)
            locked[i][j] = false;
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 2;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
}
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength1 =
                preferences[pairs[i].winner][pairs[i].loser];
            int strength2 =
                preferences[pairs[j].winner][pairs[j].loser];
            if (strength2 > strength1)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}
bool cycle(int start, int end)
{
    if (start == end)
        return true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(start, i))
                return true;
        }
    }
    return false;
}
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        if (!cycle(w, l))
        {
            locked[w][l] = true;
        }
    }
}
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                source = false;
                break;
            }
        }
        if (source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
