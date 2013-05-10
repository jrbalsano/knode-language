#ifndef __DICT_H__
#define __DICT_H__

#include "./libs/uthash.h"
#include <stdio.h>

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

Dict initDict();
Entry addToDict(Dict d, int et, char *key, void *value);

//TODO
Entry access(Dict d, char *key);

void freeEntries(Entry entries);
void freeDict(Dict d);

#endif
