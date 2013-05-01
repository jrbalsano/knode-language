#ifndef __ABSYN_H__
#define __ABSYN_H__

#include <stdio.h>
#include "symtable.h"

/**
 * Abstract Syntax Tree for Knode
 * This code creates the structs used for our grammar.
 */
typedef struct expression_ *Expression;
typedef struct identifier_ *Identifier;
typedef struct declarator_ *Declarator;
typedef struct statement_ *Statement;
typedef struct functionDefinition_ *FunctionDefinition;
typedef struct compoundStatement_ *CompoundStatement; 
typedef struct grammarList_ *GrammarList;
typedef struct grammarNode_ *GrammarNode;
typedef struct translationUnit_ *TranslationUnit;
typedef struct parameter_ *Parameter;

struct expression_ {
  enum {function, unary, postfix, primary, string, cast, mult, add, relat, eq, cond} type;
  union {
    Expression e;
    Identifier i;
    GrammarList l;
    char *s;
    int typnam;
  } sub1;
  union {
    Expression e;
    Identifier i;
    GrammarList l;
  } sub2;
  union {
    enum{none = 0, postincr, postdecr, bracket, identifier, arg} postfix;
    enum{unary_none, preincr, predecr, positive = '+', negative = '-', negate = '!', clone = '*'} unary;
    enum{cast_none, typed} cast;
    enum{mult_none, times = '*', divide = '/', mod = '%'} mult;
    enum{add_none, plus = '+', minus = '-'} add;
    enum{relat_none, less = '<', greater = '>', le, ge} relat;
    enum{eq_none, equal, notequal} eq;
    enum{cond_none, cond_or, cond_and} cond;
  } deriv;
};

struct identifier_ {
  char *symbol;
  struct symtab *sp;
};
struct declarator_ {
  Identifier name;
  GrammarList p; //A list of parameters
};
struct statement_ {
  enum {expression} type;
  union {
    Expression e;
  } sub;
};
struct parameter_ {
	int type;
	Identifier i;
};
struct functionDefinition_ {
  Declarator d;
  CompoundStatement cs;
};
struct compoundStatement_ {
  GrammarList dlist; //A list of declarations
  GrammarList sList; //A list of statements
};
struct translationUnit_ {
  FunctionDefinition f;
};
struct grammarList_ {
  enum {argument, statement,parameterList} type;
  GrammarNode head;
};
struct grammarNode_ {
  GrammarNode next;
  void *data;
};

void addFront(GrammarList g, void *data);
TranslationUnit getTranslationUnit(FunctionDefinition fd);
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
Declarator declaratorId(Identifier id);
Declarator getDeclarator(Identifier id, GrammarList pList);
CompoundStatement newCompoundStatement(GrammarList sList);
GrammarList newStatementList(Statement s);
GrammarList newParameterList(Parameter p);
Parameter getTypedParameter(int typname, Identifier i);
GrammarList appendToPList(GrammarList pList,Parameter param);
Statement getExpressionStatement(Expression e);
Expression getFunctionExpression(Identifier id, GrammarList argExpList);
Expression getPrimaryStringExpression(char *s);
GrammarList newArgumentExpressionList(Expression e);
Identifier getIdentifier(char *s);
Expression getPrimaryIdentifierExpression(Identifier id);
Expression getPostfixExpression(Expression e1);
Expression getPostfixBracketExpression(Expression e1, Expression e2);
Expression getPostfixIdentifierExpression(Expression e, Identifier id);
Expression getPostfixIncr(Expression e);
Expression getPostfixDecr(Expression e);
Expression getPostfixArgumentExpression(Expression e1, GrammarList argList);
void freeParameter(Parameter p);
Expression getUnaryExpression(Expression e);
Expression getUnaryIncr(Expression e);
Expression getUnaryDecr(Expression e);
Expression getUnarySingleOp(char c, Expression e);
Expression getCastExpression(Expression e);
Expression getTypedCast(int token, Expression e);
Expression getMultExpression(Expression e);
Expression getMultiplyExpression(Expression e1, char c, Expression e2);
Expression getAdditiveExpression(Expression e1);
Expression getAddExpression(Expression e1, char c, Expression e2);
Expression getRelatExpression(Expression e);
Expression getSingleCharRelat(Expression e1, char c, Expression e2);
Expression getLeRelat(Expression e1, Expression e2);
Expression getGeRelat(Expression e1, Expression e2);
Expression getEqExpression(Expression e);
Expression getEqual(Expression e1, Expression e2);
Expression getNotEqual(Expression e1, Expression e2);
Expression getAndExpression(Expression e);
Expression getAnd(Expression e1, Expression e2);
void freeTranslationUnit(TranslationUnit t); 
void freeFunctionDefinition(FunctionDefinition f);
void freeDeclarator(Declarator d);
void freeCompoundStatement(CompoundStatement c);
void freeGrammarList(GrammarList g);
void freeStatement(Statement s);
void freeExpression(Expression e);
void freeIdentifier(Identifier i);
#endif
