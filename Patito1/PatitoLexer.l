%{
#include <stdio.h>
#include <stdlib.h>

FILE *token_file;

void write_token(const char *lexeme, const char *value) {
    fprintf(token_file, "%s %s\n", lexeme, value);
}
%}

%option noyywrap

%%

[ \t\r\n]+              ;

"program"               { write_token("Tprogram", yytext); }
"main"                  { write_token("Tmain", yytext); }
"end"                   { write_token("Tend", yytext); }
"var"                   { write_token("Tvar", yytext); }
"int"                   { write_token("Tint", yytext); }
"float"                 { write_token("Tfloat", yytext); }
"void"                  { write_token("Tvoid", yytext); }
"if"                    { write_token("Tif", yytext); }
"else"                  { write_token("Telse", yytext); }
"while"                 { write_token("Twhile", yytext); }
"do"                    { write_token("Tdo", yytext); }
"print"                 { write_token("Tprint", yytext); }
"read"                  { write_token("Tread", yytext); }
"return"                { write_token("Treturn", yytext); }

";"                     { write_token("semicolon", yytext); }
":"                     { write_token("colon", yytext); }
","                     { write_token("comma", yytext); }
"="                     { write_token("assign_op", yytext); }
"{"                     { write_token("lbrace", yytext); }
"}"                     { write_token("rbrace", yytext); }
"("                     { write_token("lparen", yytext); }
")"                     { write_token("rparen", yytext); }
"["                     { write_token("lbracket", yytext); }
"]"                     { write_token("rbracket", yytext); }

">"                     { write_token("gt", yytext); }
"<"                     { write_token("lt", yytext); }
"!="                    { write_token("ne", yytext); }
"=="                    { write_token("eq", yytext); }
"+"                     { write_token("plus", yytext); }
"-"                     { write_token("minus", yytext); }
"*"                     { write_token("mult", yytext); }
"/"                     { write_token("divi", yytext); }

\"[^\"]*\"              { write_token("cte_string", yytext); }
[0-9]+\.[0-9]+          { write_token("cte_float", yytext); }
[0-9]+                  { write_token("cte_int", yytext); }
[a-zA-Z][a-zA-Z0-9_]*   { write_token("id", yytext); }

.                       { write_token("unknown", yytext); }

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
        perror("Error creating tokens files");
        fclose(in);
        return 1;
    }

    printf("--- Phase 1: Lexical Analysis Started ---\n");
    yylex();

    fclose(in);
    fclose(token_file);

    printf("--- Phase 1 Complete: Tokens written to token file ---\n");

    return 0;
}