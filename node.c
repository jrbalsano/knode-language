#include "node.h"

Node initNode() {
  Node n = (Node)malloc(sizeof(struct node));
  n->dictlist = initDict();
  n->edgecount = 0;
  return n;
}

void addSmartEdge(SmartNode sa, SmartNode sb, SmartEdge se) {
  //add edge to a's edgelist
  getNode(sa)->edgelist[getNode(sa)->edgecount] = copySmartEdge(se);
  getEdge(se)->aindex = getNode(sa)->edgecount;
  getNode(sa)->edgecount += 1;
  
  //add edge to b's edgelist
  getNode(sb)->edgelist[getNode(sb)->edgecount] = copySmartEdge(se);
  getEdge(se)->bindex = getNode(sb)->edgecount;
  getNode(sb)->edgecount += 1;

  freeSmartNode(sa);
  freeSmartNode(sb);
  freeSmartEdge(se);
}

void removeSmartEdge(SmartEdge se) {
  SmartNode so = getEdge(se)->a;
  SmartNode sn = getEdge(se)->b;
  int nindex = getEdge(se)->bindex;
  int oindex = getEdge(se)->aindex;
  //get rid of edge in n's edgelist
  freeSmartEdge(getNode(sn)->edgelist[nindex]);
  getNode(sn)->edgelist[nindex] = getNode(sn)->edgelist[getNode(sn)->edgecount - 1];
  getNode(sn)->edgecount -= 1;
  
  //get rid of edge in other's edgelist
  freeSmartEdge(getNode(so)->edgelist[oindex]);
  getNode(so)->edgelist[oindex] = getNode(so)->edgelist[getNode(so)->edgecount - 1];
  getNode(so)->edgecount -= 1;
  
  //finally, set the edge free
  freeSmartEdge(se);
}

void addIntToSmartNode(SmartNode sn, char *key, int value) {
  int tmp = value;
  int *tmpp = &tmp;
  addToDict(getNode(sn)->dictlist, eint, key, tmpp);
  freeSmartNode(sn);
}

void addDubToSmartNode(SmartNode sn, char *key, double value) {
  double tmp = value;
  double *tmpp = &tmp;
  addToDict(getNode(sn)->dictlist, edouble, key, tmpp);
  freeSmartNode(sn);
}

void addStrToSmartNode(SmartNode sn, char *key, char *value) {
  addToDict(getNode(sn)->dictlist, echar, key, value);
  freeSmartNode(sn);
}

int getIntFromSmartNode(SmartNode sn, char *key) {
  Entry e = getEntryForKey(getNode(sn)->dictlist, key);
  freeSmartNode(sn);
  return e->value.num;
}

double getDubFromSmartNode(SmartNode sn, char *key) {
  Entry e = getEntryForKey(getNode(sn)->dictlist, key);
  freeSmartNode(sn);
  return e->value.dub;
}

char *getStrFromSmartNode(SmartNode sn, char *key) {
  Entry e = getEntryForKey(getNode(sn)->dictlist, key);
  freeSmartNode(sn);
  return e->value.str;
}

void freeNode(Node n) {
  //free n's dictlist
  if (n->dictlist)
    freeDict(n->dictlist);
  
  //free n's edges...
  int i;
  for (i = 0; i < n->edgecount; i++) {
    removeSmartEdge(n->edgelist[i]);
  }

  //finally, free n itself
  free(n);
}
