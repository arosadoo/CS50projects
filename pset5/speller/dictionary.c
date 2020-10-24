// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];

//Number of words stored
int totalWords = 0;



////////// MY ADDED FUNCTIONS

// Adds nodes to linked list
void addNode(node *newNode, int index)
{
    if(table[index] == NULL)
    {
        table[index] = newNode;

    }
    else
    {
        newNode->next = table[index];
        table[index] = newNode;
    }
}

//Sets Heads of lsit to NULL
void initializeTable(void)
{
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}


//All nodes in the linked list is free'd from memory
void destroy(node *head)
{
    if(head == NULL)
    {
        return;
    }
    
    destroy(head->next);
    
    free(head);
}
///////////
//////////
/////////



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *temp = table[hash(word)];
    while(temp != NULL)
    {
        if(strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}


//This website is why i chose the size of the hash table as it is: http://www.cs.ecu.edu/karl/3300/spr14/Notes/DataStructure/hashtable.html
//Hash Function was created by dan bernstein
// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Initializes Lists to NULL
    initializeTable();

    // Opens Dictionary
    FILE *dictFile = fopen(dictionary,"r");
    if(dictFile == NULL)
    {
        return false;
    }

    char aWord[LENGTH + 1];
    while(fscanf(dictFile, "%s", aWord) != EOF)
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }

        strcpy(n->word, aWord);
        n->next = NULL;

        addNode(n, hash(n->word));

        totalWords++;
    }
    
    
    if(fscanf(dictFile, "%s", aWord) == EOF)
    {
        fclose(dictFile);
        return true;
    }
    
    fclose(dictFile);
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
   
   for(int i = 0; i < N; i++)
   {
       destroy(table[i]);
       
   }
   
   return true;
}
