#include "walker.h"

void startWalk(TranslationUnit root) {
  Scope s = newScope(NULL);
  TypeCheckType printType = getTypeCheckType(void_);
  printType->fn_sub = getTypeCheckType(string_);
  addSymbolToScope(s, "print", printType);
  walkTranslationUnit(root, s); 
}

void walkTranslationUnit(TranslationUnit t, Scope s) {
#ifdef MEMTRACE
  printf("Walking translation unit at %p\n", t);
#endif

  if(t == NULL) {
    fprintf(stderr, "Null child TranslationUnit\n");
    return;
  }
  if(!s) {
    s = newScope(NULL);
  }
  t->s = s;
  if (t->t != NULL){
    printf("Checking the other translation unit\n");
    walkTranslationUnit(t->t, s);
  }
  walkFunctionDefinition(t->f, s);
  if (t->t != NULL){
    printf("Checking the other translation unit\n");
    walkTranslationUnit(t->t, s);
  }
  translationUnitTypeCheck(t);
  translationUnitGenerateCode(t);
#ifdef MEMTRACE
  printf("Translation unit walked at %p\n", t);
#endif
}

void walkFunctionDefinition(FunctionDefinition f, Scope s) {
#ifdef MEMTRACE
  printf("Walking function definition at %p\n", f);
#endif
  if(f == NULL) {
    fprintf(stderr, "Null child FunctionDefinition\n");
    return;
  }
  f->s = newScope(s);
  walkDeclarator(f->d, s);
  walkCompoundStatement(f->cs, s);
  functionDefinitionTypeCheck(f);
  functionDefinitionGenerateCode(f);
#ifdef MEMTRACE
  printf("Function definition walked at %p\n", f);
#endif
}

void walkDeclarator(Declarator d, Scope s) {
#ifdef MEMTRACE
  printf("Walking declarator at %p\n", d);
#endif
  if(d == NULL) {
    fprintf(stderr, "Null child Declarator\n");
    return;
  }
  d->s = s;
  if(d->p)
    walkGrammarList(d->p, d->s);
  walkIdentifier(d->name, d->s->parent); //we want the id to be register in top level namespace
  declaratorTypeCheck(d);
  declaratorGenerateCode(d);
#ifdef MEMTRACE
  printf("Declarator walked at %p\n", d);
#endif
}

void walkCompoundStatement(CompoundStatement c, Scope s) {
#ifdef MEMTRACE
  printf("Walking compound statement at %p\n", c);
#endif
  if(c == NULL) {
    fprintf(stderr, "Null child CompoundStatement\n");
    return;
  }
  c->s = newScope(s);
  walkGrammarList(c->sList, c->s);
  compoundStatementTypeCheck(c);
  compoundStatementGenerateCode(c);
#ifdef MEMTRACE
  printf("Compound statement walked at %p\n", c);
#endif
}

void walkGrammarList(GrammarList g, Scope s) {
#ifdef MEMTRACE
  printf("Walking grammar list at %p\n", g);
#endif
  if(g == NULL) {
    fprintf(stderr, "Null child GrammarList\n");
    return;
  }  
  g->s = s;
  GrammarNode current = g->head;
  while(current) {
    void *d = current->data;
    switch(g->type) {
      case argument:
      case expressionList:
        walkExpression((Expression)d, g->s);
        break;
      case statement:
        walkStatement((Statement)d, g->s);
        break;
      case parameterList:
        walkParameter((Parameter)d, g->s);
        break;
    }
    current = current->next;
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

void walkStatement(Statement s, Scope scope) {
#ifdef MEMTRACE
  printf("Walking statement at %p\n", s);
#endif
  if(s == NULL) {
    fprintf(stderr, "Null child Statement\n");
    return;
  }  
  s->s = scope;
  switch(s->type) {
    case expression:
      walkExpression(s->sub1.e, s->s);
      expressionStatementTypeCheck(s);
      expressionStatementGenerateCode(s); 
      break;
    case decl:
      walkIdentifier(s->sub2.i, s->s);
      declStatementTypeCheck(s);
      declStatementGenerateCode(s);
      break;
    case iteration:
      switch(s->deriv.iteration) {
        case forIter:
          walkExpression(s->sub1.forloop.e1, s->s);
          walkExpression(s->sub1.forloop.e2, s->s);
          walkExpression(s->sub1.forloop.e3, s->s);
          walkCompoundStatement(s->sub2.cs, s->s);
          forStatementTypeCheck(s);
          forStatementGenerateCode(s);
          break;
        case whileIter:
          walkExpression(s->sub1.e, s->s);
          walkCompoundStatement(s->sub2.cs, s->s);
          whileStatementTypeCheck(s);
          whileStatementGenerateCode(s);
          break;
      }
      break;
    case selection:
      switch(s->deriv.selection) {
        case ifStatement:
          walkCompoundStatement(s->sub2.cs, s->s);
          walkExpression(s->sub1.e, s->s);
          ifStatementTypeCheck(s);
          ifStatementGenerateCode(s);
          break;
        case ifelseStatement:
          walkExpression(s->sub1.e, s->s);
          walkCompoundStatement(s->sub2.cs, s->s);
          walkCompoundStatement(s->sub3.cs, s->s);
          ifelseStatementTypeCheck(s);
          ifelseStatementGenerateCode(s);
          break;
      }
      break;
    case dictlist:
      walkIdentifier(s->sub1.i, s->s);
      walkExpression(s->sub2.e, s->s);
      dictlistTypeCheck(s);
      dictlistGenerateCode(s); 
      break;
    case dict:
      switch(s->deriv.dict) {
        case definitions:
          walkIdentifier(s->sub1.i, s->s);
          walkCompoundStatement(s->sub2.cs, s->s);
          dictDefinitionsTypeCheck(s);
          dictDefinitionsGenerateCode(s);
          break;
        case none:
          walkIdentifier(s->sub1.i, s->s);
          dictTypeCheck(s);
          dictGenerateCode(s);
          break;
      }
      break;
    case node:
      switch(s->deriv.node) {
        case nodeCreate:
          walkIdentifier(s->sub1.i, s->s);
          nodeCreationTypeCheck(s);
          nodeCreationGenerateCode(s);
          break;
        case nodeAssignment:
          walkIdentifier(s->sub1.i, s->s);
          walkExpression(s->sub2.e, s->s);
          nodeAssignmentTypeCheck(s);
          nodeAssignmentGenerateCode(s);
          break;
        case nodeDictAssignment:
          walkIdentifier(s->sub1.i, s->s);
          walkCompoundStatement(s->sub2.cs, s->s);
          nodeDictionaryTypeCheck(s);
          nodeDictionaryGenerateCode(s);
          break;
      }
      break;
    case edge:
      switch(s->deriv.edge) {
        case none:
          walkIdentifier(s->sub1.i, s->s);
          edgeCreationTypeCheck(s);
          edgeCreationGenerateCode(s);
          break;
        default:
          walkIdentifier(s->sub1.i, s->s);
          walkExpression(s->sub2.e, s->s);
          walkExpression(s->sub3.e, s->s);
          edgeStatementTypeCheck(s);
          edgeStatementGenerateCode(s);
          break;
      }
      break;
    case none:
      walkStatement(s->sub1.s, s->s);
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

void walkParameter(Parameter p, Scope s) {
#ifdef MEMTRACE
  printf("Walking Parameter at %p\n", p);
#endif
  p->s = s;
  walkIdentifier(p->i, p->s);
  parameterTypeCheck(p);
  parameterGenerateCode(p);
#ifdef MEMTRACE
  printf("Parameter walked at %p\n", p);
#endif
}

void walkExpression(Expression e, Scope s) {
#ifdef MEMTRACE
  printf("Walking expression at %p\n", e);
#endif
  if(e == NULL) {
    fprintf(stderr, "Null child Expression\n");
    return;
  }
  e->s = s;
  switch (e->type) {
    case postfix:
      switch (e->deriv.postfix) {
        case identifier:
          walkIdentifier(e->sub2.i, e->s);
          walkExpression(e->sub1.e, e->s);
          postfixIdentifierTypeCheck(e);
          postfixIdentifierGenerateCode(e);
          break;
        case postdecr:
          walkExpression(e->sub1.e, e->s);
          postfixDecrementTypeCheck(e);
          postfixDecrementGenerateCode(e);
          break;
        case postincr:
          walkExpression(e->sub1.e, e->s);
          postfixIncrementTypeCheck(e);
          postfixIncrementGenerateCode(e);
          break;
        case arg:
          walkExpression(e->sub1.e, e->s);
          walkGrammarList(e->sub2.l, e->s);
      /*    int *x = NULL;
          int y = *x + 2;
          printf("%d", y);
        */
          postfixArgumentTypeCheck(e);
          postfixArgumentGenerateCode(e);          
          break;
        case argEmpty:
          walkExpression(e->sub1.e, e->s);
          postfixArgumentTypeCheck(e);
          postfixArgumentGenerateCode(e);
          break;
        case bracket:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          postfixArgumentTypeCheck(e);
          postfixArgumentGenerateCode(e);          
          break;
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
      }
      break;
    case unary:
      walkExpression(e->sub1.e, e->s);
      unaryExpressionTypeCheck(e);
      unaryExpressionGenerateCode(e);
      break;
    case cast:
      switch(e->deriv.cast){
        case typed:
          printf("Typed cast expression.\n");
          walkExpression(e->sub2.e, e->s);
          castTypedExpressionTypeCheck(e);
          castTypedExpressionGenerateCode(e);
          break;
        case 0:
          printf("Case 0 cast expression. \n");
          if (e->sub1.e){
            printf("E sub1 e exists\n");
          }
          if (e->s){

            printf("E s exists \n");
          }
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
      }
      break;
    case mult:
      switch(e->deriv.mult){
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          multExpressionTypeCheck(e);
          multExpressionGenerateCode(e);
          break;
      }
      break;
    case add:
      switch(e->deriv.add){
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          addExpressionTypeCheck(e);
          addExpressionGenerateCode(e);
          break;
      }
      break;
    case relat:
      switch(e->deriv.relat){
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          relatExpressionTypeCheck(e);
          relatExpressionGenerateCode(e);
          break;
      }
      break;
    case eq:
      switch(e->deriv.eq){
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          eqExpressionTypeCheck(e);
          eqExpressionGenerateCode(e);
          break;
      }
      break;
    case cond:
      switch(e->deriv.eq){
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        default:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          condExpressionTypeCheck(e);
          condExpressionGenerateCode(e);
          break;
      }
      break;
    case assignment:
      switch(e->deriv.assign){
        case init:
          walkIdentifier(e->sub2.i, e->s);
          walkExpression(e->sub3.e, e->s);
          assignmentInitExpressionTypeCheck(e);
          assignmentInitExpressionGenerateCode(e);
          break;
        case 0:
          walkExpression(e->sub1.e, e->s);
          passupExpressionType(e);
          passupExpressionCode(e);
          break;
        case assign_left:
        case assign_right:
        case assign_both:
        case assign_all:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          edgeExpressionTypeCheck(e);
          edgeExpressionGenerateCode(e);
          break;
        case eq_assign:
        case multeq:
        case pluseq:
        case diveq:
        case minuseq:
        case modeq:
          walkExpression(e->sub1.e, e->s);
          walkExpression(e->sub2.e, e->s);
          assignmentExpressionTypeCheck(e);
          assignmentExpressionGenerateCode(e);
          break;
      } 
      break;
    case primary:
      switch(e->deriv.primary){
        case primary_string:
          primaryExpressionTypeCheck(e);
          primaryExpressionGenerateCode(e);
          break;
        case primary_identifier:
          walkIdentifier(e->sub1.i, e->s);
          primaryExpressionTypeCheck(e);
          primaryExpressionGenerateCode(e);
          break;
        case parentheses:
          walkExpression(e->sub1.e, e->s);
          primaryExpressionTypeCheck(e);
          primaryExpressionGenerateCode(e);
        default: //unhandled case
          primaryExpressionTypeCheck(e);
          primaryExpressionGenerateCode(e);
          break;
      }
      break;
    case function:
      walkIdentifier(e->sub1.i, e->s);
      walkGrammarList(e->sub2.l, e->s);
      functionExpressionTypeCheck(e);
      functionExpressionGenerateCode(e);
      break;
    case none:
      if(!e->deriv.none)  {
        walkExpression(e->sub1.e, e->s);
        passupExpressionType(e);
        passupExpressionCode(e);
      }
      else if(e->deriv.none == comma) {
        walkExpression(e->sub1.e, e->s);
        walkExpression(e->sub2.e, e->s);
        twoExpressionTypeCheck(e);
        twoExpressionGenerateCode(e);
      }
      break;
    default:
      break;
  }
#ifdef PRETRACE
  printf("Finishing Walking Expression with type %d\n", e->type);
  printf("PRECODE: %s\n", e->precode);
  printf("tt: %p\n", e->tt);
#endif
#ifdef MEMTRACE
  printf("Expression walked at %p\n", e);
#endif
}

void walkIdentifier(Identifier i, Scope s) {
#ifdef MEMTRACE
  printf("Walking identifier at %p\n", i);
#endif
  if(!i) {
    fprintf(stderr, "Null child Identifier\n");
    return;
  }  
  i->s = s;
  identifierTypeCheck(i);
  identifierGenerateCode(i);
#ifdef MEMTRACE
  printf("Identifier walked at %p\n", i);
#endif
}
