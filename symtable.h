#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "./libs/uthash.h"
#include "absyn.h"

typedef struct symtab *symtab;

struct symtab {
    char name[128];
    void *value;
    int num_val;
    UT_hash_handle hh;
};

struct symtab *symtable;

struct symtab *symlook(char *symbol); 

void deleteSymbol(char *symbol);

void storeData(char *symbol, void *data);

void freeHashTable();

#endif
