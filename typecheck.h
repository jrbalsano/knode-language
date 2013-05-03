#ifndef __TYPECHECK_H__
#define __TYPECHECK_H__

#include "absyn.h"
#include <stdio.h>

void functionDefinitionTypeCheck(FunctionDefinition f);
void declaratorTypeCheck(Declarator d);
void translationUnitTypeCheck(TranslationUnit t);
void compoundStatementTypeCheck(CompoundStatement cs);
void expressionListTypeCheck(GrammarList g);
void statementListTypeCheck(GrammarList g);
void parameterListTypeCheck(GrammarList g);

#endif
