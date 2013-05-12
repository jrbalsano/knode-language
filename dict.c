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

Entry addToDict(Dict d, int et, char *key, ...) {
  va_list ap;
  va_start(ap, key);
  Entry entry = (Entry)malloc(sizeof(struct entry));
  strncpy(entry->key, key, sizeof(entry->key));
  char *sval;
  char ival;
  char dval;
  switch(et) {
    case echar:
      sval = va_arg(ap, char *);
      strncpy(entry->value.str, sval, sizeof(entry->key));
      break;
    case eint:
      ival = va_arg(ap, int);
      entry->value.num = ival;
      break;
    case edouble:
      dval = va_arg(ap, double);
      entry->value.dub = dval;
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
