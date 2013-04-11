%{
    /* Declarations
     * ============
     */

     #include <stdio.h>
     #include <stdlib.h>
     #include "y.tab.h"
%}

    /* Rules/Aliases
     * =============
     */

    letter      [A-Za-z_]
    word        (letter)+
    new_block   \n\s\s
    string      \"(word | \s)*\"

%%

    /* Tokens & Actions */

    word                            {
                                        yylval.sIndex = *yytext;
                                        return IDENTIFIER;
                                    }

    "print"                         return PRINT;
    "main"                          return MAIN;
    "("                             return LPAR;
    ")"                             return RPAR;
    ":"                             return COLON;
    new_block                       return NEWBLOCK;
    string                          return(STRING_LITERAL);

%%

int yywrap(void){
    return 1;
}


