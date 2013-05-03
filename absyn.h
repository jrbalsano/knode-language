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

#include "yacc.tab.h"

struct expression_ {
  enum {none = 0, function, unary, postfix, primary, string, cast, mult, add, relat, eq, cond, assignment} type;
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
    Expression e;
    Identifier i;
    GrammarList l;
  } sub3;
  union {
    enum{postfix_none = none, postincr, postdecr, bracket, identifier, arg} postfix;
    enum{unary_none = none, preincr, predecr, positive = '+', negative = '-', negate = '!', clone = '*'} unary;
    enum{cast_none = none, typed} cast;
    enum{mult_none = none, times = '*', divide = '/', mod = '%'} mult;
    enum{add_none = none, plus = '+', minus = '-'} add;
    enum{relat_none = none, less = '<', greater = '>', le, ge} relat;
    enum{eq_none = none, equal, notequal} eq;
    enum{gen_none = none, comma = ','} none;
    enum{cond_none = none, cond_or, cond_and} cond;
    enum{assign_none = none, init, eq_assign, multeq = MULTEQ, diveq = DIVEQ, pluseq = PLUSEQ, minuseq = MINUSEQ, modeq = MODEQ } assign;
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
  enum {statement_none = none, expression, iteration} type;
  union {
    Expression e;
    Statement s;
    struct {
      Expression e1;
      Expression e2;
      Expression e3;
    } forloop;
  } sub1;
  union{
    CompoundStatement cs;
  } sub2;
  enum {forIter,whileIter} iterationtype;
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
  enum {argument, statement,parameterList,expressionList} type;
  GrammarNode head;
};
struct grammarNode_ {
  GrammarNode next;
  void *data;
};

TranslationUnit getTranslationUnit(FunctionDefinition fd);

FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
Declarator declaratorId(Identifier id);
Declarator getDeclarator(Identifier id, GrammarList pList);

GrammarList newStatementList(Statement s);
GrammarList newParameterList(Parameter p);
GrammarList newArgumentExpressionList(Expression e);
GrammarList appendToPList(GrammarList pList,Parameter param);
GrammarList addFront(GrammarList g, void *data);

Parameter getTypedParameter(int typname, Identifier i);

CompoundStatement newCompoundStatement(GrammarList sList);

Statement getExpressionStatement(Expression e);
Statement getStatement(Statement s);
Statement newWhileStatement(Expression e, CompoundStatement cs);
Statement newForStatement(Expression e1, Expression e2,Expression e3,CompoundStatement cs);

Identifier getIdentifier(char *s);

Expression getFunctionExpression(Identifier id, GrammarList argExpList);
Expression getPrimaryStringExpression(char *s);
Expression getPrimaryIdentifierExpression(Identifier id);
Expression getPostfixExpression(Expression e1);
Expression getPostfixBracketExpression(Expression e1, Expression e2);
Expression getPostfixIdentifierExpression(Expression e, Identifier id);
Expression getPostfixIncr(Expression e);
Expression getPostfixDecr(Expression e);
Expression getPostfixArgumentExpression(Expression e1, GrammarList argList);
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
Expression getExpression(Expression e);
Expression getExpressionAssignmentExpression(Expression e1, Expression e2);
Expression getAndExpression(Expression e);
Expression getAnd(Expression e1, Expression e2);
Expression getOrExpression(Expression e);
Expression getOr(Expression e1, Expression e2);
Expression getCond(Expression e);
Expression getAssign(Expression e);
Expression getTokenizedAssignment(Expression e1, int op, Expression e2);
Expression getAssignment(Expression e1, Expression e2);
Expression getInit(int token, Identifier i, Expression e);

void freeTranslationUnit(TranslationUnit t); 
void freeFunctionDefinition(FunctionDefinition f);
void freeDeclarator(Declarator d);
void freeCompoundStatement(CompoundStatement c);
void freeGrammarList(GrammarList g);
void freeStatement(Statement s);
void freeExpression(Expression e);
void freeIdentifier(Identifier i);
void freeParameter(Parameter p);

#endif
