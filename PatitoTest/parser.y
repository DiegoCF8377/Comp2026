%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

FILE *token_input;
char current_lexeme[256];

void yyerror(const char *s);

/* Custom yylex reading pre-generated tokens from tokens.txt */
int yylex(void) {
    int token;
    if (fscanf(token_input, "%d %255s", &token, current_lexeme) == 2) {
        return token;
    }
    return 0; /* EOF */
}
%}

/* Explicitly bind token numbers to tokens.h values */
%token PROGRAM 1 MAIN 2 END 3 VAR 4 INT 5 FLOAT 6 VOID 7 IF 8 ELSE 9 WHILE 10 DO 11 PRINT 12 READ 13
%token SEMICOLON 14 COLON 15 COMMA 16 ASSIGN_OP 17 LBRACE 18 RBRACE 19 LPAREN 20 RPAREN 21
%token GT 22 LT 23 NE 24 PLUS 25 MINUS 26 MULT 27 DIV 28
%token ID 29 CTE_INT 30 CTE_FLOAT 31 CTE_STRING 32

%%

programa:
    PROGRAM ID SEMICOLON vars funcs MAIN body END
    ;

vars:
    VAR var_decl_list
    | /* empty */
    ;

var_decl_list:
    var_decl_list id_list COLON type SEMICOLON
    | id_list COLON type SEMICOLON
    ;

id_list:
    id_list COMMA ID
    | ID
    ;

type:
    INT
    | FLOAT
    ;

funcs:
    funcs func
    | /* empty */
    ;

func:
    func_return_type ID LPAREN params RPAREN vars body SEMICOLON
    ;

func_return_type:
    VOID
    | type
    ;

params:
    param_list
    | /* empty */
    ;

param_list:
    param_list COMMA ID COLON type
    | ID COLON type
    ;

body:
    LBRACE statement_list RBRACE
    ;

statement_list:
    statement_list statement
    | /* empty */
    ;

statement:
    assign
    | condition
    | cycle
    | f_call
    | print
    | read
    ;

assign:
    ID ASSIGN_OP expresion SEMICOLON
    ;

expresion:
    exp
    | exp GT exp
    | exp LT exp
    | exp NE exp
    ;

exp:
    exp PLUS termino
    | exp MINUS termino
    | termino
    ;

termino:
    termino MULT factor
    | termino DIV factor
    | factor
    ;

factor:
    LPAREN expresion RPAREN
    | optional_sign ID
    | optional_sign cte
    ;

optional_sign:
    PLUS
    | MINUS
    | /* empty */
    ;

cte:
    CTE_INT
    | CTE_FLOAT
    ;

condition:
    IF LPAREN expresion RPAREN statement else_clause SEMICOLON
    ;

else_clause:
    ELSE statement
    | /* empty */
    ;

cycle:
    WHILE LPAREN expresion RPAREN DO statement SEMICOLON
    ;

f_call:
    ID LPAREN expr_list RPAREN SEMICOLON
    ;

expr_list:
    expr_list COMMA expresion
    | expresion
    | /* empty */
    ;

print:
    PRINT LPAREN print_item_list RPAREN SEMICOLON
    ;

print_item_list:
    print_item_list COMMA print_item
    | print_item
    ;

print_item:
    expresion
    | CTE_STRING
    ;

read:
    READ LPAREN id_read_list RPAREN SEMICOLON
    ;

id_read_list:
    id_read_list COMMA ID
    | ID
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error around token '%s': %s\n", current_lexeme, s);
}

int main(void) {
    token_input = fopen("tokens.txt", "r");
    if (!token_input) {
        perror("Error opening tokens.txt for Syntax Analysis");
        return 1;
    }

    printf("--- Phase 2: Syntax Analysis Started ---\n");
    if (yyparse() == 0) {
        printf("Syntax Analysis Successful!\n");
    } else {
        printf("Syntax Analysis Failed.\n");
    }

    fclose(token_input);
    return 0;
}