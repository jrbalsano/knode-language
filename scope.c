#include "scope.h"

Scope newScope(Scope parent) {
  Scope ret = (Scope)malloc(sizeof(struct scope_));
  ret->parent = parent;
  ret->symbolTable = NULL;
}

TypeCheckType findSymbol(Scope s, char *id) {
  TypeCheckType ret = NULL;
  while(s && !ret) {
    ret = findType(s->symbolTable, id);
    s = s->parent;
  }
  return ret;
}

void freeScope(Scope s);
