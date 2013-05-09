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
typedef struct typeCheckType_ *TypeCheckType;

#include "yacc.tab.h"

/**
 * Defines a structure for the type of a node in the tree to be used while typechecking. Indeterminable
 * is reserved for those situations where the nature of knode makes it impossible to determine the type.
 * If at all possible try to avoid the use of indeterminable because those will cause headaches during
 * code generation.
 *
 * int, double, string, char, node, edge, and dict should all be fairly straightforward types.
 *
 * For arrays, set "ar_sub" to be another TypeCheckType of the type the array is. If its an array of
 * arrays then "sub" should be another array_ type with another sub and so on.
 *
 * For functions, use fn_sub, with the first fn_sub being the return type of the function and each
 * subsequent fn_sub being the type of each argument. In the event that an argument is an array, use
 * the ar_sub to denote its type as mentioned above.
 */
struct typeCheckType_ {
  enum {indeterminable, int_, double_, string_, char_, node_, edge_, dict_, function_, array_} base;
  TypeCheckType ar_sub;
  TypeCheckType fn_sub;
};

struct expression_ {
  TypeCheckType tt;
  char *code;
  enum {none = 0, function, unary, postfix, primary, string, cast, mult, add, relat, eq, cond, assignment, decl} type;
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
    enum{assign_none = none, init, eq_assign, multeq = MULTEQ, diveq = DIVEQ,
      pluseq = PLUSEQ, minuseq = MINUSEQ, modeq = MODEQ, assign_left = LEFTEDGE,
      assign_right = RIGHTEDGE, assign_both = BOTHEDGE, assign_all = ALLEDGE } assign;
    enum{ decl_none = none, declarator } decl;
  } deriv;
};

struct identifier_ {
  char *code;
  char *symbol;
  TypeCheckType tt;
  struct symtab *sp;
};
struct declarator_ {
  char *code;
  Identifier name;
  TypeCheckType tt;
  GrammarList p; //A list of parameters
};
struct statement_ {
  char *code;
  TypeCheckType tt;
  enum {statement_none = none, expression, breakStatement, iteration, selection, node, edge, dictlist, dict} type;
  union {
    Expression e;
    Statement s;
    Identifier i;
    struct {
      Expression e1;
      Expression e2;
      Expression e3;
    } forloop;
  } sub1;
  union {
    Expression e;
    CompoundStatement cs;
    Identifier i;
  } sub2;
  union {
    CompoundStatement cs;
    Expression e;
  } sub3;
  union {
    enum {forIter,whileIter} iteration;
    enum {ifStatement, ifelseStatement} selection;
    enum {dict_none = none, definitions} dict;
    enum {nodeCreate, nodeAssignment, nodeDictAssignment} node;
    enum {edge_none = none, all = ALLEDGE, both = BOTHEDGE, left = LEFTEDGE, right = RIGHTEDGE} edge;
  } deriv;
};
struct parameter_ {
  char *code;
  TypeCheckType tt;
  int type;
  Identifier i;
};
struct functionDefinition_ {
  char *code;
  TypeCheckType tt;
  enum {typ_void = none, typ_int = INT, typ_double = DOUBLE, typ_char = CHAR, typ_string = STRING,
    typ_node = NODE, typ_edge = EDGE, typ_dict = DICT} type_name;
  Declarator d;
  CompoundStatement cs;
};
struct compoundStatement_ {
  char *code;
  TypeCheckType tt;
  GrammarList sList; //A list of statements
};
struct translationUnit_ {
  char *code;
  FunctionDefinition f;
};
struct grammarList_ {
  char *code;
  TypeCheckType tt;
  enum {argument, statement,parameterList,expressionList} type;
  GrammarNode head;
};
struct grammarNode_ {
  GrammarNode next;
  void *data;
};


void *popFront(GrammarList g);

TranslationUnit getTranslationUnit(FunctionDefinition fd);

FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
FunctionDefinition getRetTypeFunctionDefinition(int type, Declarator d, CompoundStatement cs);

Declarator declaratorId(Identifier id);
Declarator getDeclarator(Identifier id, GrammarList pList);

GrammarList newStatementList(Statement s);
GrammarList extendStatementList(GrammarList sList, Statement s);
GrammarList newParameterList(Parameter p);
GrammarList newArgumentExpressionList(Expression e);
GrammarList appendToPList(GrammarList pList,Parameter param);
GrammarList addFront(GrammarList g, void *data);

Parameter getTypedParameter(int typname, Identifier i);

CompoundStatement newCompoundStatement(GrammarList sList);

Statement getExpressionStatement(Expression e);
Statement getStatement(Statement s);
Statement newIfStatement(Expression e, CompoundStatement cs);
Statement newIfElseStatement(Expression e, CompoundStatement cs1,CompoundStatement cs2);
Statement newWhileStatement(Expression e, CompoundStatement cs);
Statement newForStatement(Expression e1, Expression e2,Expression e3,CompoundStatement cs);
Statement newBreakStatement();
Statement getDictListStatement(Expression e1, Expression e2);
Statement getDictDecStatement(Identifier i);
Statement getDictDefStatement(Identifier i, CompoundStatement cs);
Statement newNodeCreateStatement(Identifier id);
Statement newNodeAssignmentStatement(Identifier id, Expression e);
Statement newNodeDictAssignmentStatement(Identifier id, CompoundStatement cs);
Statement getEdgeStatementFromNodes(Identifier i, Expression e1, int edgeconnector, Expression e2);
Statement getEdgeDeclaration(Identifier i);

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
Expression getAssignEdgeExpression(Expression e1, int edgeconnector, Expression e2);
Expression getInit(int token, Identifier i, Expression e);
Expression getDeclaration(int token, Identifier i);
Expression getDeclExpression(Expression e);

void freeTranslationUnit(TranslationUnit t); 
void freeFunctionDefinition(FunctionDefinition f);
void freeDeclarator(Declarator d);
void freeCompoundStatement(CompoundStatement c);
void freeGrammarList(GrammarList g);
void freeStatement(Statement s);
void freeExpression(Expression e);
void freeIdentifier(Identifier i);
void freeParameter(Parameter p);
void freeTypeCheckType(TypeCheckType t);

#endif
