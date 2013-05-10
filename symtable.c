#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symtab symlook(char *symbol, Symtab table) {
    //create a symbol pointer
    struct symtab *symbolPointer;
    //try to find the symbol in our table
    HASH_FIND_STR(table, symbol, symbolPointer);
    //if we find the symbol, then return the pointer to it
    if (symbolPointer) {
        return symbolPointer;
    } 
    //if we don't find the symbol, add it to the table and return the pointer
    symbolPointer = (struct symtab*)malloc(sizeof(struct symtab));
    strncpy(symbolPointer->name, symbol, sizeof(symbolPointer->name));
    HASH_ADD_STR(table, name, symbolPointer);
    return symbolPointer;
}

/**
 * Checks to see if a symbol exists in the table already and adds it if it
 * doesn't. Returns the table record if it was successfully added, or NULL
 * otherwise.
 */
Symtab addSymbol(Symtab *table, char *symbol, TypeCheckType tt) {
  //Create a pointer to store the sumbol that we get back.
  Symtab lookupResult = NULL;
  //try to find the symbol in our table
  HASH_FIND_STR(*table, symbol, lookupResult);
  if(!lookupResult) {
    lookupResult = (Symtab)malloc(sizeof(struct symtab));
    strncpy(lookupResult->name, symbol, sizeof(lookupResult->name));
    lookupResult->type = tt;
    HASH_ADD_STR(*table, name, lookupResult);
    return lookupResult;
  }
  return NULL;
}

TypeCheckType findType(Symtab *table, char *symbol) {
  //Create a pointer to store the symbol that we get back in.
  Symtab lookupResult = NULL;
  //try to find the symbol in our table
  HASH_FIND_STR(*table, symbol, lookupResult);
  //get space for the type
  TypeCheckType result = NULL;
  if(lookupResult) {
    result = lookupResult->type;
  }
  return result;
}

//delete the symbol in the hash table that has the corresponding symbol
void deleteSymbol(Symtab table, char *symbol) {
    struct symtab *symbolPointer;
    HASH_FIND_STR(table, symbol, symbolPointer);
    if (symbolPointer) {
        HASH_DEL(table, symbolPointer);
        free(symbolPointer);
    }
}

//iterate through the hash table and delete/free everything
void freeHashTable(Symtab table) {
    struct symtab *curr, *tmp;
    HASH_ITER(hh, table, curr, tmp) {
        HASH_DEL(table, curr);
        free(curr);
    }
}

