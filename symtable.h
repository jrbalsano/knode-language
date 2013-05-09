#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "./libs/uthash.h"
#include "typechecktype.h"

typedef struct symtab *Symtab;

struct symtab {
    char name[128];
    TypeCheckType type;
    UT_hash_handle hh;
};

Symtab symlook(char *symbol, Symtab table); 

Symtab addSymbol(Symtab table, char *symbol);

TypeCheckType findType(Symtab table, char *symbol);

void deleteSymbol(Symtab table, char *symbol);

void freeHashTable(Symtab table);

#endif
