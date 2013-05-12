#ifndef __DICT_H__
#define __DICT_H__

#include "./libs/uthash.h"
#include <stdio.h>
#include <stdarg.h>

/* *
 * This is our dict representation in C. Entries represent each individual
 * key-value pair in a dictionary. A dictionary struct points to a series of
 * entries.
 */

typedef struct entry *Entry;
typedef struct dict *Dict;

struct entry {
    char key[128];
    enum { echar, eint, edouble} entry_type;
    union {
        char str[128];
        int num;
        double dub;
    } value;
    UT_hash_handle hh;
};

struct dict {
    char name[128];
    Entry entries;
};

/**
 * Initialize the dictionary and set the value of entries to NULL (MUST HAPPEN
 * FOR UTHASH TO WORK)
 */
Dict initDict();

/* *
 * Free all the entries!
 */
void freeEntries(Entry entries);

/* *
 * Frees the dictionary as well as all the entries it is associated with. 
 */
void freeDict(Dict d);

/**
 * Adds the key-value pair to the dictionary specified, with the value specified
 */
Entry addToDict(Dict d, int et, char *key, ...);

/* *
 * Checks through the entries of the dictionary to see if the entry exists and
 * returns the value for the key if it exists. Otherwise, it returns null.
 */
Entry getEntryForKey(Dict d, char *key);

#endif
