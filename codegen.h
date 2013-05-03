#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include "absyn.h"
#include <stdio.h>

void functionDefinitionGenerateCode(FunctionDefinition f);
void declaratorGenerateCode(Declarator d);
void translationUnitGenerateCode(translationUnit t);
void compoundStatementGenerateCode(CompoundStatement cs);
void expressionListGenerateCode(GrammarList g);


#endif

