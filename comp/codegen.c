#include "codegen.h"
int knodetemp;
char *translationUnitGenerateCode(TranslationUnit t) {

  char *outercode = getValidString(t->f->code);
  char *innercode;
  if (t->t){
      innercode = getValidString(t->t->code);
  }
  else
     innercode = "";

  int length = strlen(outercode) + strlen(innercode) + 1;
  char *result = malloc(sizeof(char)*length);
  strncpy(result, innercode, length);
  strncat(result, outercode, length);
  t->code = getAllocatedString(result);
#ifdef CODETRACE
  printf("Code: %s\n\n", t->code);
#endif
  return result;
}
void functionDefinitionGenerateCode(FunctionDefinition f) {
      Declarator dec = f->d;
      char *c = getValidString(dec->code);
      char *mainFunc = "main()\n";
      char *c1 = getValidString(f->cs->code);
      if(strcmp(c, mainFunc) == 0) {
        char *cCode = "int main()";
        int length = strlen(cCode) + strlen(c1) + 1;
        char result[length];
        strncpy(result, cCode, length);
        strncat(result, c1, length);
        f->code = getAllocatedString(result);
     }
     else {
       char *cv = "void ";
       int length = strlen(c) + strlen(c1) + strlen(cv) + 1;
       char result[length];
       strncpy(result, cv, length);
       strncat(result, c, length);
       strncat(result, c1, length);
       f->code = getAllocatedString(result);
     }
#ifdef CODETRACE
  printf("Code: %s\n\n", f->code);
#endif
}

void declaratorGenerateCode(Declarator d) {
  if(!d->p) {
    char *c = getValidString(d->name->code);
    char *c2 = "()\n";
    int length = strlen(c) + strlen(c2) + 1;
    char result[length];
    sprintf(result, "%s%s", c, c2);
    d->code = getAllocatedString(result);
  }
  else {
    char *c1 = getValidString(d->name->code);
    char *c2 = getValidString(d->p->code);
    int length = strlen(c1) + strlen(c2) + 4;
    char result[length];
    sprintf(result, "%s(%s)\n", c1, c2);
    d->code = getAllocatedString(result);
  }
#ifdef CODETRACE
  printf("Code: %s\n", d->code);
#endif
}

void compoundStatementGenerateCode(CompoundStatement cs) {
  char *c1 = getValidString(cs->sList->code);
  char *c2 = "{\n";
  char *c3 = "}\n";
  char *c4 = getValidString(cs->s->postcode);
  char *c5 = cs->main ? "return 0;\n" : "";
  int length = strlen(c1)+strlen(c2)+strlen(c3)+strlen(c4)+1;
  char result[length];
  sprintf(result, "%s%s%s%s%s", c2, c1, c4, c5, c3);
  cs->code = getAllocatedString(result);
#ifdef CODETRACE
  printf("Code: %s\n\n", cs->code);
#endif
}

void expressionListGenerateCode(GrammarList g) {
  int b1 = 1024;
  int b2 = 1024;
  int b3 = 1024;
  char *code = malloc(sizeof(char)*b1);
  char *precode = malloc(sizeof(char)*b2);
  char *postcode = malloc(sizeof(char)*b3);
  GrammarNode current = g->head;
  code[0] = precode[0] = postcode[0] = 0;
  int i = 0;
  //loop through all expression list nodes
  while (current)
  {
    char *c = getValidString(((Expression)current->data)->code);
    char *pre = getValidString(((Expression)current->data)->precode);
    char *post = getValidString(((Expression)current->data)->postcode);
    c = getValidString(c);
    pre = getValidString(pre);
    post = getValidString(post);
    int n1;
    int n2;
    int n3;
    n1 = strlen(code) + strlen(c) + 3;
    n2 = strlen(precode) + strlen(pre) + 3;
    n3 = strlen(postcode) + strlen(post) + 3;
    while (n1>b1) {
      b1 *= 2;
      char *old = code;
      code = malloc(sizeof(char)*b1);
      strcpy(code, old);
      free(old);
    }
    while (n2>b2) {
      b2 *= 2;
      char *old = precode;
      precode = malloc(sizeof(char)*b2);
      strcpy(precode, old);
      free(old);
    }
    while (n3>b3) {
      b3 *= 2;
      char *old = postcode;
      postcode = malloc(sizeof(char)*b3);
      strcpy(postcode, old);
      free(old);
    }

    if (i == 0) {
      strncpy(code, c, b1);
      strncpy(precode, pre, b2);
      strncpy(postcode, post, b3);
    }
    else {
      strncat(code, ", ", b1);
      strncat(code, c, b1);
      strncat(precode, pre, b2);
      strncat(postcode, post, b3);
    }
    
    current = current->next;
    i = i + 1;
  }

  g->code = getAllocatedString(code);
  g->precode = getAllocatedString(precode);
  g->postcode = getAllocatedString(postcode);
  free(code);
  free(precode);
  free(postcode);
#ifdef CODETRACE
  printf("Code: %s", g->code);
#endif
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
#ifdef CODETRACE
  printf("Code: %s\n\n", g->code);
#endif
}

void parameterListGenerateCode(GrammarList g) {
  int b1 = 1024;
  char *code = malloc(sizeof(char)*b1);
  GrammarNode current = g->head;
  code[0] = 0;
  int i = 0;
  while (current)
  {
    char *c = getValidString(((Parameter)(current->data))->code);
    c = getValidString(c);
    int n1;
    n1 = strlen(code) + strlen(c) + 3;
    while (n1>b1) {
      b1 *= 2;
      char *old = code;
      code = malloc(sizeof(char)*b1);
      strcpy(code, old);
      free(old);
    }
    if (i == 0) {
      strncpy(code, c, b1);
    }
    else {
      strncat(code, ", ", b1);
      strncat(code, c, b1);
    }
    
    current = current->next;
    i++;
  }

  g->code = getAllocatedString(code);
  free(code);
#ifdef CODETRACE
  printf("Code: %s", g->code);
#endif
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
           
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
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
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
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
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
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
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

//This is the code for the dictlist statements for entries
void dictlistGenerateCode(Statement s) {
    //getting identfier of key
   
    char *valueIdentifier = getValidString(s->sub1.i->code);
    //find out what the enum value should be
    char *et;
    //char *c1;
    switch(s->sub2.e->tt->base){
        case int_:
           // c1 = "int %s;\n";
            et= "eint";
            break;
        case double_:
          //  c1 = "double %s;\n";
            et= "edouble";
            break;
        case string_:
            et= "echar";
            break;
        default:
            ;
    }
    const char *format = "addToDict(%%1$s, %s, \"%s\", %s);\n";
    char *value = getValidString(s->sub2.e->code);
    int length = strlen(valueIdentifier) + strlen(value) + strlen(format) + 1;
    char result[length];
   // char *delcar[strlen(c1)];
   // sprintf(delcar, c1, valueIdentifier);
    sprintf(result, format, et, valueIdentifier, value);
    //strncat(result,delcar,length);
    s->code = getAllocatedString(result);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

//This is the case when you initialize a dictionary with entries
void dictDefinitionsGenerateCode(Statement s) {
  //dict initialization
  char *dictIdentifier = getValidString(s->sub1.i->code);
  //add entries to dicitonary
  char *str = getValidString(s->sub2.cs->code);
  const char *delims = "\n";
  char forStrTok[strlen(str)];
  strcpy(forStrTok, str);
  char *sResult = NULL;
  sResult = strtok(forStrTok, delims );
  int i=-2;
  int length = 1;
  while( sResult != NULL ) {
    i++;
    length += strlen(sResult);
    sResult = strtok( NULL, delims );
  }
  length += i * strlen(dictIdentifier);
  char result[length];
  
  sprintf(result, str, dictIdentifier);
  char *final = result + 2;
  result[strlen(result)-3] = 0;
  const char *format = "Dict %s = initDict(); \n%s\n";
  int length2 = strlen(format) + strlen(dictIdentifier) + strlen(final);
  char endResult[length2];
  sprintf(endResult, format, dictIdentifier, final);
  s->code = getAllocatedString(endResult);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void dictGenerateCode(Statement s) {
//This case is when you are declaring a dict without any entries y'all
    char *dictKeyWord = "Dict ";
    char *dictIdentifier = getValidString(s->sub1.i->code);
    char *eqSign = "=";
    char *functionName = "initDict();\n";
    int length = strlen(dictKeyWord) + strlen(dictIdentifier) + strlen(eqSign) + strlen(functionName);
    char result[length];
    strncpy(result, dictKeyWord, length);
    strncat(result, dictIdentifier, length);
    strncat(result, eqSign, length);
    strncat(result, functionName, length);
    s->code = getAllocatedString(result);    
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void nodeCreationGenerateCode(Statement s) {
  char *c = getValidString(s->sub1.i->code);
  char *c1 = "SmartNode ";
  char *c2 = " = newSmartNode();\n";
  int length = strlen(c) + strlen(c1) + strlen(c2) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c, length);
  strncat(result, c2, length);
  
  char *format = "freeSmartNode(%s);\n%s";
  char *existing = getValidString(s->s->postcode);
  length = strlen(format) + strlen(c) + strlen(existing) + 1;
  char post[length];
  sprintf(post, format, c, existing);
  s->s->postcode = getAllocatedString(post);

  s->code = getAllocatedString(result); 
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void nodeAssignmentGenerateCode(Statement s) {
  char *c1 = "SmartNode ";
  char *c2 = getValidString(s->sub1.i->code);
  char *c3 = " = ";
  char *c4 = "newSmartNode();\n";
  char *c5 = " = ";
  char *c6 = getValidString(s->sub2.e->code);
  char *c7 = ";\n";
  int length = strlen(c1) + strlen(c2) + strlen(c2) + strlen(c3) + strlen(c4) + strlen(c6) + strlen(c7);
  char result[length];
  strcpy(result, c1);
  strcat(result, c2);
  strcat(result, c3);
  strcat(result, c4);
  strcat(result, c2);
  strcat(result, c5);
  strcat(result, c6);
  strcat(result, c7);
  s->code = getAllocatedString(result);

  char *format = "freeSmartNode(%s);\n%s";
  char *existing = getValidString(s->s->postcode);
  length = strlen(format) + strlen(c2) + strlen(existing) + 1;
  char post[length];
  sprintf(post, format, c2, existing);
  s->s->postcode = getAllocatedString(post);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void nodeDictionaryGenerateCode(Statement s) {
  char *c1 = "SmartNode ";
  char *id = getValidString(s->sub1.i->code);
  char *c3 = " = ";
  char *c4 = "newSmartNode();\n";
  //now get the code for our compound statement
  
  char *str = getValidString(s->sub2.cs->code);
  //format the code for our silly compound statement
  const char *delims = "\n";
  char forStrTok[strlen(str)];
  strcpy(forStrTok, str);
  char *sResult = NULL;
  sResult = strtok(forStrTok, delims);
  int i = -2;
  int cslength = 1;
  while (sResult != NULL) {
    i++;
    cslength += strlen(sResult);
    sResult = strtok(NULL, delims);
  }
  char *wrapper = "getNode(%s)->dictlist";
  char wrapperWithId[strlen(wrapper) + strlen(id) + 1];
  sprintf(wrapperWithId, wrapper, id);
  cslength += i * strlen(wrapperWithId);
  char c5[cslength];
  sprintf(c5, str, wrapperWithId);

  //char *c5 = getValidString(s->sub2.cs->code);

  int length = strlen(c1) + strlen(id) + strlen(c3) + strlen(c4) + strlen(c5);
  char result[length];
  strcpy(result, c1);
  strcat(result, id);
  strcat(result, c3);
  strcat(result, c4);
  strcat(result, c5);
  s->code = getAllocatedString(result);

  char *format = "freeSmartNode(%s);\n%s";
  char *existing = getValidString(s->s->postcode);
  length = strlen(format) + strlen(id) + strlen(existing) + 1;
  char post[length];
  sprintf(post, format, id, existing);
  s->s->postcode = getAllocatedString(post);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void edgeCreationGenerateCode(Statement s) {


}

void edgeStatementGenerateCode(Statement s) {
  char *c = getValidString(s->sub1.i->code);
  char *ca = getValidString(s->sub2.e->code);
  char *cb = getValidString(s->sub3.e->code);
  char *c4; 

  switch(s->deriv.edge){
    case right:
      c4 = "atob";
      break;
    case left:
      c4 = "btoa";
      break;
    case both:
      c4 = "both";  
      break;
    default: 
      c4 = "";
  }
  
  const char *format = "SmartEdge %s = newSmartEdge(copySmartNode(%s), copySmartNode(%s), %s);\n";
  int length = strlen(c) + strlen(ca) + strlen(cb) + strlen(c4) + strlen(format);
  char result[length];
  sprintf(result, format, c, ca, cb, c4);

  s->code = getAllocatedString(result); 
 
  format = "freeSmartEdge(%s);\n%s";
  char *existing = getValidString(s->s->postcode);
  length = strlen(format) + strlen(c) + strlen(existing) + 1;
  char post[length];
  sprintf(post, format, c, existing);
  s->s->postcode = getAllocatedString(post);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void statementGenerateCode(Statement s) {

  //figure out what kind of statement this code from hello world is
  char str[strlen(getValidString(s->sub1.s->code))+1];
  strcpy(str, getValidString(s->sub1.s->code));
  s->code = getAllocatedString(str);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void expressionStatementGenerateCode(Statement s) {
  char *pre = getValidString(s->sub1.e->precode);
  char *code = testForSemicolon(getValidString(s->sub1.e->code));
  char *post = getValidString(s->sub1.e->postcode);
  int length = strlen(pre)+ strlen(code) + strlen(post) + 2;
  char str[length];
  strcpy(str, pre);
  strcat(str, code);
  strcat(str, ";\n");
  strcat(str, post);
  s->code = getAllocatedString(str);
#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void declStatementGenerateCode(Statement s){
  char *c2 = testForSemicolon(getValidString(s->sub2.i->code));
  char *c3 = ";\n";
  char *c4 = "";
  char *c1 = getValidString(getTypnamString(s->sub1.typnam));
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c4, length);
  strncat(result, c2, length);
  strncat(result, c3, length);
     
  s->code = getAllocatedString(result);

#ifdef CODETRACE
  printf("Code: %s\n\n", s->code);
#endif
}

void parameterGenerateCode(Parameter p) {
  char *c1 = getValidString(getTypnamString(p->type));
  char *c2 = getValidString(p->i->code);
  int length = strlen(c1) + strlen(c2) + 2;
  char result[length];
  sprintf(result, "%s%s", c1, c2);
  p->code = getAllocatedString(result);

#ifdef CODETRACE
  printf("Code: %s\n", p->code);
#endif
}

void passupExpressionCode(Expression e) {
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
#ifdef CODETRACE
  printf("Passup Code: %s\n", e->code);
#endif
}

void postfixIdentifierGenerateCode(Expression e) {
  char *c = getValidString(e->sub1.e->code);
  char *c2 = getValidString(e->sub2.i->code);
  if(e->sub1.e->tt->base == edge_) {
    char *edgeWrapper = "getEdge(%s)->edge_name";
    char result[strlen(edgeWrapper) + strlen(c) + 1];
    sprintf(result, edgeWrapper, c);
    e->code = getAllocatedString(result);
  }
  else if(e->sub1.e->tt->base == node_) {
    char *nodeWrapping = "getStrFromSmartNode(copySmartNode(%s), \"%s\")";
    char result[strlen(nodeWrapping) + strlen(c) + strlen(c2) + 1];
    sprintf(result, nodeWrapping, c, c2);
    e->code = getAllocatedString(result);
  }
  else {
    char *c3 = "->";
    int length = strlen(c) + strlen(c2) + strlen(c3) + 1;
    char result[length];
    strncpy(result, c, length);
    strncat(result, c3, length);
    strncat(result, c2, length);

    e->code = getAllocatedString(result);
  }
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
#ifdef CODETRACE
  printf("PostfixIdentifier Code: %s\n", e->code);
#endif
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
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
#ifdef CODETRACE
  printf("PostfixIncrement Code: %s\n", e->code);
#endif
}

void postfixArgumentGenerateCode(Expression e) {
  char *str = getValidString(e->sub1.e->code);
  char *str2 = getValidString(e->sub2.l ? e->sub2.l->code : NULL);
  char *str3;// = ""; 
  char *str4 = "printf";
  char *str5 = "";
/*  if(strcmp(str, str4)==0)
     printf("%s is equal to printf and str2 = %s", str, str2);*/
  /**deal with printing things that might not be strings already*/
  if (strcmp(str, str4)==0 && strcmp(str2, str5)!=0){
    void *d = e->sub2.l->head->data; 
    Expression e  = (Expression)d; //gets first expression
    if (e != NULL){
      switch(e->tt->base){
        case int_:
        case double_:
        case boolean_:
          str3 = "\"%d\" , ";
          break;
        case char_:
          str3 = "\"%c\" , ";
          break;
        default:
          str3 = "\"%s\" , "; //guess it's a string 
      }
   }
  }
  else{
    str3 = "";
  }
  int length = strlen(str) + strlen(str2) + strlen(str3) + 3;
  char result[length];
  strncpy(result, str, length);
  strncat(result, "(", length);
  strncat(result, str3, length);
  strncat(result, str2, length);
  strncat(result, ")", length);
  e->precode = getAllocatedString(e->sub2.l ? e->sub2.l->precode : "");
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(e->sub2.l ? e->sub2.l->postcode : "");
#ifdef CODETRACE
  printf("PostfixArgument Code: %s\n", e->code);
#endif
}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
#ifdef CODETRACE
  printf("UnaryExpression Code: %s\n", e->code);
#endif
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
  sprintf(result, "%s%s%s", c1, c2, c3);
  e->code = getAllocatedString(result);

  char *pre1 = getValidString(e->sub1.e->precode);
  char *pre2 = getValidString(e->sub2.e->precode);
  char *post1 = getValidString(e->sub1.e->postcode);
  char *post2 = getValidString(e->sub2.e->postcode);

  int prelen = strlen(pre1) + strlen(pre2) + 1;
  char pre[prelen];
  int postlen = strlen(post1) + strlen(post2) + 1;
  char post[postlen];
  
  sprintf(pre, "%s%s", pre1, pre2);
  sprintf(post, "%s%s", post1, post2);
  e->precode = getAllocatedString(pre);
  e->postcode = getAllocatedString(post);
#ifdef CODETRACE
  printf("MultExpression Code: %s\n", e->code);
#endif
}

void addExpressionGenerateCode(Expression e) {
  if ((e->tt->base == int_) | (e->tt->base == double_)){ 
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

  else if (e->tt->base == string_){
    char *s1;
    char *s2;
    char *pre = malloc(1);
    char n[27]; //size of __knodetemp\0 + 15
    if(e->sub1.e->tt->base != string_) {
      char *c1 = getValidString(e->sub1.e->code);
      if(e->sub1.e->tt->base == double_) {
        free(pre);
        char *format = "char __knodetemp%s[15];\nsprintf(__knodetemp%s, \"%%f\", %s);\n";
        char j[15];
        sprintf(j, "%d", knodetemp++);
        int length = strlen(format) + strlen(j) * 2 + strlen(c1) + 1;
        pre = malloc(length * sizeof(char));
        sprintf(pre, format, j, j, c1);
        sprintf(n, "__knodetemp%s", j);
        s1 = n;
      }
      else if(e->sub1.e->tt->base == int_) {
        free(pre);
        char *format = "char __knodetemp%s[15];\nsprintf(__knodetemp%s, \"%%d\", %s);\n";
        char j[15];
        sprintf(j, "%d", knodetemp++);
        int length = strlen(format) + strlen(j) * 2 + strlen(c1) + 1;
        pre = malloc(length * sizeof(char));
        sprintf(pre, format, j, j, c1);
        sprintf(n, "__knodetemp%s", j);
        s1 = n;
      }
      s2 = getValidString(e->sub2.e->code);
    }
    else if(e->sub2.e->tt->base != string_) {
      char *c2 = getValidString(e->sub2.e->code);
      if(e->sub2.e->tt->base == double_) {
        free(pre);
        char *format = "char __knodetemp%s[15];\nsprintf(__knodetemp%s, \"%%f\", %s);\n";
        char j[15];
        sprintf(j, "%d", knodetemp++);
        int length = strlen(format) + strlen(j) * 2 + strlen(c2) + 1;
        pre = malloc(length * sizeof(char));
        sprintf(pre, format, j, j, c2);
        sprintf(n, "__knodetemp%s", j);
        s2 = n;
      }
      else if(e->sub2.e->tt->base == int_) {
        free(pre);
        char *format = "char __knodetemp%s[15];\nsprintf(__knodetemp%s, \"%%d\", %s);\n";
        char j[15];
        sprintf(j, "%d", knodetemp++);
        int length = strlen(format) + strlen(j) * 2 + strlen(c2) + 1;
        pre = malloc(length * sizeof(char));
        sprintf(pre, format, j, j, c2);
        sprintf(n, "__knodetemp%s", j);
        s2 = n;
      }
      s1 = getValidString(e->sub1.e->code);
    }
    else {
      // this char pointer is the length of the precode without the input.
      s1 = getValidString(e->sub1.e->code);
      s2 = getValidString(e->sub2.e->code);
    }
    char prestat[strlen(getValidString(pre)) + 1];
    strcpy(prestat, getValidString(pre));
    free(pre);
    // k is the string of the value of the current knodetemp.
    // k is incremented after use here for the next knodetemp.
    char k[15];
    sprintf(k, "%d", knodetemp++);
    char l[15];
    sprintf(l, "%d", knodetemp++);

    const char *format = "%s%s%sint __knodetemp%s = strlen(%s) + strlen(%s);\nchar __knodetemp%s[__knodetemp%s];\nstrcpy(__knodetemp%s, %s);\nstrcat(__knodetemp%s, %s);\n";

    // the length of the precode
    int length = strlen(getValidString(e->sub1.e->precode)) + strlen(getValidString(e->sub2.e->precode)) + strlen(prestat) + strlen(s1) * 2 + strlen(s2) * 2 + strlen(k) * 3 + strlen(l) * 2 + strlen(format) + 1;

    // sets the size of the precode
    e->precode = (char *)malloc(length * sizeof(char));

    // sets this expression's precode.
    sprintf(e->precode, format, getValidString(e->sub1.e->precode), getValidString(e->sub2.e->precode), prestat, l, s1, s2, k, l, k, s1, k, s2);

    //precode = 
    //int length = strlen(string1) + strlen(string2);
    //char __knodetemp#[length]
    //strcpy(__knodetemp#, string1);
    //strcat(__knodetemp#, string2);

    //val = __knodetemp#

    const char *valformat = "__knodetemp%s";
    int vallength = strlen(format) + 1 + strlen(k);
    e->code = (char *)malloc(vallength * sizeof(char));
    sprintf(e->code, valformat, k);

    char *post1 = getValidString(e->sub1.e->postcode);
    char *post2 = getValidString(e->sub2.e->postcode);
    int postlength = strlen(post1) + strlen(post2) + 1;
    char newpost[postlength];
    sprintf(newpost, "%s%s", post1, post2);
    e->postcode = getAllocatedString(newpost);
    //postcode, none
  }
#ifdef CODETRACE
  printf("AddExpression Code: %s\n", e->code);
#endif
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

  e->precode = getAllocatedString(e->sub1.e->precode);
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(e->sub1.e->postcode);

#ifdef CODETRACE
  printf("RelatExpression Code: %s\n", e->code);
#endif
}

void eqExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2;
  if(e->deriv.eq == equal)
    c2 = "==";
  else
    c2 = "!=";
  char *c3 = getValidString(e->sub2.e->code);
  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result,c1,length);
  strncat(result,c2,length);
  strncat(result,c3,length);
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
#ifdef CODETRACE
  printf("eqExpression Code: %s\n", e->code);
#endif
}

void condExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = getValidString(e->sub2.e->code);
  char *c3; 
  switch(e->deriv.cond){
    case cond_or:
      c3 = " || ";
      break;
    case cond_and:
      c3 = " && ";
      break;
    default:
      c3 = "";
      ;
  }

  int length = strlen(c1) + strlen(c2) + strlen(c3) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c3, length);
  strncat(result, c2, length);
 
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));


#ifdef CODETRACE
  printf("CondExpression Code: %s\n", e->code);
#endif
}

void assignmentInitExpressionGenerateCode(Expression e) {

}

void edgeExpressionGenerateCode(Expression e) {

}

void assignmentExpressionGenerateCode(Expression e) {
  char *c1 = getValidString(e->sub1.e->code);
  char *c2 = testForSemicolon(getValidString(e->sub2.e->code));
  char *c3 = " = ";
  char *c4 = ";";
  int length = strlen(c1) + strlen(c2) + strlen(c3) + strlen(c4) + 1;
  char result[length];
  strncpy(result, c1, length);
  strncat(result, c3, length);
  strncat(result, c2, length);
  strncat(result, c4, length);
  char *pre1 = getValidString(e->sub1.e->precode);
  char *pre2 = getValidString(e->sub2.e->precode);
  int prelen = strlen(pre1) + strlen(pre2) + 1;
  char pre[prelen];
  strcpy(pre, pre1);
  strcat(pre, pre2);
  char *post1 = getValidString(e->sub1.e->postcode);
  char *post2 = getValidString(e->sub2.e->postcode);
  int postlen = strlen(post1) + strlen(post2) + 1;
  char post[postlen];
  strcpy(post, post1);
  strcat(post, post2);
  e->precode = getAllocatedString(pre);
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(post);
#ifdef CODETRACE
  printf("AssignmentExpression Code: %s\n", e->code);
#endif
}

void primaryExpressionGenerateCode(Expression e) {
  char intval[15];
  char dval[15];
  switch(e->deriv.primary)
  {
    case primary_identifier: 
      e->code = getAllocatedString(getValidString(e->sub1.i->code));
     break;
    case primary_string:
      e->code = getAllocatedString(getValidString(e->sub1.s));
      break;
    case primary_int:
      sprintf(intval, "%d", e->sub1.ival);
      e->code = getAllocatedString(getValidString(intval));
      break;
    case primary_double:
      sprintf(dval, "%f", e->sub1.dval);
      e->code = getAllocatedString(getValidString(dval));
      break;
    case primary_bool:
      sprintf(intval, "%d", e->sub1.boolval);
      e->code = getAllocatedString(getValidString(intval));
      break;
    default: //not correct default behavior, just tryna debug
      e->code = getAllocatedString(getValidString(e->sub1.s));
      break;
  }
  e->precode = getAllocatedString("");
  e->postcode = getAllocatedString("");
#ifdef CODETRACE
  printf("PrimaryExpression Code: %s\n", e->code);
#endif
}

void primaryExpressionParenthesesGenerateCode(Expression e) {
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));

  int length = strlen(e->sub1.e->code) + 3;
  char result[length];
  sprintf(result, "(%s)", e->sub1.e->code);

  e->code = getAllocatedString(result);
#ifdef CODETRACE
  printf("PrimaryExpressionParentheses Code: %s\n", e->code);
#endif
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
#ifdef CODETRACE
  printf("Identifier Code: %s\n\n", i->code);
#endif
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
      return "int ";
    case DOUBLE:
      return "double ";
    case CHAR:
      return "char ";
    case BOOLEAN:
      return "int "; //this happens because C doesn't do booleans
    case STRING:
      return "char *"; //temporary way of dealing with strings in C
    case NODE:
      return "node ";
    case EDGE:
      return "edge ";
    case DICT:
      return "dict ";
    default:
      return "not any normal type ";
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
