#include "smartpointers.h"

String newString(int length) {
  String ret = (String)malloc(sizeof(struct string_));
  ret->count = (int *)malloc(sizeof(int));
  ret->pointer = (char *)malloc(sizeof(char *) * (length + 1));
  ret->pointer[0] = 0;
  *(ret->count) = 1;
  return ret;
}

char *getString(String p) {
  return p->pointer;
}

String copyString(String p) {
  String ret = (String)malloc(sizeof(struct string_));
  ret->count = p->count;
  ret->pointer = p->pointer;
  *(ret->count)++;
  return ret;
}

void freeString(String p) {
  if(--*(p->count) == 0) {
    free(p->count);
    free(p->pointer);
  }
  free(p);
}

SmartDict newDict() {
  SmartDict ret = (SmartDict)malloc(sizeof(struct dictPointer_));
  ret->count = (int *)malloc(sizeof(int));
  ret->pointer = initDict();
  *(ret->count) = 1;
  return ret;
}

Dict getDict(SmartDict p) {
  return p->pointer;
}

SmartDict copySmartDict(SmartDict p) {
  SmartDict ret = (SmartDict)malloc(sizeof(struct dictPointer_));
  ret->count = p->count;
  ret->pointer = p->pointer;
  *(ret->count)++;
  return ret;
}

void freeSmartDict(SmartDict p) {
  if(--*(p->count) == 0) {
    free(p->count);
    freeDict(p->pointer);
  }
  free(p);
}

SmartNode newNode() {
  SmartNode ret = (SmartNode)malloc(sizeof(struct nodePointer_));
  ret->count = (int *)malloc(sizeof(int));
  ret->pointer = initNode();
  *(ret->count) = 1;
  return ret;
}

Node getNode(SmartNode p) {
  return p->pointer;
}

SmartNode copySmartNode(SmartNode p) {
  SmartNode ret = (SmartNode)malloc(sizeof(struct nodePointer_));
  ret->count = p->count;
  ret->pointer = p->pointer;
  *(ret->count)++;
  return ret;
}

void freeSmartNode(SmartNode p) {
  if(--*(p->count) == 0) {
    free(p->count);
    freeNode(p->pointer);
  }
  free(p);
}

SmartEdge newEdge(SmartNode n1, SmartNode n2, int edge_dir) {
  SmartEdge ret = (SmartEdge)malloc(sizeof(struct edgePointer_));
  ret->count = (int *)malloc(sizeof(int));
  ret->pointer = initEdge();
  *(ret->count) = 1;
  return ret;
}

Edge getEdge(SmartEdge p) {
  return p->pointer;
}

SmartEdge copySmartEdge(SmartEdge p) {
  SmartEdge ret = (SmartEdge)malloc(sizeof(struct edgePointer_));
  ret->count = p->count;
  ret->pointer = p->pointer;
  *(ret->count)++;
  return ret;
}

void freeSmartEdge(SmartEdge p) {
  if(--*(p->count) == 0) {
    free(p->count);
    freeEdge(p->pointer);
  }
  free(p);
}
