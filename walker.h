#ifndef __WALKER_H__
#define __WALKER_H__

#include "absyn.h"

void walkTranslationUnit(TranslationUnit t);
void walkFunctionDefinition(FunctionDefinition f);
void walkDeclarator(Declarator d);
void walkCompoundStatement(CompoundStatement c);
void walkGrammarList(GrammarList g);

#endif
