// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * LENGTH;

// Hash table
node *table[N];

// Total size of hash table
int SIZE = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word
    int hash_index = hash(word);
    
    // Get correct linked list from hash table
    node *cursor = table[hash_index];
    
    // Traverse linked list looking for word (strcasecmp)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Found match
            return true;
        }
        // iterate to next node in linked list
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // My hash function
    // int first_letter = tolower(word[0]);
    // int second_letter = 0;
    // if (word[1] != '\0')
    // {
    //     second_letter = tolower(word[1]); 
    // }
    // int hash_val = (first_letter + second_letter) % N;
    // hash is the sum of the first and second letter
    
    // hash function from UCSD CSWeb https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-13.html
    int hashVal = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        hashVal += tolower(word[i]);
    }
    return hashVal % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Read strings from file one at a time
    // Buffer for word
    char word[LENGTH + 1];
    ;
    while (fscanf(file, "%s", word) != EOF)
    {
        // printf("Load found word %s", word);

        // Make new node
        node *n = malloc(sizeof(node));
        
        // Check for malloc issue
        if (n == NULL)
        {
            printf("Memory issue with malloc of node");
            return false;
        }
        
        // Copy in word to new node
        strcpy(n->word, word);

        // Get hash for the word
        int hash_index = hash(word);

        // Insert node into hash table.  Insert at the front of linked list
        n->next = table[hash_index];
        // Hash table points to N as head of the linked list
        table[hash_index] = n;
        // Update size of hash table
        SIZE++; 
    }
    
    // Close file maybe
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free all the nodes in the hash table
    for (int i = 0; i < N + 1; i++)
    {
        // Cursor and temp pointers for each linked list
        node *cursor = table[i];
        node *tmp = table[i];
        
        // Iterate through list
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
