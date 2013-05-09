#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "./libs/uthash.h"
#include "absyn.h"

typedef struct symtab *Symtab;

struct symtab {
    char name[128];
    void *value;
    int num_val;
    UT_hash_handle hh;
};

Symtab symlook(char *symbol, Symtab table); 

void deleteSymbol(Symtab table, char *symbol);

void storeData(Symtab table, char *symbol, void *data);

void freeHashTable(Symtab table);

#endif
