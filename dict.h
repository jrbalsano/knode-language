#ifndef __DICT_H__
#define __DICT_H__

#include "./libs/uthash.h"
#include <stdio.h>

typedef struct entry *Entry;
typedef struct dict *Dict;

//add enums so that we can figure out what it is that we're freaking storing
struct entry {
    char key[128];
    //char value[128];
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

Entry addEntry(Entry entries, char *key, char *val);
Entry addToDict(Dict d, char *key, char *val);
Entry access(Dict d, char *key);

void freeEntries(Entry entries);

#endif
