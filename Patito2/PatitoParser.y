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

/* Convierte los tokens de operadores a su representación textual. */
static const char *operator_to_string(int token) {
    switch (token) {
        case plus:      return "+";
        case minus:     return "-";
        case mult:      return "*";
        case divi:      return "/";
        case gt:        return ">";
        case lt:        return "<";
        case eq:        return "==";
        case ne:        return "!=";
        case assign_op: return "=";
        default:        return "?";
    }
}

/* Genera nombres temporales: T1, T2, T3... */
static void generate_temp(char *buffer, size_t size) {
    snprintf(buffer, size, "T%d", ++temp_counter);
}

/* Guarda un operando y su tipo en sus respectivas pilas. */
static void push_expression_value(const char *operand, int type) {
    if (!stack_push_operand(&operand_stack, operand)) {
        fprintf(stderr, "Error: could not push operand.\n");
        exit(EXIT_FAILURE);
    }

    if (!stack_push_type(&type_stack, type)) {
        fprintf(stderr, "Error: could not push type.\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * Extrae un operando y su tipo.
 * La función transfiere la propiedad del string al llamador.
 */
static int pop_expression_value(char **operand, int *type) {
    StackItem operand_item;
    StackItem type_item;

    if (!stack_pop(&operand_stack, &operand_item)) {
        fprintf(stderr, "Error: operand stack is empty.\n");
        return 0;
    }

    if (!stack_pop(&type_stack, &type_item)) {
        fprintf(stderr, "Error: type stack is empty.\n");
        stack_item_destroy(&operand_item);
        return 0;
    }

    *operand = operand_item.lexeme;
    *type = type_item.data_type;

    /* Evitamos liberar el string transferido al llamador. */
    operand_item.lexeme = NULL;

    stack_item_destroy(&operand_item);
    stack_item_destroy(&type_item);

    return 1;
}

/*
 * Reduce una operación binaria:
 *
 *     left_operand operator right_operand
 *
 * Genera un temporal y guarda el resultado en las pilas.
 */
static int reduce_pending_operation(void) {
    StackItem operator_item;
    char *right_operand = NULL;
    char *left_operand = NULL;

    int right_type;
    int left_type;

    char result_temp[QUAD_FIELD_SIZE];

    if (!stack_pop(&operator_stack, &operator_item)) {
        fprintf(stderr, "Error: operator stack is empty.\n");
        return TYPE_ERROR;
    }

    int operator_token = operator_item.token;
    stack_item_destroy(&operator_item);

    /* Primero extraemos el operando derecho. */
    if (!pop_expression_value(&right_operand, &right_type)) {
        return TYPE_ERROR;
    }

    /* Después extraemos el operando izquierdo. */
    if (!pop_expression_value(&left_operand, &left_type)) {
        free(right_operand);
        return TYPE_ERROR;
    }

    /* Validación mediante el cubo semántico. */
    int result_type = validate_operation(
        left_type,
        operator_token,
        right_type
    );

    if (result_type == TYPE_ERROR) {
        free(left_operand);
        free(right_operand);

        /* Mantenemos las pilas balanceadas. */
        push_expression_value("ERROR", TYPE_ERROR);

        return TYPE_ERROR;
    }

    generate_temp(result_temp, sizeof(result_temp));

    quadruples_add(
        &quadruples,
        operator_to_string(operator_token),
        left_operand,
        right_operand,
        result_temp
    );

    printf(
        "[QUAD] (%s, %s, %s, %s)\n",
        operator_to_string(operator_token),
        left_operand,
        right_operand,
        result_temp
    );

    free(left_operand);
    free(right_operand);

    /* El resultado de la operación pasa a ser un nuevo operando. */
    push_expression_value(result_temp, result_type);

    return result_type;
}

/* Aplica el operador unario negativo. */
static int apply_unary_minus(void) {
    char *operand = NULL;
    int operand_type;

    char result_temp[QUAD_FIELD_SIZE];

    if (!pop_expression_value(&operand, &operand_type)) {
        return TYPE_ERROR;
    }

    if (operand_type == TYPE_ERROR) {
        push_expression_value("ERROR", TYPE_ERROR);
        free(operand);
        return TYPE_ERROR;
    }

    generate_temp(result_temp, sizeof(result_temp));

    quadruples_add(
        &quadruples,
        "NEG",
        operand,
        "-",
        result_temp
    );

    free(operand);

    push_expression_value(result_temp, operand_type);

    return operand_type;
}
/* Consume el resultado de una expresión y genera un cuádruplo PRINT. */
static void emit_print(void) {
    char *operand = NULL;
    int type;

    if (!pop_expression_value(&operand, &type)) {
        return;
    }

    quadruples_add(
        &quadruples,
        "PRINT",
        operand,
        "-",
        "-"
    );

    free(operand);
}

/* Consume el resultado de una expresión y genera un cuádruplo RETURN. */
static void emit_return(void) {
    char *operand = NULL;
    int type;

    if (!pop_expression_value(&operand, &type)) {
        return;
    }

    quadruples_add(
        &quadruples,
        "RETURN",
        operand,
        "-",
        "-"
    );

    free(operand);
}

/* Descarta el resultado de una expresión después de validarlo. */
static void discard_expression(void) {
    char *operand = NULL;
    int type;

    if (pop_expression_value(&operand, &type)) {
        free(operand);
    }
}



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
      {
          stack_push_operator(&operator_stack, gt);
      }
      EXP
      {
          $$ = reduce_pending_operation();
      }

    | EXP lt
      {
          stack_push_operator(&operator_stack, lt);
      }
      EXP
      {
          $$ = reduce_pending_operation();
      }

    | EXP eq
      {
          stack_push_operator(&operator_stack, eq);
      }
      EXP
      {
          $$ = reduce_pending_operation();
      }

    | EXP ne
      {
          stack_push_operator(&operator_stack, ne);
      }
      EXP
      {
          $$ = reduce_pending_operation();
      }
    ;




ASSIGN
    : id assign_op EXPRESION semicolon
      {
          char *expression_operand = NULL;
          int expression_type;

          if (pop_expression_value(
                  &expression_operand,
                  &expression_type)) {

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
          push_expression_value($1, Tint);

          $$ = Tint;

          free($1);
      }

    | cte_float
      {
          push_expression_value($1, Tfloat);

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
          $$ = reduce_pending_operation();
      }

    | EXP minus
      {
          stack_push_operator(&operator_stack, minus);
      }
      TERMINO
      {
          $$ = reduce_pending_operation();
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
          $$ = reduce_pending_operation();
      }

    | TERMINO divi
      {
          stack_push_operator(&operator_stack, divi);
      }
      FACTOR
      {
          $$ = reduce_pending_operation();
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

          if (pop_expression_value(&operand, &expression_type)) {
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
          emit_print();
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
          discard_expression();
      }
    ;

CONDITION
    : Tif lparen EXPRESION rparen STATEMENT ConditionElse semicolon
      {
          validate_condition($3);
          discard_expression();
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
          $$ = apply_unary_minus();
      }
    ;

FactorContinuacion
    : id
      {
          int variable_type = get_variable_type($1);

          push_expression_value($1, variable_type);

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