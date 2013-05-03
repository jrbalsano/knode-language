#include "absyn.h"
#include "yacc.tab.h"
#include <stdlib.h>

/*******************
 * Translation Units
 *******************/

/**
 * Create Translation Unit from an existing FunctionDefinition
 */
TranslationUnit getTranslationUnit(FunctionDefinition fd) {
  TranslationUnit ret = (TranslationUnit)malloc(sizeof(struct translationUnit_));
  ret->f = fd;
  return ret;
}

/**
 * Recursively free the translation unit and its children.
 */
void freeTranslationUnit(TranslationUnit t) {
  #ifdef MEMTRACE
  printf("Freeing translation unit\n");
  #endif

  if(t == NULL) {
    fprintf(stderr, "Null child TranslationUnit\n");
    return;
  }  
  freeFunctionDefinition(t->f);
  free(t);
  #ifdef MEMTRACE
  printf("Translation unit freed\n");
  #endif
}

/*********************
 * Function Definition 
 *********************/

/**
 * Create FunctionDefinition from its Declaration and the statements that comprise
 * the function.
 */
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs) {
  FunctionDefinition ret = (FunctionDefinition)malloc(sizeof(struct functionDefinition_));
  ret->d = d;
  ret->cs = cs;
  return ret;
}

/**
 * Recursively free the function definition and its children.
 */
void freeFunctionDefinition(FunctionDefinition f) {
  #ifdef MEMTRACE
  printf("Freeing function definition\n");
  #endif
  if(f == NULL) {
    fprintf(stderr, "Null child FunctionDefinition\n");
    return;
  }  
  freeDeclarator(f->d);
  freeCompoundStatement(f->cs);
  free(f);
  #ifdef MEMTRACE
  printf("Function definition freed\n");
  #endif
}

/*************
 * Declarators
 *************/

/**
 * Create a declarator from just an identifier. This is used in cases where
 * the function has no parameters, just an identifier
 */
Declarator declaratorId(Identifier id) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->name = id;
  d->p = NULL;
  return d;
}

/**
 * Create a declarator from an identifier and a parameter list
 */
Declarator getDeclarator(Identifier id, GrammarList pList) {
  Declarator d = (Declarator)malloc(sizeof(struct declarator_));
  d->name = id;
  d->p = pList;
  return d;
}

/**
 * Recursively free the declarator and its children.
 */
void freeDeclarator(Declarator d) {
  #ifdef MEMTRACE
  printf("Freeing declarator\n");
  #endif
  if(d == NULL) {
    fprintf(stderr, "Null child Declarator\n");
    return;
  }  
  if(d->p)
    freeGrammarList(d->p);
  freeIdentifier(d->name);
  free(d);
  #ifdef MEMTRACE
  printf("Declarator freed\n");
  #endif
}

/*********************
 * Compound Statements
 *********************/

/**
 * Create a new compound statement by initializing a new statement list.
 */
CompoundStatement newCompoundStatement(GrammarList sList) {
  CompoundStatement ret = (CompoundStatement)malloc(sizeof(struct compoundStatement_));
  ret->sList = sList;
  return ret;
}

/**
 * Recursively free the compound statement and its children in postorder.
 */
void freeCompoundStatement(CompoundStatement c) {
  #ifdef MEMTRACE
  printf("Freeing compound statement\n");
  #endif
  if(c == NULL) {
    fprintf(stderr, "Null child CompoundStatement\n");
    return;
  }
  freeGrammarList(c->sList);
  free(c);
  #ifdef MEMTRACE
  printf("Compound statement freed\n");
  #endif
}
/*****************
 * Grammar Lists
 *****************/

/**
 * Create a new statement list from an existing statement. To be used in situations where
 * a statement list does not already exist.
 */
GrammarList newStatementList(Statement s) {
  GrammarList sList = (GrammarList)malloc(sizeof(struct grammarList_));
  sList->type = statement;
  sList->head = 0;
  addFront(sList, s);
  return sList;
}


/**
 * Creates a new parameter list from an existing parameter. To be used in sutations
 * where a parameter list does not already exist. See addFront for cases where the
 * list already exists.
 */
GrammarList newParameterList(Parameter p) {
	GrammarList pList = (GrammarList)malloc(sizeof(struct grammarList_));
    pList->type = parameterList;
	pList->head = 0;
	addFront(pList, p);
	return pList;
}

/**
 * Creates a new argument expression list from an existing expression. To be used in
 * situations where the argument expression list does not already exist.
 */
GrammarList newArgumentExpressionList(Expression e) {
  GrammarList aeList = (GrammarList)malloc(sizeof(struct grammarList_));
  aeList->type = argument;
  aeList->head = 0;
  addFront(aeList, e);
  return aeList;
}
/**
 * Creates a new argument expression list from an existing expression. To be used in
 * situations where the argument expression list does not already exist.
 */
GrammarList newExpressionList(Expression e) {
    GrammarList eList = (GrammarList)malloc(sizeof(struct grammarList_));
    eList->type = expressionList;
    eList->head = 0;
    addFront(eList, e);
    return eList;
}
/**
 * Add a node to the front of the Grammar List g, with data pointer data
 */
GrammarList addFront(GrammarList g, void *data) {
  GrammarNode n = (GrammarNode)malloc(sizeof(struct grammarNode_));
  n->data = data;
  n->next = g->head;
  g->head = n;
  return g;
}

/**
 * pops the first node off the front of the list and returns the data stored therein.
 */
void *popFront(GrammarList g) {
  if(g->head) {
    GrammarNode n = g->head;
    g->head = n->next;
    void *d = n->data;
    free(n);
    return d;
  }
  else
    return NULL;
}

void freeGrammarList(GrammarList g) {
  #ifdef MEMTRACE
  printf("Freeing grammar list\n");
  #endif
  if(g == NULL) {
    fprintf(stderr, "Null child GrammarList\n");
    return;
  }  
  while(g->head) {
    void *d = popFront(g);
    switch(g->type) {
      case argument:
        freeExpression((Expression)d);
        break;
      case statement:
        freeStatement((Statement)d);
        break;
      case parameterList:
        freeParameter((Parameter)d);
        break;
      case expressionList:
        freeExpression((Expression)d);
        break;
    }
  }
  free(g);
  #ifdef MEMTRACE
  printf("Grammar list freed\n");
  #endif
}

/************
 * Statements
 ************/

/**
 * Creates a statement from an existing statement
 */
Statement getStatement(Statement s) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->type = none;
  ret->sub1.s = s;
  return ret;
}

/**
 * Create a Statement from an existing expression
 */
Statement getExpressionStatement(Expression e) {
  Statement s = (Statement)malloc(sizeof(struct statement_));
  s->type = expression;
  s->sub1.e = e;
  return s;
}
/**
 * Create a new while iteration statement.
 */
Statement newWhileStatement(Expression e, CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->type = iteration;
  ret->iterationtype = whileIter;
  ret->sub1.e = e;
  ret->sub2.cs = cs;
  return ret;
}
/**
 * Create a new for iteration statement.
 */
Statement newForStatement(Expression e1, Expression e2,Expression e3,CompoundStatement cs) {
  Statement ret = (Statement)malloc(sizeof(struct statement_));
  ret->type = iteration;
  ret->iterationtype = forIter;
  ret->sub1.forloop.e1 = e1;
  ret->sub1.forloop.e2 = e2;
  ret->sub1.forloop.e3 = e3;
  ret->sub2.cs = cs;
  return ret;
}
/**
 * Recursively free the Statement and its children in postorder.
 */
void freeStatement(Statement s) {
  #ifdef MEMTRACE
  printf("Freeing statement\n");
  #endif
  if(s == NULL) {
    fprintf(stderr, "Null child Statement\n");
    return;
  }  
  switch(s->type) {
    case expression:
      freeExpression(s->sub1.e);
      break;
    case iteration:
      switch(s->iterationtype) {
        case forIter:
          freeExpression(s->sub1.forloop.e1);
          freeExpression(s->sub1.forloop.e2);
          freeExpression(s->sub1.forloop.e3);
          freeCompoundStatement(s->sub2.cs);
        case whileIter:
          freeExpression(s->sub1.e);
          freeCompoundStatement(s->sub2.cs);
        break;
          }
      break;
    case none:
      freeStatement(s->sub1.s);
      break;
  }
  free(s);
  #ifdef MEMTRACE
  printf("Statement freed\n");
  #endif
}

/************
 * Parameters
 ************/

/**
 * Create a parameter from a typed argument
 */
Parameter getTypedParameter(int typename, Identifier i){
	Parameter ret = (Parameter)malloc(sizeof(struct parameter_));
	ret->type=typename;
	ret->i = i;
	return ret;
}

/**
 * Free the Parameter.
 */
void freeParameter(Parameter p) {
    freeIdentifier(p->i);
}

/*************
 * Expressions
 *************/

/**
 * Create a new expression from a function call defined by the functions id
 * and the list of arguments
 */
Expression getFunctionExpression(Identifier id, GrammarList argExpList) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = function;
  ret->sub1.i = id;
  ret->sub2.l = argExpList;
  return ret;
}

/**
 * Creates a new primary expression from an existing identifier
 */
Expression getPrimaryIdentifierExpression(Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = primary;
  ret->sub1.i = id;
  return ret;
}

/**
 * Creates a new primary expression from an existing string
 */
Expression getPrimaryStringExpression(char *s) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = string;
  ret->sub1.s = s;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression
 */
Expression getPostfixExpression(Expression e1){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->deriv.postfix = none;
  ret->sub1.e = e1;
  ret->type = postfix;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression followed
 * by square brackets encompassing a second expression
 */
Expression getPostfixBracketExpression(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  ret->deriv.postfix = bracket;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing argument list and an
 * existing expression
 */
Expression getPostfixArgumentExpression(Expression e1, GrammarList argList){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e1;
  ret->sub2.l = argList;
  ret->deriv.postfix = arg;
  return ret;

}

/**
 * Creates a new Postfix Expression from an existing expression and specifies
 * it as an incremement expression
 */
Expression getPostfixIncr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->deriv.postfix = postincr;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression and specifies
 * it as an increment expression
 */
Expression getPostfixDecr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type=postfix;
  ret->deriv.postfix = postdecr;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new Postfix Expression from an existing expression and its
 * identifier. This is to be used when accessing the properties of some
 * expression using a expression.identifier construct.
 */
Expression getPostfixIdentifierExpression(Expression e, Identifier id){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = postfix;
  ret->sub1.e = e;
  ret->sub2.i = id;
  ret->deriv.postfix = identifier;
  return ret;
}

Expression getUnaryExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->deriv.unary = none;
  ret->sub1.e = e;
  return ret;
}

Expression getUnaryIncr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->sub1.e = e;
  ret->deriv.unary = preincr;
  return ret;
}

Expression getUnarySingleOp(char op, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->sub1.e = e;
  ret->deriv.unary = op;
  return ret;
}

Expression getUnaryDecr(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = unary;
  ret->deriv.unary = predecr;
  ret->sub1.e = e;
  return ret;
}

Expression getCastExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cast;
  ret->deriv.cast = none;
  ret->sub1.e = e;
  return ret;
}

Expression getTypedCast(int token, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cast;
  ret->deriv.cast = typed;
  ret->sub1.typnam = token;
  ret->sub2.e = e;
  return ret;
}

Expression getMultExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = mult;
  ret->deriv.mult = none;
  ret->sub1.e = e;
  return ret;
}

Expression getMultiplyExpression(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = mult;
  ret->deriv.mult = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAdditiveExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = add;
  ret->deriv.add = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAddExpression(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = add;
  ret->deriv.add = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getRelatExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = relat;
  ret->deriv.relat = none;
  ret->sub1.e = e;
  return ret;
}

Expression getSingleCharRelat(Expression e1, char c, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = relat;
  ret->deriv.relat = c;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getLeRelat(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = relat;
  ret->deriv.relat = le;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getGeRelat(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = relat;
  ret->deriv.relat = ge;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getEqExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = eq;
  ret->deriv.eq = none;
  ret->sub1.e = e;
  return ret;
}

Expression getEqual(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = eq;
  ret->deriv.relat = equal;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getNotEqual(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = eq;
  ret->deriv.relat = notequal;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAndExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAnd(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cond;
  ret->deriv.cond = cond_and;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}
Expression getOrExpression(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getOr(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cond;
  ret->deriv.cond = cond_or;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}
Expression getCond(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = cond;
  ret->deriv.cond = none;
  ret->sub1.e = e;
  return ret;
}

Expression getAssign(Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = assignment;
  ret->deriv.assign = none;
  ret->sub1.e = e;
  return ret;
}

Expression getTokenizedAssignment(Expression e1, int op, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = assignment;
  ret->deriv.assign = op;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getAssignment(Expression e1, Expression e2){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = assignment;
  ret->deriv.assign = eq_assign;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

Expression getInit(int token, Identifier i, Expression e){
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->deriv.assign = init;
  ret->type = assignment;
  ret->sub1.typnam = token;
  ret->sub2.i = i;
  ret->sub3.e = e;
  return ret;
}
/**
 * Creates a new expression from an existing assignment expression
 */
Expression getExpression(Expression e) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = none;
  ret->deriv.none = none;
  ret->sub1.e = e;
  return ret;
}

/**
 * Creates a new expression from an existing expression and an existing
 * assignment expression.
 */
Expression getExpressionAssignmentExpression(Expression e1, Expression e2) {
  Expression ret = (Expression)malloc(sizeof(struct expression_));
  ret->type = none;
  ret->deriv.none = comma;
  ret->sub1.e = e1;
  ret->sub2.e = e2;
  return ret;
}

/**
 * Recursively free an expression and its children in postorder
 */
void freeExpression(Expression e) {
  #ifdef MEMTRACE
  printf("Freeing expression\n");
  #endif
  if(e == NULL) {
    fprintf(stderr, "Null child Expression\n");
    return;
  }
  switch (e->type) {
    case postfix:
      switch (e->deriv.postfix) {
        case identifier:
          freeIdentifier(e->sub2.i);
          freeExpression(e->sub1.e);
          break;
        case postdecr:
          freeExpression(e->sub1.e);
          break;
        case postincr:
          freeExpression(e->sub1.e);
          break;
        case arg:
          freeExpression(e->sub1.e);
          freeGrammarList(e->sub2.l);
          break;
        case bracket:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
        case 0:
          freeExpression(e->sub1.e);
          break;
      }
      break;
    case unary:
      freeExpression(e->sub1.e);
      break;
    case cast:
      switch(e->deriv.cast){
        case typed:
          freeExpression(e->sub2.e);
          break;
        case 0:
          freeExpression(e->sub1.e);
          break;
      }
      break;

    case mult:
      switch(e->deriv.mult){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case add:
      switch(e->deriv.add){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case relat:
      switch(e->deriv.relat){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case eq:
      switch(e->deriv.eq){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case cond:
      switch(e->deriv.eq){
        case 0:
          freeExpression(e->sub1.e);
          break;
        default:
          freeExpression(e->sub1.e);
          freeExpression(e->sub2.e);
          break;
      }
      break;
    case assignment:
      switch(e->deriv.assign){
      case init:
        freeIdentifier(e->sub2.i);
        freeExpression(e->sub3.e);
        break;
      case 0:
        freeExpression(e->sub1.e);
        break;
      default:
        freeExpression(e->sub1.e);
        freeExpression(e->sub2.e);
        break;
      } 
      break;
    case primary:
      freeIdentifier(e->sub1.i);
      break;
    case function:
      freeIdentifier(e->sub1.i);
      freeGrammarList(e->sub2.l);
      break;
    case none:
      if(!e->deriv.none) 
        freeExpression(e->sub1.e);
      else if(e->deriv.none == comma) {
        freeExpression(e->sub1.e);
        freeExpression(e->sub2.e);
      }
      break;
    default:
      break;
  }
  free(e);
  #ifdef MEMTRACE
  printf("Expression freed\n");
  #endif
}


/*************
 * Identifiers
 *************/

/**
 * Create an identifier from a string
 */
Identifier getIdentifier(char *s) {
  Identifier i = (Identifier)malloc(sizeof(struct identifier_));
  i->symbol = s;
  i->sp = symlook(s);
  return i;
}

/**
 * free an identifier and its children
 */
void freeIdentifier(Identifier i) {
  #ifdef MEMTRACE
  printf("Freeing identifier\n");
  #endif
  if(i == NULL) {
    fprintf(stderr, "Null child Identifier\n");
    return;
  }  
  free(i);
  #ifdef MEMTRACE
  printf("Identifier freed\n");
  #endif
}
