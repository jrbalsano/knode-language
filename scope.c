#include "scope.h"

Scope newScope(Scope parent) {
  Scope ret = (Scope)malloc(sizeof(struct scope_));
  ret->parent = parent;
  ret->symbolTable = NULL;
  return ret;
}

TypeCheckType findSymbol(Scope s, char *id) {
  TypeCheckType ret = NULL;
  while(s && !ret) {
    ret = findType(&(s->symbolTable), id);
    s = s->parent;
  }
  return ret;
}

TypeCheckType addSymbolToScope(Scope s, char *id, TypeCheckType tt) {
  Symtab table = addSymbol(&(s->symbolTable), id, tt);
  if(table)
    return table->type;
  else
    return NULL;
}
