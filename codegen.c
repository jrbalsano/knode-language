#include "codegen.h"

void translationUnitGenerateCode(TranslationUnit t) {

  t->code = getAllocatedString(getValidString(t->f->code));
  //does not deal with case where t also has a translation unit
  printf("final code:\n%s\n", t->code);
}
void functionDefinitionGenerateCode(FunctionDefinition f) {

      Declarator dec = f->d;
      char *c = getValidString(dec->code);
      char *mainFunc = "main()\n";
      char *c1 = getValidString(f->cs->code);
      if(strcmp(c, mainFunc) == 0) {
        char *cCode = "void main()";
        int length = strlen(cCode) + strlen(c1) + 1;
        char result[length];
        strncpy(result, cCode, length);
        strncat(result, c1, length);
        f->code = getAllocatedString(result);
     }
     else {
       int length = strlen(c) + strlen(c1) + 1;
       char result[length];
       strncpy(result, c, length);
       strncat(result, c1, length);
       f->code = getAllocatedString(result);
     }
}

void declaratorGenerateCode(Declarator d) {
  if(!d->p) {
    char *c = getValidString(d->name->code);
    char *c2 = "()\n";
    int length = strlen(c) + strlen(c2) + 1;
    char result[length];
    strncpy(result, c, length);
    strncat(result, c2, length);
    d->code = getAllocatedString(result);
  }
  //TODO: deal with d->p case (The case where the function has a parameter list)
}

void compoundStatementGenerateCode(CompoundStatement cs) {

  char *c1 = getValidString(cs->sList->code);
  char *c2 = "{\n";
  char *c3 = "}\n";
  int length = strlen(c1)+strlen(c2)+strlen(c3)+1;
  char result[length];
  strncpy(result, c2, length);
  strcat(result, c1);
  strcat(result, c3);
  cs->code = getAllocatedString(result);

}

void expressionListGenerateCode(GrammarList g) {
  int buffer = 1024;
  char *str = malloc(sizeof(char)*buffer);
  GrammarNode current = g->head;
  int i = 0;
  while (current)
  {
    char *c = ((Expression)current->data)->code;
    c = getValidString(c);
    int newlength;
    if(i)
      newlength = strlen(str) + strlen(c) + 3;
    else
      newlength = strlen(c) + 1;
    while (newlength>buffer) {
      buffer *= 2;
      char *old = str;
      str = malloc(sizeof(char)*buffer);
      strcpy(str, old);
      free(old);
    }

    if (i == 0)
      strncpy(str, c, buffer);
    else {
      strncat(str, ", ", buffer);
      strncat(str, c, buffer);
    }
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(str);
  free(str);
}

void statementListGenerateCode(GrammarList g) {
  int buffer = 1024;
  char *str = malloc(sizeof(char)*buffer);
  GrammarNode current = g->head;
  int i = 0;
  while (current)
  {
    char *c = ((Statement)current->data)->code;
    c = getValidString(c);
    int newlength;
    if(i)
      newlength = strlen(str) + strlen(c) + 1;
    else
      newlength = strlen(c) + 1;
    while (newlength>buffer) {
      buffer *= 2;
      char *old = str;
      str = malloc(sizeof(char)*buffer);
      strcpy(str, old);
      free(old);
    }

    if (i == 0)
      strncpy(str, c, buffer);
    else
      strncat(str, c, buffer);
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(str);
  free(str);
}

void parameterListGenerateCode(GrammarList g) {

}

void forStatementGenerateCode(Statement s) {
  char *c1 = "for(";
  char *c2 = getValidString(s->sub1.forloop.e1->code);
  char *c3 = getValidString(s->sub1.forloop.e2->code);
  char *c4 = getValidString(s->sub1.forloop.e3->code);
  char *c5 = ")\n";
  char *c6 = getValidString(s->sub2.cs->code);
  
  /*problem: c8 likely has a semicolon at the end of it. the next line gets rid of it.*/
  //c4[strlen(c4)-1]='\0';
  
  int length = strlen(c1) + strlen(c2) +strlen(c3) + strlen(c4) + strlen(c5) + strlen(c6) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
  strncat(result, c4, length);
  strncat(result, c5, length);
  strncat(result, c6, length);
 
  s->code = getAllocatedString(result);
           
}

void whileStatementGenerateCode(Statement s) {

  char *c1 = "while(";
  char *c2 = getValidString(s->sub1.e->code);

  //remove semicolon from end of c2
  c2[strlen(c2)-1] = '\0';

  char *c3 = ")\n";
  char *c4 = getValidString(s->sub2.cs->code);
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4);
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
  strncat(result, c4, length);

  s->code = getAllocatedString(result);
}

void ifStatementGenerateCode(Statement s) {
   char *c1 = "if(";
   char *c2 = getValidString(s->sub1.e->code);
   char *c3 = ")";
   char *c4 = getValidString(s->sub2.cs->code);
   int length = strlen(c1) + strlen(c2) +strlen(c3) + strlen(c4);
   char result[length];
   strncpy(result, c1, length);
   strncat(result, c2, length);
   strncat(result, c3, length);
   strncat(result, c4, length);
   s->code = getAllocatedString(result);
}

void ifelseStatementGenerateCode(Statement s) {
    char *c1 = "if(";
    char *c2 = getValidString(s->sub1.e->code);
    char *c3 = ")";
    char *c4 = getValidString(s->sub2.cs->code);
    char *c5 = "else";
    char *c6 = getValidString(s->sub3.cs->code);
    int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + strlen(c5) + strlen(c6);
    char result[length];
    strncpy(result, c1, length);
    strncat(result, c2, length);
    strncat(result, c3, length);
    strncat(result, c4, length);
    strncat(result, c5, length);
    strncat(result, c6, length);
    s->code = getAllocatedString(result);
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

  //figure out what kind of statement this code from hello world is
  char str[strlen(getValidString(s->sub1.s->code))+1];
  strcpy(str, getValidString(s->sub1.s->code));
  s->code = getAllocatedString(str);

}

void expressionStatementGenerateCode(Statement s){

  char *str = testForSemicolon(getValidString(s->sub1.e->code));
  char str1[strlen(getValidString(s->sub1.e->code))+2];
  strcpy(str1, str);
  strcat(str1, ";\n");
  s->code = getAllocatedString(str1);
}

void declStatementGenerateCode(Statement s){
  char *c2 = testForSemicolon(getValidString(s->sub2.i->code));
  char *c3 = ";\n";
  char *c4 = " ";
  char *c1 = getValidString(getTypnamString(s->sub1.typnam));
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c4, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
     
  s->code = getAllocatedString(result);

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {
  e->code = getAllocatedString(getValidString(e->sub1.e->code));

}

void postfixIdentifierGenerateCode(Expression e) {

}

void postfixDecrementGenerateCode(Expression e) {

}

void postfixIncrementGenerateCode(Expression e) {
  char *s = getValidString(e->sub1.e->code);
  char *s2 = "++";
  int length = strlen(s) + strlen(s2) + 1;
  char result[length];
  strncpy(result,s,length);
  strncat(result,s2,length);
  e->code = getAllocatedString(result);
}

void postfixArgumentGenerateCode(Expression e) {

  if (e->deriv.postfix == arg){
    char *str = getValidString(e->sub1.e->code);
    char *str2 = getValidString(e->sub2.l->code);
    int length = strlen(str) + strlen(str2) + 3;
    char result[length];
    strncpy(result, str, length);
    strncat(result, "(", length);
    strncat(result, str2, length);
    strncat(result, ")", length);
    e->code = getAllocatedString(result);
  }
}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
}

void castTypedExpressionGenerateCode(Expression e) {

}

void multExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2; 
  switch(e->deriv.mult) {
    case 0:
      break;
    case times:
      c2 = "*";
      break;
   case divide:
      c2 = "/";
      break;
   case mod:
      c2 = "%";
      break;
  }
  char *c3 = getValidString(e->sub2.e->code);
  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
  e->code = getAllocatedString(result);
}

void addExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = getValidString(e->sub2.e->code);
  char *c3;
  switch(e->deriv.add){
    case plus:
         c3 = "+";
         break;
   case minus:
        c3 = "-";
        break;
   case 0:
       ;
  }

  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c3, length);
  strncat(result, c2, length);
 
  e->code = getAllocatedString(result);
      

}

void relatExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2;
  char *c3 = testForSemicolon(getValidString(e->sub2.e->code));
  char *c4 = ";";
  switch(e->deriv.relat){
    case le:
      c2 = "<=";
      break;
    case ge:
      c2 = ">=";
      break;
    case less:
      c2 = "<";
      break;
    case greater:
      c2 = ">";
      break;
    case none:
      ;
  }
  
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
  strncat(result, c4, length);

  e->code = getAllocatedString(result);
}

void eqExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = "==";
  char *c3 = getValidString(e->sub2.e->code);
  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result,c1,length);
  strncat(result,c2,length);
  strncat(result,c3,length);
  e->code = getAllocatedString(result);
}

void condExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = getValidString(e->sub2.e->code);
  char *c3; 
  switch(e->deriv.cond){
    case cond_or:
      c2 = "||";
      break;
    case cond_and:
      c3 = "&&";
      break;
    case 0:
      ;
  }

  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c3, length);
  strncat(result, c2, length);
 
  e->code = getAllocatedString(result);
}

void assignmentInitExpressionGenerateCode(Expression e) {

}

void edgeExpressionGenerateCode(Expression e) {

}

void assignmentExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = testForSemicolon(getValidString(e->sub2.e->code));
  char *c3 = "=";
  char *c4 = ";";
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c3, length);
  strncat(result, c2, length);
  strncat(result, c4, length);
  e->code = getAllocatedString(result);
}

void primaryExpressionGenerateCode(Expression e) {
  switch(e->deriv.primary)
  {
    case primary_identifier: 
      e->code = getAllocatedString(getValidString(e->sub1.i->code));
     break;
    case primary_string:
      e->code = getAllocatedString(getValidString(e->sub1.s));
      break;
    default: 
      break;
  }
}

void functionExpressionGenerateCode(Expression e) {

}

void twoExpressionGenerateCode(Expression e) {

}

void identifierGenerateCode(Identifier i) {
  char *c = getValidString(i->symbol);
  if(!strcmp(c, "print"))
    c = "printf";
  else
    c = i->symbol;
  i->code = getAllocatedString(c); 
}

char *getAllocatedString(char *s) {
  char *ret = (char *)malloc((strlen(s)+1)*sizeof(char));
  strcpy(ret, s);
  return ret;
}

char *getValidString(char *s){
  if (s)
     return s;
  else
     return "";
}

char *getTypnamString(int typ){
  switch(typ){
    case INT:
      return "int";
    case DOUBLE:
      return "double";
    case CHAR:
      return "char";
    case BOOLEAN:
      return "int"; //this happens because C doesn't do booleans
    case STRING:
      return "String"; //this will probably need to be fixed later since C doesn't do Strings
    case NODE:
      return "node";
    case EDGE:
      return "edge";
    case DICT:
      return "dict";
    default:
      return "not any normal type";
  }
}

char *testForSemicolon(char *s){
  char a = ';';
  char b = s[strlen(s)-1];
  if (a == b){
    s[strlen(s)-1] = '\0';
    return s;
  }
  else
    return s;
}    
