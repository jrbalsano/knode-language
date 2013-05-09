#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "symtable.h"
#include "typechecktype.h"

typedef struct scope_ *Scope;

struct scope_ {
  Scope parent;
  Symtab symbolTable;
};

TypeCheckType findSymbol(char *id);

void freeScope(Scope s);

#endif
