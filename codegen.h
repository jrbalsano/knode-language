#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include "absyn.h"
#include <stdio.h>

void functionDefinitionGenerateCode(FunctionDefinition f);

void declaratorGenerateCode(Declarator d);

void translationUnitGenerateCode(translationUnit t);

void compoundStatementGenerateCode(CompoundStatement cs);

void expressionListGenerateCode(GrammarList g);

/****
 * Statements
 ****/
/* Iteration */
void forStatementGenerateCode(Statement s);
void whileStatementGenerateCode(Statement s);
/* Selection */
void ifStatementGenerateCode(Statement s);
void ifelseStatementGenerateCode(Statement s);
/* Dictlist */
void dictlistGenerateCode(Statement s);
/* Dictionaries */
void dictDefinitionsGenerateCode(Statement s);
void dictGenerateCode(Statement s);
/* Nodes */
void nodeCreationGenerateCode(Statement s);
void nodeAssignmentGenerateCode(Statement s);
void nodeDictionaryGenerateCode(Statement s);
/* Generic */
void statementGenerateCode(Statement s);

/**
 * This function should just take the code of e->sub1.e
 * and make the code of e. It's for cases where we convert
 * one expression to another type of expression without actually
 * adding any semantic meaning.
 */
void passupExpressionCode(Expression e);
void postfixIdentifierGenerateCode(Expression e);
void postfixDecrementGenerateCode(Expression e);
void postfixIncrementGenerateCode(Expresion e);
void postfixArgumentGenerateCode(Expression e);
void postfixArgumentGenerateCode(Expression e);

void unaryExpressionGenerateCode(Expression e);

void castTypedExpressionGenerateCode(e);

void multExpressionGenerateCode(Expression e);

void addExpressionGenerateCode(Expression e);

void relatExpressionGenerateCode(Expression e);

void eqExpressionGenerateCode(Expression e);

void assignmentInitExpressionGenerateCode(Expression e);
void edgeExpressionGenerateCode(Expression e);
void assignmentExpressionGenerateCode(Expression e);

void primaryExpressionGenerateCode(Expression e);

void functionExpressionGenerateCode(Expression e);

void twoExpressionGenerateCode(Expression e);


void identifierGenerateCode(Identifier i);
#endif

