#ifndef __WALKER_H__
#define __WALKER_H__

#include "absyn.h"
#include "codegen.h"
#include "typecheck.h"

void walkTranslationUnit(TranslationUnit t);
void walkFunctionDefinition(FunctionDefinition f);
void walkDeclarator(Declarator d);
void walkCompoundStatement(CompoundStatement c);
void walkGrammarList(GrammarList g);
void walkStatement(Statement s);

#endif
