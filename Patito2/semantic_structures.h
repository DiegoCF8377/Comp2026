#ifndef SEMANTIC_STRUCTURES_H
#define SEMANTIC_STRUCTURES_H

#include <stddef.h>

#include "stack.h"
#include "quadruples.h"
#include "Hash.h"

/* Una variable */
typedef struct {
    int type;
} Variable;

/* Lista temporal de identificadores */
typedef struct IdList {
    char *name;
    struct IdList *next;
} IdList;

/* Una función */
typedef struct {
    int return_type;
    struct hashMap variables;
    int registered;
} Function;

/* Contexto semántico */
typedef struct {
    struct hashMap global_variables;
    struct hashMap functions;

    Function *current_function;

    int semantic_errors;
} SemanticContext;

/* Contexto global del compilador */
extern SemanticContext semantic_context;

/* Inicialización */
void init_semantic_context(void);

/* Variables */
void declare_variable(const char *name, int type);
Variable *lookup_variable(const char *name);

/* Funciones */
void begin_function(const char *name, int return_type);
void declare_parameter(const char *name, int type);
void finish_function(void);

/* Listas temporales de identificadores */
IdList *idlist_create(char *name);
IdList *idlist_append(IdList *list, char *name);
void declare_id_list(IdList *list, int type);
void idlist_destroy(IdList *list);

/* Validaciones */
int validate_assignment(const char *name, int expression_type);
int validate_read(const char *name);
int validate_condition(int expression_type);
int validate_return(int expression_type);

/* Expresiones */
int validate_operation(int left, int op, int right);

int get_variable_type(const char *name);
int get_function_return_type(const char *name);


/* Generates temporary names: T1, T2, T3... */
void generate_temp(char *buffer, size_t size, int *temp_counter);

/* Pushes an operand and its corresponding type. */
void push_expression_value(
    const char *operand,
    int type,
    Stack *operand_stack,
    Stack *type_stack
);

/* Extracts an operand and its corresponding type. */
int pop_expression_value(
    char **operand,
    int *type,
    Stack *operand_stack,
    Stack *type_stack
);

/* Reduces a pending binary operation. */
int reduce_pending_operation(
    Stack *operator_stack,
    QuadrupleList *quadruples,
    Stack *operand_stack,
    Stack *type_stack,
    int *temp_counter
);

/* Applies unary minus. */
int apply_unary_minus(
    QuadrupleList *quadruples,
    Stack *operand_stack,
    Stack *type_stack,
    int *temp_counter
);

/* Generates PRINT and RETURN quadruples. */
void emit_print(
    QuadrupleList *quadruples,
    Stack *operand_stack,
    Stack *type_stack
);

void emit_return(
    QuadrupleList *quadruples,
    Stack *operand_stack,
    Stack *type_stack
);

/* Discards an expression result. */
void discard_expression(
    Stack *operand_stack,
    Stack *type_stack
);

#endif