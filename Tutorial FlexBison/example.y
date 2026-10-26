%{
#include <stdio.h>

void yyerror(const char *s);
int yylex(void);
%}

%token NUMBER

%left '+' '-'

%%

expr:
      expr '+' expr { printf("Add\n"); }
    | expr '-' expr { printf("Subtract\n"); }
    | NUMBER        { printf("Number\n"); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}