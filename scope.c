#include "scope.h"

Scope newScope(Scope parent) {
  Scope ret = (Scope)malloc(sizeof(struct scope_));
  ret->parent = parent;
  ret->symbolTable = NULL;
#ifdef MEMTRACE
  printf("New Scope at %p with parent at %p\n", ret, ret->parent);
#endif  
  return ret;
}

TypeCheckType findSymbol(Scope s, char *id) {
  TypeCheckType ret = NULL;
  printf("Looking up symbol %s\n", id);
  while(s && !ret) {
    ret = findType(&(s->symbolTable), id);
    s = s->parent;
  }
  return ret;
}

TypeCheckType addSymbolToScope(Scope s, char *id, TypeCheckType tt) {
  printf("Attempting to add symbol %s to scope %p\n", id, s);
  Symtab table = addSymbol(&(s->symbolTable), id, tt);
  if(table) {
    printf("Successful!\n");
    return table->type;
  }
  else
    return NULL;
}
