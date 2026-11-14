%{
#include <stdio.h>
#include <stdlib.h>
#include "PatitoParser.tab.h"
#include "semantic_structures.h"
#include "semantic_cube.h"
#include "stack.h"
#include "quadruples.h"
#include <string.h>

Stack operator_stack;
Stack operand_stack;
Stack type_stack;

QuadrupleList quadruples;
static int temp_counter = 0;




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

    | EXP gt
      {stack_push_operator(&operator_stack, gt);}
      EXP
      {$$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter); }

    | EXP lt{stack_push_operator(&operator_stack, lt);}
      EXP{$$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}

    | EXP eq {stack_push_operator(&operator_stack, eq);}
      EXP {$$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}

    | EXP ne {stack_push_operator(&operator_stack, ne);}
      EXP {$$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}
    ;




ASSIGN
    : id assign_op EXPRESION semicolon
      {
          char *expression_operand = NULL;
          int expression_type;

          if (pop_expression_value(&expression_operand, &expression_type,&operand_stack,&type_stack)) {

              validate_assignment($1, expression_type);

              quadruples_add(
                  &quadruples,
                  "=",
                  expression_operand,
                  "-",
                  $1
              );

              free(expression_operand);
          }

          free($1);
      }
    ;


CTE
    : cte_int
      {
          push_expression_value($1, Tint,&operand_stack,&type_stack);

          $$ = Tint;

          free($1);
      }

    | cte_float
      {
          push_expression_value($1, Tfloat,&operand_stack,&type_stack);

          $$ = Tfloat;

          free($1);
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
    : EXP plus
      {
          stack_push_operator(&operator_stack, plus);
      }
      TERMINO
      {
          $$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }

    | EXP minus
      {
          stack_push_operator(&operator_stack, minus);
      }
      TERMINO
      {
          $$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }

    | TERMINO
      {
          $$ = $1;
      }
    ;



TERMINO
    : TERMINO mult
      {
          stack_push_operator(&operator_stack, mult);
      }
      FACTOR
      {
          $$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }

    | TERMINO divi
      {
          stack_push_operator(&operator_stack, divi);
      }
      FACTOR
      {
          $$ = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
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
          char *operand = NULL;
          int expression_type;

          if (pop_expression_value(&operand, &expression_type,&operand_stack,&type_stack)) {
              validate_return(expression_type);

              quadruples_add(
                  &quadruples,
                  "RETURN",
                  operand,
                  "-",
                  "-"
              );

              free(operand);
          }
      }
    ;

READ
    : Tread lparen id rparen semicolon
      {
          validate_read($3);

          quadruples_add(
              &quadruples,
              "READ",
              "-",
              "-",
              $3
          );

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
    : EXPRESION
      {
          emit_print(&quadruples,&operand_stack,&type_stack);
      }
      PrintContenidoContinuacion

    | cte_string
      {
          quadruples_add(
              &quadruples,
              "PRINT",
              $1,
              "-",
              "-"
          );

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
          discard_expression(&operand_stack,&type_stack);
      }
    | Tdo STATEMENT Twhile lparen EXPRESION rparen  semicolon
      {
          validate_condition($5);
          discard_expression(&operand_stack,&type_stack);
      }
    ;

CONDITION
    : Tif lparen EXPRESION rparen STATEMENT ConditionElse semicolon
      {
          validate_condition($3);
          discard_expression(&operand_stack,&type_stack);
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
          $$ = apply_unary_minus(&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
    ;

FactorContinuacion
    : id
      {
          int variable_type = get_variable_type($1);

          push_expression_value($1, variable_type,&operand_stack,&type_stack);

          $$ = variable_type;

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
    
    stack_init(&operator_stack, 20);
    stack_init(&operand_stack, 20);
    stack_init(&type_stack, 20);

    quadruples_init(&quadruples, 100);

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
    printf("\nGENERATED QUADRUPLES:\n");

    quadruples_print(&quadruples, stdout);

    stack_destroy(&operator_stack);
    stack_destroy(&operand_stack);
    stack_destroy(&type_stack);

    quadruples_destroy(&quadruples);
    
    return (result != 0 || semantic_context.semantic_errors > 0);
}