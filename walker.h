#ifndef __WALKER_H__
#define __WALKER_H__

#include "absyn.h"
#include "codegen.h"
#include "typecheck.h"

void walkTranslationUnit(TranslationUnit t, Scope s);

/**
 * Recursively walk a function definition, checking types and
 * generating code.
 */
void walkFunctionDefinition(FunctionDefinition f, Scope s);

/**
 * Recursively walks through a declarator, branching based
 * on whether or not the declarator has an argument list
 * and checking its types and generating the code.
 */
void walkDeclarator(Declarator d, Scope s);

/**
 * Walks a compound statement's statements and then checks
 * the overall types of the CS and generates its code.
 */
void walkCompoundStatement(CompoundStatement c, Scope s);

/**
 * Walks a grammarlist by walking each node. After walking all
 * the individual nodes, it checks types and generates code for
 * the entire list.
 */
void walkGrammarList(GrammarList g, Scope s);

/**
 * Walks a statement, branching based on type, and then based on
 * derivation, to check the proper types and then generate code.
 */
void walkStatement(Statement s, Scope scope);

/**
 * Checks out a parameter by walking its identifier and then
 * typechecking and generating code.
 */
void walkParameter(Parameter p, Scope s);

/**
 * Walks an expression branching based on type and then based on
 * derivation, to check the proper types and then generate code.
 */
void walkExpression(Expression e, Scope s);

/**
 * Checks out an identifiers types (basically registers them) and then
 * generates code for it.
 */
void walkIdentifier(Identifier i, Scope s);

#endif
