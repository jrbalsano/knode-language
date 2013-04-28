#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "./libs/uthash.h"

struct symtab {
    char *name;
    double value;
    UT_hash_handle hh;
};

struct symtab *symtable;

struct symtab *symlook(char *symbol); 

#endif
