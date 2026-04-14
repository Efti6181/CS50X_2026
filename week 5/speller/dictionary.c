#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;
#define N 676
node *table[N];
unsigned int word_count = 0;
bool check(const char *word)
{
    char lower_word[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[len] = '\0';
    unsigned int index = hash(lower_word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower_word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}
unsigned int hash(const char *word)
{
    int first = tolower(word[0]) - 'a';
    int second = 0;
    if (word[1] != '\0')
    {
        second = tolower(word[1]) - 'a';
    }
    return first * 26 + second;
}
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (!new_node)
        {
            fclose(file);
            return false;
        }
        strcpy(new_node->word, word);
        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    fclose(file);
    return true;
}
unsigned int size(void)
{
    return word_count;
}
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
