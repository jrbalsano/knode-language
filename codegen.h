#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include "absyn.h"
#include <stdio.h>
#include <string.h>

/************************************************
 * Translation Units
 ************************************************/
void translationUnitGenerateCode(TranslationUnit t);

/************************************************
 * Function Definitions
 ************************************************/
void functionDefinitionGenerateCode(FunctionDefinition f);

/************************************************
 * Declarators
 ************************************************/
void declaratorGenerateCode(Declarator d);

/************************************************
 * Compound Statements
 ************************************************/
void compoundStatementGenerateCode(CompoundStatement cs);

/************************************************
 * Grammar Lists
 ************************************************/
void expressionListGenerateCode(GrammarList g);
void statementListGenerateCode(GrammarList g);
void parameterListGenerateCode(GrammarList g);

/************************************************
 * Statements
 ************************************************/
/* Expression */
void expressionStatementGenerateCode(Statement s);
/* Declarations */
void declStatementGenerateCode(Statement s);
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
/* Edges */
void edgeCreationGenerateCode(Statement s);
void edgeStatementGenerateCode(Statement s);
/* Generic */
void statementGenerateCode(Statement s);

/************************************************
 * Parameters
 ************************************************/
void parameterGenerateCode(Parameter p);

/************************************************
 * Expressions
 ************************************************/
/**
 * This function should just take the code of e->sub1.e
 * and make the code of e. It's for cases where we convert
 * one expression to another type of expression without actually
 * adding any semantic meaning.
 */
void passupExpressionCode(Expression e);
void postfixIdentifierGenerateCode(Expression e);
void postfixDecrementGenerateCode(Expression e);
void postfixIncrementGenerateCode(Expression e);
void postfixArgumentGenerateCode(Expression e);
void postfixBracketGenerateCode(Expression e);

void unaryExpressionGenerateCode(Expression e);

void castTypedExpressionGenerateCode(Expression e);

void multExpressionGenerateCode(Expression e);

void addExpressionGenerateCode(Expression e);

void relatExpressionGenerateCode(Expression e);

void eqExpressionGenerateCode(Expression e);

void condExpressionGenerateCode(Expression e);

void assignmentInitExpressionGenerateCode(Expression e);
void edgeExpressionGenerateCode(Expression e);
void assignmentExpressionGenerateCode(Expression e);

void primaryExpressionGenerateCode(Expression e);

void functionExpressionGenerateCode(Expression e);

void twoExpressionGenerateCode(Expression e);


void identifierGenerateCode(Identifier i);


/************************************************
 * Code Generating
 ************************************************/
/**
 * Anytime you generate code in any of the above functions you should NOT
 * be setting that generated code to the code of a node in the abstract syntax
 * tree. Rather, deal with stack-allocated strings within your method until you're
 * ready to set the AST node's code to a string. Then, set it to the return value of
 * this function, called on the string you were going to use. This will automatically
 * heap allocating the string for you.
 */
char *getAllocatedString(char *s);

/**
 * Gets a null string if there is no string in s and returns that instead.
 */
char *getValidString(char *s);
#endif

