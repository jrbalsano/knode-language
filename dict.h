#ifndef __DICT_H__
#define __DICT_H__

#include "./libs/uthash.h"
#include <stdio.h>

typedef struct entry *Entry;
typedef struct dict *Dict;

struct entry {
    union {
        char *str;
        int num;
        double dub;
        float flo;
    } value;
    char key[128];
    UT_hash_handle hh;
};

struct dict {
    char name[128];
    Entry *entries;
};

void access(char *key);

void freeDict(Dict dictionary);

#endif
