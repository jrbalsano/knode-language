#include "walker.h"

/**
 * Recursively walk a function definition, generating
 * code and checking types.
 */
void walkFunctionDefinition(FunctionDefinition f) {
#ifdef MEMTRACE
  printf("Walking function definition at %p\n", f);
#endif
  if(f == NULL) {
    fprintf(stderr, "Null child FunctionDefinition\n");
    return;
  }  
  walkDeclarator(f->d);
  walkCompoundStatement(f->cs);
  functionDefinitionTypeCheck(f);
  functionDefinitionGenerateCode(f);
#ifdef MEMTRACE
  printf("Function definition walked at %p\n", f);
#endif
}

void walkDeclarator(Declarator d) {
#ifdef MEMTRACE
  printf("Walking declarator at %p\n", d);
#endif
  if(d == NULL) {
    fprintf(stderr, "Null child Declarator\n");
    return;
  }  
  if(d->p)
    walkGrammarList(d->p);
  walkIdentifier(d->name);
  declaratorTypeCheck(d);
  declaratorGenerateCode(d);
#ifdef MEMTRACE
  printf("Declarator walked at %p\n", d);
#endif
}

void walkTranslationUnit(TranslationUnit t) {
#ifdef MEMTRACE
  printf("Walking translation unit at %p\n", t);
#endif

  if(t == NULL) {
    fprintf(stderr, "Null child TranslationUnit\n");
    return;
  }
  walkFunctionDefinition(t->f);
  translationUnitTypeCheck(t);
  translationUnitGenerateCode(t);
#ifdef MEMTRACE
  printf("Translation unit walked at %p\n", t);
#endif
}

void walkCompoundStatement(CompoundStatement c) {
#ifdef MEMTRACE
  printf("Walking compound statement at %p\n", c);
#endif
  if(c == NULL) {
    fprintf(stderr, "Null child CompoundStatement\n");
    return;
  }
  walkGrammarList(c->sList);
  compoundStatementTypeCheck(c);
  compoundStatementGenerateCode(c);
#ifdef MEMTRACE
  printf("Compound statement walked at %p\n", c);
#endif
}

void walkGrammarList(GrammarList g) {
#ifdef MEMTRACE
  printf("Walking grammar list at %p\n", g);
#endif
  if(g == NULL) {
    fprintf(stderr, "Null child GrammarList\n");
    return;
  }  
  while(g->head) {
    void *d = popFront(g);
    switch(g->type) {
      case argument:
        walkExpression((Expression)d);
        break;
      case statement:
        walkStatement((Statement)d);
        break;
      case parameterList:
        walkParameter((Parameter)d);
        break;
      case expressionList:
        walkExpression((Expression)d);
        break;
    }
  }
  switch(g->type) {
    case argument:
      expressionListTypeCheck(g);
      expressionListGenerateCode(g);
      break;
    case statement:
      statementListTypeCheck(g);
      statementListGenerateCode(g);
      break;
    case parameterList:
      parameterListTypeCheck(g);
      parameterListGenerateCode(g);
      break;
    case expressionList:
      expressionListTypeCheck(g);
      expressionListGenerateCode(g);
      break;
  }
#ifdef MEMTRACE
  printf("Grammar list walked at %p\n", g);
#endif
}


void walkStatement(Statement s) {
#ifdef MEMTRACE
  printf("Walking statement at %p\n", s);
#endif
  if(s == NULL) {
    fprintf(stderr, "Null child Statement\n");
    return;
  }  
  switch(s->type) {
    case expression:
      walkExpression(s->sub1.e);
      break;
    case iteration:
      switch(s->deriv.iteration) {
        case forIter:
          walkExpression(s->sub1.forloop.e1);
          walkExpression(s->sub1.forloop.e2);
          walkExpression(s->sub1.forloop.e3);
          walkCompoundStatement(s->sub2.cs);
          forStatementTypeCheck(s);
          forStatementGenerateCode(s);
          break;
        case whileIter:
          walkExpression(s->sub1.e);
          walkCompoundStatement(s->sub2.cs);
          whileStatementTypeCheck(s);
          whileStatementGenerateCode(s);
          break;
      }
      break;
    case selection:
      switch(s->deriv.selection) {
        case ifStatement:
          walkCompoundStatement(s->sub2.cs);
          walkExpression(s->sub1.e);
          ifStatementTypeCheck(s);
          ifStatementGenerateCode(s);
          break;
        case ifelseStatement:
          walkExpression(s->sub1.e);
          walkCompoundStatement(s->sub2.cs);
          walkCompoundStatement(s->sub3.cs);
          ifelseStatementTypeCheck(s);
          ifelseStatementGenerateCode(s);
          break;
      }
      break;
      // EVERYTHING BELOW HERE IS WRONG AND NEEDS TO BE SWITCHED TO WALK/TYPECHECK/GENERATE
    case dictlist:
      freeExpression(s->sub1.e);
      freeExpression(s->sub2.e);
      break;
    case dict:
      switch(s->deriv.dict) {
        case definitions:
          freeIdentifier(s->sub1.i);
          freeCompoundStatement(s->sub2.cs);
          break;
        case none:
          freeIdentifier(s->sub1.i);
          break;
      }
      break;
    case node:
      switch(s->deriv.node) {
        case nodeCreate:
          freeIdentifier(s->sub1.i);
          break;
        case nodeAssignment:
          freeIdentifier(s->sub1.i);
          freeExpression(s->sub2.e);
          break;
        case nodeDictAssignment:
          freeIdentifier(s->sub1.i);
          freeCompoundStatement(s->sub2.cs);
          break;
      }
      break;
    case edge:
      switch(s->deriv.edge) {
        case none:
          freeIdentifier(s->sub1.i);
          break;
        default:
          freeIdentifier(s->sub1.i);
          freeExpression(s->sub2.e);
          freeExpression(s->sub3.e);
          break;
      }
      break;
    case none:
      freeStatement(s->sub1.s);
      break;
    default:
      break;
  }
  free(s);
#ifdef MEMTRACE
  printf("Statement walked at %p\n", s);
#endif
}
