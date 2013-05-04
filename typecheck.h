#ifndef __TYPECHECK_H__
#define __TYPECHECK_H__

#include "absyn.h"
#include <stdio.h>

/************************************************
 * TranslationUnits
 ************************************************/
/**
 * This function likely doesn't need to do anything so lets
 * just leave it here for now in case we need it but don't implement
 * it.
 */
void translationUnitTypeCheck(TranslationUnit t);

/************************************************
 * FunctionDefinitions
 ************************************************/
/**
 * This function should probably make sure that its function type and
 * return type match up. Any other type inconsistencies are hard to do
 * anything about.
 */
void functionDefinitionTypeCheck(FunctionDefinition f);

/************************************************
 * Declarators
 ************************************************/

/**
 * This need only figure out what kind of declarator it is - what its
 * identifier is, what kind of parameters it has, and what its return
 * type should be.
 */
void declaratorTypeCheck(Declarator d);

/************************************************
 * Compounds Statements
 ************************************************/
/**
 * This probably just needs to pass up a type for whatever kind
 * of grammar list it has.
 */
void compoundStatementTypeCheck(CompoundStatement cs);

/************************************************
 * Grammar Lists
 ************************************************/

/**
 * Doesn't need to do anything?
 */ 
void expressionListTypeCheck(GrammarList g);

/**
 * Doesn't need to do anything?
 */
void statementListTypeCheck(GrammarList g);

/**
 * Should pick up some sort of combined type, like a list
 * of types, to denote the parameters.
 */
void parameterListTypeCheck(GrammarList g);

/************************************************
 * Statements
 ************************************************/

/**
 * Checks to make sure that each statement that is in
 * its compound statement is a valid statement, and not
 * a dictionary definition for example. Need not be recursive.
 * Also checks the middle expression to make sure it types to
 * boolean or indeterminable.
 */
void forStatementTypeCheck(Statement s);

/**
 * 
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
