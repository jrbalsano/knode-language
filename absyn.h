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

struct expression_ {
  enum {function, unary, postfix, primary} type;
  Identifier name;
};
struct identifier_ {
  char *symbol;
}
struct declarator_ {
  Identifier name;
  GrammarList p; //A list of parameters
}
struct statement_ {
  enum {expression} type;
  union {
    Expression e;
  } sub;
}
struct functionDefinition_ {
  Declarator d;
  CompoundStatement cs;
}
struct compoundStatement_ {
  GrammarList dlist; //A list of declarations
  GrammarList sList; //A list of statements
}
struct translationUnit_ {
  FunctionDefinition f;
}
struct grammarList_ {
  GrammarNode head;
}
struct grammarNode_ {
  GrammarNode next;
  void *data;
}

TranslationUnit getTranslationUnit(FunctionDefinition fd);
FunctionDefinition getFunctionDefinition(Declarator d, CompoundStatement cs);
Declarator declaratorId(char *s);
Declarator getDeclarator(Declarator d, GrammarList pList);
CompoundStatement newCompoundStatement(GrammarList sList);
GrammarList newStatementList(Statement s);
Statement getExpressionStatement(Expression e);
Expression getFunctionExpression(char *id, GrammarList argExpList);
Expression getStringExpression(char *s);
GrammarList newArgumentExpressionList(Expression e);
