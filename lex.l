%{
    /* Declarations
     * ============
     * declarations for external libraries and variables that we want to use in
     * the program
     * ie: 
     * #include <stdio.h>
     * #include "y.tab.h"
     * int count = 0
     *
     */
%}

    /* Rules/Aliases
     * =============
     * Create named rules in this section to make your life easier
     * ie:
     * digit [0-9]
     * letter [a-z]
     * 
     */

%%

* {/* Tokens & Actions
    * ================
    * Tokens precede {} and are regular expressions that lex recognizes
    * ie:
    * [0-9]
    * 
    * Actions are inside of the {} and indicate the programmatic action that
    * you wish to occur every time that lex comes across this token
    * ie:
    * if (count >= 0)
    *   count++;
    * NOTE: you can use all the programming constructs you are used to in these
    * actions
    *
    */
}

%%

    /* Programmatic things go here
    * ===========================
    * Any code that we want to execute following the generation. 
    * ie:
    * int main() {
    *      yylex()
    *      return 0;
    * }
    * 
    */
