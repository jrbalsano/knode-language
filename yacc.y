%{
    /* DECLARATIONS
     * ============
     * declarations for variables that we want to use in the program
     * ie: 
     * int symtable[10] = 0
     *
     */
%}

    /* Tokens & Associations
     * =====================
     * This section specifies tokens, and associativity of operators
     * ie:
     * %token NUMBER
     * %left PLUS
     * 
     */


    /* Grammar 
     * =======
     * The grammar goes below the %%. This section is here b/c of the way yacc
     * handles comments...General format follows. Remember that actions to the
     * grammar are assigned through the use of a curly brace following the
     * statement {}
     * ie:
     * statement_list
     *      : statement {statement_count++}
     *      | statement statement_list
     *
     */
%%


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
