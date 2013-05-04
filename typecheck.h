#ifndef __TYPECHECK_H__
#define __TYPECHECK_H__

#include "absyn.h"
#include <stdio.h>

/************************************************
 * TranslationUnits
 ************************************************/
void translationUnitTypeCheck(TranslationUnit t);

/************************************************
 * FunctionDefinitions
 ************************************************/
void functionDefinitionTypeCheck(FunctionDefinition f);

/************************************************
 * Declarators
 ************************************************/
void declaratorTypeCheck(Declarator d);

/************************************************
 * Compounds Statements
 ************************************************/
void compoundStatementTypeCheck(CompoundStatement cs);

/************************************************
 * Grammar Lists
 ************************************************/
void expressionListTypeCheck(GrammarList g);
void statementListTypeCheck(GrammarList g);
void parameterListTypeCheck(GrammarList g);

/************************************************
 * Statements
 ************************************************/
/* Iteration */
void forStatementTypeCheck(Statement s);
void whileStatementTypeCheck(Statement s);
/* Selection */
void ifStatementTypeCheck(Statement s);
void ifelseStatementTypeCheck(Statement s);
/* Dictionaries */
void dictlistTypeCheck(Statement s);
void dictDefinitionsTypeCheck(Statement s);
void dictTypeCheck(Statement s);
/* Nodes */
void nodeCreationTypeCheck(Statement s);
void nodeAssignmentTypeCheck(Statement s);
void nodeDictionaryTypeCheck(Statement s);
/* Statement */
void statementTypeCheck(s);

/************************************************
 * Expressions
 ************************************************/
void passupExpressionType(Expression e);
void postfixIdentifierTypeCheck(Expression e);
void postfixDecrementTypeCheck(Expression e);
void postfixIncrementTypeCheck(Expresion e);
void postfixArgumentTypeCheck(Expression e);
void postfixArgumentTypeCheck(Expression e);

void unaryExpressionTypeCheck(Expression e);

void castTypedExpressionTypeCheck(Expression e);

void multExpressionTypeCheck(Expression e);

void addExpressionTypeCheck(Expression e);

void relatExpressionTypeCheck(Expression e);

void eqExpressionTypeCheck(Expression e);

void assignmentInitExpressionTypeCheck(Expression e);
void edgeExpressionTypeCheck(Expression e);
void assignmentExpressionTypeCheck(Expression e);

void primaryExpressionTypeCheck(Expression e);

void functionExpressionTypeCheck(Expression e);

void twoExpressionTypeCheck(Expression e);

/************************************************
 * Identifiers
 ************************************************/
void identifierTypeCheck(Identifier i);
#endif
