#ifndef __SMARTPOINTERS_H__
#define __SMARTPOINTERS_H__

#include <stdlib.h>

typedef struct string_ *String;
typedef struct dictPointer_ *SmartDict;
typedef struct nodePointer_ *SmartNode;
typedef struct edgePointer_ *SmartEdge;

#include "dict.h"
#include "node.h"
#include "edge.h"

struct string_ {
  int *count;
  char *pointer;
};

struct dictPointer_ {
  int *count;
  Dict pointer;
};

struct nodePointer_ {
  int *count;
  Node pointer;
};

struct edgePointer_ {
  int *count;
  Edge pointer;
};

/**
 * Allocates a new smartpointer for char*'s of a certain length,
 * initializes its values, and initializes/allocates a new char *.
 */
String newString(int length);

/**
 * Gets the char * that a String represents
 */
char *getString(String p);

/**
 * Makes a new smartpointer to the same string as a previous smart
 * pointer, s.
 */
String copyString(String p);

/**
 * Frees the space taken by this smartpointer, and if its the last
 * smartpointer pointing to a particular char*, free's that char *
 * as well.
 */
void freeString(String p);

SmartDict newSmartDict();

Dict getDict(SmartDict p);

SmartDict copySmartDict(SmartDict p);

void freeSmartDict(SmartDict p);

SmartNode newSmartNode();

Node getNode(SmartNode p);

SmartNode copySmartNode(SmartNode p);

void freeSmartNode(SmartNode p);

SmartEdge newSmartEdge();

Edge getEdge(SmartEdge p);

SmartEdge copySmartEdge(SmartEdge p);

void freeSmartEdge(SmartEdge p);

#endif
