#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symtab *symlook(char *symbol) {
    //create a symbol pointer
    struct symtab *symbolPointer;
    //try to find the symbol in our table
    HASH_FIND_STR(symtable, symbol, symbolPointer);
    //if we find the symbol, then return the pointer to it
    if (symbolPointer) {
        return symbolPointer;
    } 
    //if we don't find the symbol, add it to the table and return the pointer
    symbolPointer = (struct symtab*)malloc(sizeof(struct symtab));
    symbolPointer->name = strdup(symbol);
    HASH_ADD_STR(symtable, name, symbolPointer);
    return symbolPointer;
}
