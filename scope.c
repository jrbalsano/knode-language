#include "scope.h"

Scope newScope(Scope parent) {
  Scope ret = (Scope)malloc(sizeof(struct scope_));
  printf("Creating new scope at %p, with parent %p\n", ret, parent);
  ret->parent = parent;
  ret->symbolTable = NULL;
  return ret;
}

TypeCheckType findSymbol(Scope s, char *id) {
  TypeCheckType ret = NULL;
  while(s && !ret) {
    ret = findType(s->symbolTable, id);
    s = s->parent;
  }
  return ret;
}

TypeCheckType addSymbolToScope(Scope s, char *id, TypeCheckType tt) {
  Symtab table = addSymbol(s->symbolTable, id, tt);
  if(table)
    return table->type;
  else
    return NULL;
}
