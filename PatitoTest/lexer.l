%{
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

FILE *token_file;

void write_token(int token, const char *lexeme) {
    fprintf(token_file, "%d %s\n", token, lexeme);
}
%}

%option noyywrap

%%

[ \t\r\n]+              ; /* Ignore whitespace */

"program"               { write_token(PROGRAM, yytext); }
"main"                  { write_token(MAIN, yytext); }
"end"                   { write_token(END, yytext); }
"var"                   { write_token(VAR, yytext); }
"int"                   { write_token(INT, yytext); }
"float"                 { write_token(FLOAT, yytext); }
"void"                  { write_token(VOID, yytext); }
"if"                    { write_token(IF, yytext); }
"else"                  { write_token(ELSE, yytext); }
"while"                 { write_token(WHILE, yytext); }
"do"                    { write_token(DO, yytext); }
"print"                 { write_token(PRINT, yytext); }
"read"                  { write_token(READ, yytext); }

";"                     { write_token(SEMICOLON, yytext); }
":"                     { write_token(COLON, yytext); }
","                     { write_token(COMMA, yytext); }
"="                     { write_token(ASSIGN_OP, yytext); }
"{"                     { write_token(LBRACE, yytext); }
"}"                     { write_token(RBRACE, yytext); }
"("                     { write_token(LPAREN, yytext); }
")"                     { write_token(RPAREN, yytext); }

">"                     { write_token(GT, yytext); }
"<"                     { write_token(LT, yytext); }
"!="                    { write_token(NE, yytext); }
"+"                     { write_token(PLUS, yytext); }
"-"                     { write_token(MINUS, yytext); }
"*"                     { write_token(MULT, yytext); }
"/"                     { write_token(DIV, yytext); }

\"[^\"]*\"              { write_token(CTE_STRING, yytext); }
[0-9]+\.[0-9]+          { write_token(CTE_FLOAT, yytext); }
[0-9]+                  { write_token(CTE_INT, yytext); }
[a-zA-Z][a-zA-Z0-9_]*   { write_token(ID, yytext); }

.                       { printf("Lexical Error: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <source_code_file>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Error opening source file");
        return 1;
    }
    yyin = in;

    token_file = fopen("tokens.txt", "w");
    if (!token_file) {
        perror("Error creating tokens file");
        fclose(in);
        return 1;
    }

    printf("--- Phase 1: Lexical Analysis Started ---\n");
    yylex();
    
    fclose(in);
    fclose(token_file);
    printf("--- Phase 1 Complete: Tokens written to tokens.txt ---\n");
    return 0;
}