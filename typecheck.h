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
 * Checks to make sure that each statement in its compound statement
 * is an evaluatable statement, and not for example a dictionary definition.
 * Also makes sure that the while condition is a boolean or indeterminable.
 */
void whileStatementTypeCheck(Statement s);

/**
 * Checks for valid sub-compoundstatements and then makes sure that its
 * condition is either a boolean or indeterminable.
 */
void ifStatementTypeCheck(Statement s);

/**
 * Checks for valid sub-compoundstatements and then makes sure that its
 * condition is either a boolean or indeterminable.
 */
void ifelseStatementTypeCheck(Statement s);

/**
 * Doesn't need to do anything?
 */
void dictlistTypeCheck(Statement s);

/**
 * Checks to make sure all the statements in its compounds statement
 * are dictlists and nothing else. Also sets its type to dict.
 */
void dictDefinitionsTypeCheck(Statement s);

/**
 * Sets its type to dict
 */
void dictTypeCheck(Statement s);

/**
 * Sets its type to node
 */
void nodeCreationTypeCheck(Statement s);

/**
 * Sets its type to node and checks to make sure the operator is an equals sign
 * and that on the other side of the equals sign is a node type expression.
 */
void nodeAssignmentTypeCheck(Statement s);

/**
 * Sets its type to node and makes sure that its compound statement's statements
 * are all dictlists statements.
 */

void nodeDictionaryTypeCheck(Statement s);
/**
 * Just carries up the type of its sub-statement.
 */
void statementTypeCheck(s);

/************************************************
 * Expressions
 ************************************************/
/**
 * Just passes up the type of the single sub-statement
 * to the this statement.
 */
void passupExpressionType(Expression e);

/**
 * Sets its type to the type of its identifier after
 * first checking that the postfix expression on the left
 * is a '.' operable postfix expression type (node, dict, edge,
 * undeterminable)
 */
void postfixIdentifierTypeCheck(Expression e);

/**
 * Sets its type to integer after checking to make sure
 * the sub expression is type integer.
 */
void postfixDecrementTypeCheck(Expression e);

/**
 * Sets its type to integer after checking to make sure
 * the sub expression is type integer.
 */
void postfixIncrementTypeCheck(Expresion e);

/**
 * Sets its type to whatever type the function its trying to be
 * should return. If the function its trying to be is indeterminable
 * then it should be indeterminable.
 */
void postfixArgumentTypeCheck(Expression e);

/**
 * Checks to make sure either a) the bracketed expression
 * is an integer and the left expression is an array type
 * or b) the bracketed expression is a string (or convertible
 * to string)
 */
void postfixBracketTypeCheck(Expression e);

/**
 * Checks to make sure the sub expression is operable on by the
 * operator.
 */
void unaryExpressionTypeCheck(Expression e);

/**
 * Checks the two types to make sure its a valid cast and then
 * types the expression to the casted type.
 */
void castTypedExpressionTypeCheck(Expression e);

/**
 * Checks to make sure the two expressions are int or double
 * and then should use the normal rules to resolve whether or not
 * the resulting expression is int or double. Indeterminable is also
 * an option.
 */
void multExpressionTypeCheck(Expression e);

/**
 * Checks to make sure the two expressions are int or double
 * and then should use the normal rules to resolve whether or not
 * the resulting expression is int or double. Indeterminable is also
 * an option.
 */
void addExpressionTypeCheck(Expression e);

/**
 * If we're talking > or < comparators then check again for number types.
 * Don't forget about indeterminables and set the resulting expression to
 * boolean type.
 */
void relatExpressionTypeCheck(Expression e);

/**
 * Make sure two expressions are of castably comparable types and then set
 * the resulting expression to boolean.
 */
void eqExpressionTypeCheck(Expression e);

/**
 * Check to make sure right hand side type matches left hand side type
 * and then set the resulting expression type to the same type as the
 * expression.
 */
void assignmentInitExpressionTypeCheck(Expression e);

/**
 * Check to make sure that both sides are node types and then set the
 * expression type to an array of edges.
 */
void edgeExpressionTypeCheck(Expression e);

/**
 * Check to make sure left hand side and right hand side are the same type
 * or castable to the same type and then set the expression type to the lhs
 * type.
 */
void assignmentExpressionTypeCheck(Expression e);

/**
 * Sets its type to the appropriate type based on the kind of primary expression
 * it is.
 */ 
void primaryExpressionTypeCheck(Expression e);

/**
 * Sets its type to function the return type of the function its calling.
 */
void functionExpressionTypeCheck(Expression e);

/**
 * Sets its type to the list type of the two expressions its composed of?
 */
void twoExpressionTypeCheck(Expression e);

/************************************************
 * Identifiers
 ************************************************/
/**
 * Sets its type to the type of the variable it represents. May or may not be knowable.
 */
void identifierTypeCheck(Identifier i);

/************************************************
 * Types
 ************************************************/
/**
 * Returns a new TypeCheckType object that's been malloc'ed and set to the proper type.
 */
void getTypeCheckType(int type);

/**
 * Returns 1 if t1 is exactly the same type as t2. Return -1 if they are matches
 * because of an indeterminable type. Return 0 otherwise. Easily
 * done recursively (think pattern matcher)
 */
int exactTypeMatch(TypeCheckType t1, TypeCheckType t2);

/**
 * Returns 1 if t1 is exactly the same type as t2. Return -1 if they are matches
 * because of an indeterminable type. Return 2 if they are matchable via an implicit
 * cast such as int or double to string, or int to double. Return 0 otherwise. Easily
 * done recursively (think pattern matcher)
 */
int castTypeMatch(TypeCheckType t1, TypeCheckType t2);

#endif
