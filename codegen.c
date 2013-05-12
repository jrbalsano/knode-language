#include "codegen.h"
int knodetemp;
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
  int b1 = 1024;
  int b2 = 1024;
  int b3 = 1024;
  char *code = malloc(sizeof(char)*b1);
  char *precode = malloc(sizeof(char)*b2);
  char *postcode = malloc(sizeof(char)*b3);
  GrammarNode current = g->head;
  int i = 0;
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
    if(i) {
      n1 = strlen(code) + strlen(c) + 3;
      n2 = strlen(precode) + strlen(pre) + 3;
      n2 = strlen(postcode) + strlen(post) + 3;
    }
    else {
      n1 = strlen(c) + 1;
      n2 = strlen(pre) + 1;
      n3 = strlen(post) + 1;
    }
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

}

void parameterGenerateCode(Parameter p) {

}

void passupExpressionCode(Expression e) {
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
  #ifdef PRETRACE
   printf("PASSING UP PRECODE %s \n", e->precode);
  #endif
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
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
}

void postfixArgumentGenerateCode(Expression e) {
  char *str = getValidString(e->sub1.e->code);
  char *str2 = getValidString(e->sub2.l->code);
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
  e->precode = getAllocatedString(e->sub2.l->precode);
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(e->sub2.l->postcode);
}

void postfixBracketGenerateCode(Expression e) {

}

void unaryExpressionGenerateCode(Expression e) {
  #ifdef PRETRACE
    printf("Where'd it go? %s", e->sub1.e->precode);
  #endif
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
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
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(getValidString(e->sub1.e->code));
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
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
    // k is the string of the value of the current knodetemp.
    // k is incremented after use here for the next knodetemp.
    char k[15];
    sprintf(k, "%d", knodetemp++);

    // this char pointer is the length of the precode without the input.
    char *s1 = getValidString(e->sub1.e->code);
    char *s2 = getValidString(e->sub2.e->code);
    const char *format = "int length = strlen(%s) + strlen(%s);\nchar __knodetemp%s[length];\nstrcpy(__knodetemp%s, %s);\n strcat(__knodetemp%s, %s);\n";

    //  print for debugging
    //printf("%s\n", s1);
    //printf("%s\n", s2);

    // the length of the precode
    int length = strlen(s1) * 2 + strlen(s2) * 2 + strlen(k) * 3 + strlen(format) + 1;

    // sets the size of the precode
    e->precode = (char *)malloc(length * sizeof(char));

    // sets this expression's precode.
    sprintf(e->precode, format, s1, s2, k, k, s1, k, s2);
     
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

    //postcode, none
  }
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
  e->precode = getAllocatedString(getValidString(e->sub1.e->precode));
  e->code = getAllocatedString(result);
  e->postcode = getAllocatedString(getValidString(e->sub1.e->postcode));
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
