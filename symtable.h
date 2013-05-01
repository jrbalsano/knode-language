#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "./libs/uthash.h"
#include "absyn.h"

typedef struct symtab *symtab;

struct symtab {
    char *name;
    void *value;
    UT_hash_handle hh;
};

struct symtab *symtable;

struct symtab *symlook(char *symbol, void *data); 

#endif
