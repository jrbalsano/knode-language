#include "node.h"

Node initNode() {
  Node n = (Node)malloc(sizeof(struct node));
  n->dictlist = initDict();
  //n->edgelist = NULL;
  n->edgecount = 0;
  return n;
}

void addEdge(Node n, Edge e) {
  n->edgelist[n->edgecount] = e;
  e->aindex = n->edgecount;
  n->edgecount += 1;
}

void addIntToNode(Node n, char *key, int value) {
  int tmp = value;
  int *tmpp = &tmp;
  addToDict(n->dictlist, eint, key, tmpp);
}

void addDubToNode(Node n, char *key, double value) {
  double tmp = value;
  double *tmpp = &tmp;
  addToDict(n->dictlist, edouble, key, tmpp);
}

void addStrToNode(Node n, char *key, char *value) {
  addToDict(n->dictlist, echar, key, value);
}

int getIntFromNode(Node n, char *key) {
  Entry e = getEntryForKey(n->dictlist, key);
  return e->value.num;
}

double getDubFromNode(Node n, char *key) {
  Entry e = getEntryForKey(n->dictlist, key);
  return e->value.dub;
}

char *getStrFromNode(Node n, char *key) {
  Entry e = getEntryForKey(n->dictlist, key);
  return e->value.str;
}

void freeNode(Node n) {
  if (n->dictlist)
    freeDict(n->dictlist);
  free(n);
}
