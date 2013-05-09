#include "codegen.h"

void translationUnitGenerateCode(TranslationUnit t) {

  t->code = getAllocatedString(t->f->code);
  //does not deal with case where t also has a translation unit

}

void functionDefinitionGenerateCode(FunctionDefinition f) {

/*NOTE: I have no idea why, but I get tons of errors when this switch statement is uncommented out... halp?!*/

//  switch(f->type_name)
//  {
//    case 0:
      Declarator dec = f->d;
      char *c = dec->code;
      char *c1 = f->cs->code;
      strcat(c,c1);
      f->code = getAllocatedString(c);
//      break;
//    default: 
//      break;//will need to be filled in for all types
//  }
        
}

void declaratorGenerateCode(Declarator d) {

  char *c = d->name->code;
  char *c2 = "():\n";
  strcat(c,c2);
  d->code = getAllocatedString(c);

  //TODO: deal with d->p case
}

void compoundStatementGenerateCode(CompoundStatement cs) {

  char *c1 = cs->sList->code;
  char *c2 = "\n ";
  strcat(c2, c1);
  cs->code = getAllocatedString(c2);

}

void expressionListGenerateCode(GrammarList g) {

  char *str = ""; 
  void *current = g->head;
  while (current)
  {
    char *c = ((Expression)current)->code;
    strcat(str, c);
  }

  g->code = getAllocatedString(str);
}

void statementListGenerateCode(GrammarList g) {

}

void parameterListGenerateCode(GrammarList g) {

}

void forStatementGenerateCode(Statement s) {

}

void whileStatementGenerateCode(Statement s) {

}

void ifStatementGenerateCode(Statement s) {

}

void ifelseStatementGenerateCode(Statement s) {

}

void dictlistGenerateCode(Statement s) {

}

void dictDefinitionsGenerateCode(Statement s) {

}

void dictGenerateCode(Statement s) {

}

void nodeCreationGenerateCode(Statement s) {

}

void nodeAssignmentGenerateCode(Statement s) {

}

void nodeDictionaryGenerateCode(Statement s) {

}

void edgeCreationGenerateCode(Statement s) {

}

void edgeStatementGenerateCode(Statement s) {

}

void statementGenerateCode(Statement s) {

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {

}

void postfixIdentifierGenerateCode(Expression e) {

}

void postfixDecrementGenerateCode(Expression e) {

}

void postfixIncrementGenerateCode(Expression e) {

}

void postfixArgumentGenerateCode(Expression e) {

  if (e->deriv.postfix == arg)
  {
    char *str = e->sub1.e->code;
    char *str2 = e->sub2.l->code;
    strcat(str, "(");
    strcat(str, str2);
    strcat(str, ")");
    e->code = getAllocatedString(str);  
  }
}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {

}

void castTypedExpressionGenerateCode(Expression e) {

}

void multExpressionGenerateCode(Expression e) {

}

void addExpressionGenerateCode(Expression e) {

}

void relatExpressionGenerateCode(Expression e) {

}

void eqExpressionGenerateCode(Expression e) {

}

void condExpressionGenerateCode(Expression e) {

}

void assignmentInitExpressionGenerateCode(Expression e) {

}

void edgeExpressionGenerateCode(Expression e) {

}

void assignmentExpressionGenerateCode(Expression e) {

}

void primaryExpressionGenerateCode(Expression e) {

}

void functionExpressionGenerateCode(Expression e) {

}

void twoExpressionGenerateCode(Expression e) {

}

void identifierGenerateCode(Identifier i) {

  char *c = getAllocatedString(i->symbol);
  i->code = c;

}

char *getAllocatedString(char *s) {
  char *ret = (char *)malloc((strlen(s)+1)*sizeof(char));
  strcpy(ret, s);
  return ret;
}
