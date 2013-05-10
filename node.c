#include "node.h"

Node initNode() {
  Node n = (Node)malloc(sizeof(struct node));
  n->dictlist = initDict();
  return n;
}

void freeNode(Node n) {
  if (n->dictlist)
    freeDict(n->dictlist);
  free(n);
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
  Entry e = access(n->dictlist, key);
  return e->value.num;
}

double getDubFromNode(Node n, char *key) {
  Entry e = access(n->dictlist, key);
  return e->value.dub;
}

char *getStrFromNode(Node n, char *key) {
  Entry e = access(n->dictlist, key);
  return e->value.str;
}
