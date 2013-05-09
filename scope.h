#ifndef __SCOPE_H__
#define __SCOPE_H__

#include "symtable.h"
#include "typechecktype.h"

typedef struct scope_ *Scope;

struct scope_ {
  Scope parent;
  Symtab symbolTable;
};

Scope newScope(Scope parent);

/**
 * Checks to see if a symbol exists within a scope. First checks
 * the scope and then all the outer scopes of that scope. Return
 * value of null indicates that the symbol does not exist.
 */
TypeCheckType findSymbol(Scope s, char *id);

#endif
