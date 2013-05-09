#include "codegen.h"

void translationUnitGenerateCode(TranslationUnit t) {

  t->code = getAllocatedString(t->f->code);
  //does not deal with case where t also has a translation unit
  printf("translationUnit code~ %s ~", t->code);
}
void functionDefinitionGenerateCode(FunctionDefinition f) {

/*NOTE: I have no idea why, but I get tons of errors when this switch statement is uncommented out... halp?!*/

//  switch(f->type_name)
//  {
//    case 0:
      Declarator dec = f->d;
      char *c = dec->code;
//      printf("dec->code %s\n", dec->code);
      char *c1 = f->cs->code;
//      printf("f->cs->code %s\n", f->cs->code);
      int length = strlen(c)+strlen(c1)+1;
      char result[length];
      strncpy(result, c, length);
      strncat(result, c1, length);
      f->code = getAllocatedString(result);
      printf("functionDefinion code ~ %s ~", f->code);
//      break;
//    default: 
//      break;//will need to be filled in for all types
//  }

}

void declaratorGenerateCode(Declarator d) {

  char *c = d->name->code;
//printf("%s", c);
  char *c2 = "():\n";
//printf("%s", c2);
  int length = strlen(c) + strlen(c2) + 1;
  char result[length];
  strncpy(result, c, length);
  strncat(result, c2, length);
  d->code = getAllocatedString(result);
  printf("declarator code~ %s ~", d->code);
  //TODO: deal with d->p case (The case where the function has a parameter list)
}

void compoundStatementGenerateCode(CompoundStatement cs) {

  char *c1 = ""; //cs->sList->code;
  printf(cs->sList->code);
  char *c2 = "\n ";
  int length = strlen(c1)+strlen(c2)+1;
  char result[length];
  strncpy(result, c2, length);
  strncat(result, c1, length);
  cs->code = getAllocatedString(result);
  printf("compoundStatement code~ %s ~", cs->code);

}
//this needs a better fix
void expressionListGenerateCode(GrammarList g) {
//
  int buffer = 1024;
  char *str = malloc(sizeof(char)*buffer);
  GrammarNode current = g->head;
  int i = 0;

  while (current)
  {
    char *c = ((Expression)current)->code;
    int newlength = strlen(str) + strlen(c) + 1;
    if (newlength>buffer)
      buffer*= 2;

    if (i == 0)
      strncpy(str, c, buffer);
    else
      strncat(str, c, buffer);
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(str);
  printf("grammarList code~ %s ~", g->code);
  free(str);
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
    char *str;//= e->sub1.e->code;
/*    if (e->sub1.e->code)
    {
      str = e->sub1.e->code;
    }*/
//    else
      str = "ERROR on postfixarg";
//    printf("e->sub1.e->code %s\n" , str);
    char *str2 = e->sub2.l->code;
//    printf("e->sub2.l->code %s\n", str2);
    int length = strlen(str) + strlen(str2) + 3;
    char result[length];
    strncpy(result, str, length);
    strncat(result, "(", length);
    strncat(result, str2, length);
    strncat(result, ")", length);
    e->code = getAllocatedString(result);
    printf("postfix argument code~ %s ~", e->code);  
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
  printf("identfier code~ %s ~", i->code);

}

char *getAllocatedString(char *s) {
  char *ret = (char *)malloc((strlen(s)+1)*sizeof(char));
  strcpy(ret, s);
  return ret;
}
