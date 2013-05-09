#include <stdlib.h>
#include "dict.h"

/**
 * Checks through the entries of the dictionary to see if the entry exists and
 * returns the value for the key if it exists. Otherwise, it returns null.
 */
Entry access(Dict d, char *key) {
  //create a pointer to the entry that we want to get back
  Entry e = NULL;
  //try to find the value in our table
  HASH_FIND_STR(d->entries, key, e);
  //return the result of the lookup
  return e;
}

void freeDict(Dict dictionary) {

}
