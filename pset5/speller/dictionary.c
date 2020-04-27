// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h> //strlen() strcmp()
#include <ctype.h> //tolowe()
#include <stdio.h> //file
#include <stdlib.h> //malloc()

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Closest prime to 143091 / 0.75 (143091 is the number of words in /dictionaries/large)
const unsigned int N = 190793;

// Hash table
node *table[N];

// Count for size()
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //string to lowercase (Case insensitive)
    int len = strlen(word);
    char lowerword[len + 1];
    for (int i = 0; i < len; i++)
    {
        lowerword[i] = tolower(word[i]);
    }
    lowerword[len] = '\0';

    int index = hash(lowerword);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lowerword) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 Hash function, ~best for short input
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;
        /*hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(inptr, "%s\n", word) != EOF)
    {
        //New node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        //Add node to table
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
        count++;
    }

    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
