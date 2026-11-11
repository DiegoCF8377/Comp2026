%{
#include <stdio.h>
#include <stdlib.h>

#include "semantic_structures.h"
#include "semantic_cube.h"

void yyerror(const char *s);
int yylex(void);

extern FILE *yyin;
extern int yylineno;
%}

%code requires {
    #include "semantic_structures.h"
}

%define parse.trace
%define parse.error detailed


%token Tprogram
%token Tmain
%token Tend
%token Tvar
%token Tint
%token Tfloat
%token Tvoid
%token Tif
%token Telse
%token Twhile
%token Tdo
%token Tprint
%token Tread
%token Treturn

%token semicolon
%token colon
%token comma
%token assign_op
%token lbrace
%token rbrace
%token lparen
%token rparen
%token lbracket
%token rbracket

%token gt
%token lt
%token ne
%token eq
%token plus
%token minus
%token mult
%token divi

%token <str> cte_string
%token <str> cte_float
%token <str> cte_int
%token <str> id

%token unknown


%union {
    char *str;
    int type;
    IdList *ids;
}
%type <type> TYPE FuncsType
%type <type> EXPRESION EXP TERMINO FACTOR CTE
%type <type> InnerF_CALL FactorStart FactorContinuacion

%type <ids> IdList

%destructor { free($$); } <str>
%destructor { idlist_destroy($$); } <ids>
%%
PROGRAMA : Tprogram id semicolon VarsOpcional ProgramaFuncs Tmain BODY Tend
    {
        printf("Function name: %s\n", $2);
        free($2);
    }
;

ProgramaFuncs
    : FUNCS ProgramaFuncs
    | %empty
    ;

EXPRESION
    : EXP
      {
          $$ = $1;
      }

    | EXP gt EXP
      {
          $$ = validate_operation($1, gt, $3);
      }

    | EXP lt EXP
      {
          $$ = validate_operation($1, lt, $3);
      }

    | EXP eq EXP
      {
          $$ = validate_operation($1, eq, $3);
      }

    | EXP ne EXP
      {
          $$ = validate_operation($1, ne, $3);
      }
    ;




ASSIGN
    : id assign_op EXPRESION semicolon
      {
          validate_assignment($1, $3);
          free($1);
      }
    ;


CTE
    : cte_int
      {
          free($1);
          $$ = Tint;
      }

    | cte_float
      {
          free($1);
          $$ = Tfloat;
      }
    ;

STATEMENT
    : RETURN
    | ASSIGN
    | CONDITION
    | CYCLE
    | F_CALL
    | PRINT
    | READ
    | lbracket StatementInBrackets rbracket
    ;

StatementInBrackets
    : %empty
    | STATEMENT StatementInBrackets
    ;

BODY : lbrace BodyCont rbrace;

BodyCont
    : STATEMENT BodyCont
    | %empty
    ;


EXP
    : EXP plus TERMINO
      {
          $$ = validate_operation($1, plus, $3);
      }

    | EXP minus TERMINO
      {
          $$ = validate_operation($1, minus, $3);
      }

    | TERMINO
      {
          $$ = $1;
      }
    ;



TERMINO
    : TERMINO mult FACTOR
      {
          $$ = validate_operation($1, mult, $3);
      }

    | TERMINO divi FACTOR
      {
          $$ = validate_operation($1, divi, $3);
      }

    | FACTOR
      {
          $$ = $1;
      }
    ;

InnerF_CALL
    : id lparen FCallInitial rparen
      {
          $$ = get_function_return_type($1);
          free($1);
      }
    ;

F_CALL : InnerF_CALL semicolon;

FCallInitial
    : FCallContinuation
    | %empty
    ;

FCallContinuation : EXPRESION FCallMultiple;

FCallMultiple
    : comma FCallContinuation
    | %empty
    ;

RETURN
    : Treturn EXPRESION semicolon
      {
          validate_return($2);
      }
    ;

READ
    : Tread lparen id rparen semicolon
      {
          validate_read($3);
          free($3);
      }
    ;


VarsOpcional
    : VARS
    | %empty
    ;

VARS
    : Tvar VarStart
    ;

VarStart
    : IdList colon TYPE semicolon
      {
          declare_id_list($1, $3);
          idlist_destroy($1);
      }
      VarStart

    | IdList colon TYPE semicolon
      {
          declare_id_list($1, $3);
          idlist_destroy($1);
      }
    ;

IdList
    : id
      {
          $$ = idlist_create($1);
      }

    | IdList comma id
      {
          $$ = idlist_append($1, $3);
      }
    ;

TYPE
    : Tint
      {
          $$ = Tint;
      }

    | Tfloat
      {
          $$ = Tfloat;
      }
    ;
PRINT
    : Tprint lparen PrintContenido rparen semicolon
    ;

PrintContenido
    : EXPRESION PrintContenidoContinuacion

    | cte_string
      {
          free($1);
      }
      PrintContenidoContinuacion
    ;

PrintContenidoContinuacion
    : comma PrintContenido
    | %empty
    ;

CYCLE
    : Twhile lparen EXPRESION rparen Tdo STATEMENT semicolon
      {
          validate_condition($3);
      }
    ;


CONDITION
    : Tif lparen EXPRESION rparen STATEMENT ConditionElse semicolon
      {
          validate_condition($3);
      }
    ;

ConditionElse
    : Telse STATEMENT
    | %empty
    ;

FACTOR
    : lparen EXPRESION rparen
      {
          $$ = $2;
      }

    | InnerF_CALL
      {
          $$ = $1;
      }

    | FactorStart
      {
          $$ = $1;
      }
    ;

FactorStart
    : FactorContinuacion
      {
          $$ = $1;
      }

    | plus FactorContinuacion
      {
          $$ = $2;
      }

    | minus FactorContinuacion
      {
          $$ = $2;
      }
    ;

FactorContinuacion
    : id
      {
          $$ = get_variable_type($1);
          free($1);
      }

    | CTE
      {
          $$ = $1;
      }
    ;

FUNCS
    : FuncsType id
      {
          begin_function($2, $1);
          free($2);
      }
      lparen FuncsIDsOpcional rparen
      lbracket VarsOpcional BODY rbracket semicolon
      {
          finish_function();
      }
    ;

FuncsType
    : Tvoid
      {
          $$ = Tvoid;
      }

    | TYPE
      {
          $$ = $1;
      }
    ;

FuncsIDsOpcional
    : FuncsIDs
    | %empty
    ;

FuncsIDs
    : id colon TYPE
      {
          declare_parameter($1, $3);
          free($1);
      }
      FuncsIDsContinuacion
    ;

FuncsIDsContinuacion
    : comma FuncsIDs
    | %empty
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr,
        "[SYNTAX ERROR] Line %d: %s\n",
        yylineno,
        s
    );
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        perror("Error opening source file");
        return 1;
    }

    yyin = input;

    init_semantic_cube();
    init_semantic_context();

    yydebug = 0;

    int result = yyparse();

    if (result == 0 && semantic_context.semantic_errors == 0) {
        printf("\nCompilation successful!\n");
    } else {
        printf("\nCompilation failed.\n");
        printf("Semantic errors: %d\n",
            semantic_context.semantic_errors);
    }

    fclose(input);

    return (result != 0 || semantic_context.semantic_errors > 0);
}