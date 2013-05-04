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
    case dictlist:
      walkExpression(s->sub1.e);
      walkExpression(s->sub2.e);
      dictlistTypeCheck(s);
      dictlistGenerateCode(s); 
      break;
    case dict:
      switch(s->deriv.dict) {
        case definitions:
          walkIdentifier(s->sub1.i);
          walkCompoundStatement(s->sub2.cs);
          dictDefinitionsTypeCheck(s);
          dictDefinitionsGenerateCode(s);
          break;
        case none:
          walkIdentifier(s->sub1.i);
          dictTypeCheck(s);
          dictGenerateCode(s);
          break;
      }
    case node:
      switch(s->deriv.node) {
        case nodeCreate:
          walkIdentifier(s->sub1.i);
          nodeCreationTypeCheck(s);
          nodeCreationGenerateCode(s);
          break;
        case nodeAssignment:
          walkIdentifier(s->sub1.i);
          walkExpression(s->sub2.e);
          nodeAssignmentTypeCheck(s);
          nodeAssignmentGenerateCode(s);
          break;
        case nodeDictAssignment:
          walkIdentifier(s->sub1.i);
          walkCompoundStatement(s->sub2.cs);
          nodeDictionaryTypeCheck(s);
          nodeDictionaryGenerateCode(s);
          break;
      }
      break;
    case edge:
      switch(s->deriv.edge) {
        case none:
          walkIdentifier(s->sub1.i);
          edgeCreationTypeCheck(s);
          edgeCreationGenerateCode(s);
          break;
        default:
          walkIdentifier(s->sub1.i);
          walkExpression(s->sub2.e);
          walkExpression(s->sub3.e);
          edgeStatementTypeCheck(s);
          edgeStatementGenerateCode(s);
          break;
      }
      break;
    case none:
      walkStatement(s->sub1.s);
      statementTypeCheck(s);
      statementGenerateCode(s);
      break;
    default:
      break;
  }
#ifdef MEMTRACE
  printf("Statement walked at %p\n", s);
#endif
}

void walkParameter(Parameter p) {
#ifdef MEMTRACE
  printf("Walking Parameter at %p\n", p);
#endif
  walkIdentifier(p->i);
  parameterTypeCheck(p);
  parameterGenerateCode(p);
#ifdef MEMTRACE
  printf("Parameter walked at %p\n", p);
#endif
}

void walkExpression(Expression e) {
#ifdef MEMTRACE
  printf("Walking expression at %p\n", e);
#endif
  if(e == NULL) {
    fprintf(stderr, "Null child Expression\n");
    return;
  }
  switch (e->type) {
    case postfix:
      switch (e->deriv.postfix) {
        case identifier:
          walkIdentifier(e->sub2.i);
          walkExpression(e->sub1.e);
          postfixIdentifierTypeCheck(e);
          postfixIdentifierGenerateCode(e);
          break;
        case postdecr:
          walkExpression(e->sub1.e);
          postfixDecrementTypeCheck(e);
          postfixDecrementGenerateCode(e);
          break;
        case postincr:
          walkExpression(e->sub1.e);
          postfixIncrementTypeCheck(e);
          postfixIncrementGenerateCode(e);
          break;
        case arg:
          walkExpression(e->sub1.e);
          walkGrammarList(e->sub2.l);
          postfixArgumentTypeCheck(e);
          postfixArgumentGenerateCode(e);          
          break;
        case bracket:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          postfixArgumentTypeCheck(e);
          postfixArgumentGenerateCode(e);          
          break;
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
      }
      break;
    case unary:
      walkExpression(e->sub1.e);
      unaryExpressionTypeCheck(e);
      unaryExpressionGenerateCode(e);
      break;
    case cast:
      switch(e->deriv.cast){
        case typed:
          walkExpression(e->sub2.e);
          castTypedExpressionTypeCheck(e);
          castTypedExpressionGenerateCode(e);
          break;
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
      }
      break;
    case mult:
      switch(e->deriv.mult){
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          multExpressionTypeCheck(e);
          multExpressionGenerateCode(e);
          break;
      }
      break;
    case add:
      switch(e->deriv.add){
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          addExpressionTypeCheck(e);
          addExpressionGenerateCode(e);
          break;
      }
      break;
    case relat:
      switch(e->deriv.relat){
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          relatExpressionTypeCheck(e);
          relatExpressionGenerateCode(e);
          break;
      }
      break;
    case eq:
      switch(e->deriv.eq){
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          eqExpressionTypeCheck(e);
          eqExpressionGenerateCode(e);
          break;
      }
      break;
    case cond:
      switch(e->deriv.eq){
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          condExpressionTypeCheck(e);
          condExpressionGenerateCode(e);
          break;
      }
      break;
    case assignment:
      switch(e->deriv.assign){
        case init:
          walkIdentifier(e->sub2.i);
          walkExpression(e->sub3.e);
          assignmentInitExpressionTypeCheck(e);
          assignmentInitExpressionGenerateCode(e);
          break;
        case 0:
          walkExpression(e->sub1.e);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        case assign_left:
        case assign_right:
        case assign_both:
        case assign_all:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          edgeExpressionTypeCheck(e);
          edgeExpressionGenerateCode(e);
          break;
        case eqassign:
        case multeq:
        case pluseq:
        case diveq:
        case minuseq:
        case modeq:
          walkExpression(e->sub1.e);
          walkExpression(e->sub2.e);
          assignmentExpressionTypeCheck(e);
          assignmentExpressionGenerateCode(e);
          break;
      } 
      break;
    case primary:
      walkIdentifier(e->sub1.i);
      primaryExpressionTypeCheck(e);
      primaryExpressionGenerateCode(e);
      break;
    case function:
      walkIdentifier(e->sub1.i);
      walkGrammarList(e->sub2.l);
      functionExpressionTypeCheck(e);
      functionExpressionGenerateCode(e);
      break;
    case none:
      if(!e->deriv.none)  {
        walkExpression(e->sub1.e);
        passupExpressionType(e);
        passupExpressionCode(e);
      }
      else if(e->deriv.none == comma) {
        walkExpression(e->sub1.e);
        walkExpression(e->sub2.e);
        twoExpressionTypeCheck(e);
        twoExpressionGenerateCode(e);
      }
      break;
    default:
      break;
  }
#ifdef MEMTRACE
  printf("Expression walked at %p\n", e);
#endif
}

void walkIdentifier(Identifier i) {
#ifdef MEMTRACE
  printf("walking identifier at %p\n", i);
#endif
  if(i == NULL) {
    fprintf(stderr, "Null child Identifier\n");
    return;
  }  
  identifierTypeCheck(i);
  identifierCodeGeneration(i);
#ifdef MEMTRACE
  printf("Identifier walked at %p\n", i);
#endif
}
