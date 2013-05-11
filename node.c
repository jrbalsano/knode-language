#include "node.h"

Node initNode() {
  Node n = (Node)malloc(sizeof(struct node));
  n->dictlist = initDict();
  n->edgecount = 0;
  return n;
}

void addEdge(Node a, Node b, Edge e) {
  //add edge to a's edgelist
  a->edgelist[a->edgecount] = e;
  e->aindex = a->edgecount;
  a->edgecount += 1;
  
  //add edge to b's edgelist
  b->edgelist[b->edgecount] = e;
  e->bindex = b->edgecount;
  b->edgecount += 1;
}

void removeEdge(Node n, Edge e) {
  Node o;
  int nindex;
  int oindex;
  //determine which node we are at relative to the edge: a or b
  if (n == e->a) {
    o = e->b;
    nindex = e->aindex;
    oindex = e->bindex;
  }
  else if (n == e->b) {
    o = e->a;
    nindex = e->bindex;
    oindex = e->aindex;
  }

  //get rid of edge in n's edgelist
  n->edgelist[nindex] = n->edgelist[n->edgecount - 1];
  n->edgecount -= 1;
  
  //get rid of edge in other's edgelist
  o->edgelist[oindex] = o->edgelist[o->edgecount - 1];
  o->edgecount -= 1;

  //update the aindex and bindex of the edge plugging the hole
  if (n == e->a) {
    n->edgelist[nindex]->aindex = nindex;
    o->edgelist[oindex]->bindex = oindex;
  }
  else if (n == e->b) {
    n->edgelist[nindex]->bindex = nindex;
    o->edgelist[oindex]->aindex = oindex;
  }
  
  //finally, set the edge free
  freeEdge(e);
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
  //free n's dictlist
  if (n->dictlist)
    freeDict(n->dictlist);
  
  //free n's edges...
  int i;
  for (i = 0; i < n->edgecount; i++) {
    removeEdge(n, n->edgelist[i]);
  }

  //finally, free n itself
  free(n);
}
