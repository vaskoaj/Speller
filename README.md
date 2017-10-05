#Spell Check

dictionary.c defines functions that are used in the speller.c. These functions include:

    check - compares an input in the form of a string with words found in the dictionary. If the word if in the dictionary it return True, otherwise, False

    load - load takes a text file with a list of valid words and loads it into a trie

    size - returns how many words are loaded in the trie

    unload - pretects from memory leaks by freeing all nodes in the trie after the spellcheck is complete

speller.c can take 2 arguments: the dictionary, and the text. If no dictionary is provided, it will default to the large dictoinary provided.

