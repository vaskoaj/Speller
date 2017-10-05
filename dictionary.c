/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

node *root;

int totwords = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // initialize variables
    node* curr = root;
    int index = 0;

    // while we are in a word
    while (word[index] != '\0')
    {
        //make the letter same case as dictionary
        int letter = tolower(word[index]);

        //if the word is a letter and the path is open
        if (isalpha(letter) && curr->children[letter - 'a'] != NULL)
        {
            // go down path
            curr = curr->children[letter - 'a'];
            index++;
        }
        //if it is an apostrophy, and path is open
        else if (letter == '\'' && curr->children[26] != NULL)
        {
            //go down path
            curr = curr->children[26];
            index++;
        }
        //else, not a word
        else
        {
            return false;
        }
    }
    //once string is complete, check if valid entry
    if (curr->is_word == true)
    {
        return true;
    }
    return false;

}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *odict = fopen(dictionary, "r");

    if (odict == NULL)
    {
        return false;
    }

    root = calloc(1, sizeof(node));
    node* curr = root;

    int index = 0;
    for (int c = fgetc(odict); c != EOF; c = fgetc(odict))
    {
        //allow alpha characters
        if (isalpha(c))
        {
            // if path hasn't been made, allocate path
            if (curr->children[c - 'a'] == NULL)
            {
                curr->children[c - 'a'] = calloc(1, sizeof(node));
                curr = curr->children[c - 'a'];
            }
            // if there is a path, go down it
            else
            {
                curr = curr->children[c - 'a'];
            }
            index++;
        }
        //allow apostrophes in the middle of words
        else if (c == '\'' && index > 0)
        {
            if (curr->children[26] == NULL)
            {
                curr->children[26] = calloc(1, sizeof(node));
                curr = curr->children[26];
            }
            else
            {
                curr = curr->children[26];
            }
        }
        // we must have found a whole word
        else if (index > 0)
        {
            // label a complete word
            curr->is_word = true;

            // prepare for next word
            curr = root;
            index = 0;
            totwords++;
        }
    }
    fclose(odict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return totwords;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
 void freeNode(node* curr)
 {
     //check that every child is free
     for (int a = 0; a < 27; a++)
     {
         //if child is not free use recursion to free children
         if (curr->children[a] != NULL)
         {
             freeNode(curr->children[a]);
         }
     }
     //once all children are free, free current node
     free(curr);
 }

bool unload(void)
{
    freeNode(root);
    return true;
}