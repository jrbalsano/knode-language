#include <stdlib.h>
#include "dict.h"

Dict initDict() {
  Dict d = (Dict)malloc(sizeof(struct dict));
  d->entries = NULL;
  return d;
}

/**
 * Checks through the entries of the dictionary to see if the entry exists and
 * returns the value for the key if it exists. Otherwise, it returns null.
 */
Entry getEntryForKey(Dict d, char *key) {
  //create a pointer to the entry that we want to get back
  Entry e = NULL;
  //try to find the value in our table
  HASH_FIND_STR(d->entries, key, e);
  //return the result of the lookup
  return e;
}

Entry addToDict(Dict d, int et, char *key, void *value) {
  Entry entry = (Entry)malloc(sizeof(struct entry));
  strncpy(entry->key, key, sizeof(entry->key));
  switch(et) {
    case echar:
      strncpy(entry->value.str, (char *)value, sizeof(entry->key));
      break;
    case eint:
      entry->value.num = *(int *)value;
      break;
    case edouble:
      entry->value.dub = *(double *)value;
      break;
  }
  HASH_ADD_STR(d->entries, key, entry);
  return entry;
}

void freeEntries(Entry entries) {
  struct entry *curr, *tmp;
  HASH_ITER(hh, entries, curr, tmp) {
    HASH_DEL(entries, curr);
    free(curr);
  }
}

void freeDict(Dict d) {
  freeEntries(d->entries);
  free(d); 
}
