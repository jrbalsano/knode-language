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
    strncpy(symbolPointer->name, symbol, sizeof(symbolPointer->name));
    HASH_ADD_STR(symtable, name, symbolPointer);
    return symbolPointer;
}

//delete the symbol in the hash table that has the corresponding symbol
void deleteSymbol(char *symbol) {
    struct symtab *symbolPointer;
    HASH_FIND_STR(symtable, symbol, symbolPointer);
    if (symbolPointer) {
        HASH_DEL(symtable, symbolPointer);
        free(symbolPointer);
    }
}

void *storeData(void *data) {
    void *store = (void *)malloc(sizeof(*data));
    return store;
}

//iterate through the hash table and delete/free everything
void freeHashTable() {
    struct symtab *curr, *tmp;
    HASH_ITER(hh, symtable, curr, tmp) {
        HASH_DEL(symtable, curr);
        free(curr);
    }
}

