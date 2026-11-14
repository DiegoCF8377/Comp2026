#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "quadruples.h"
#include "semantic_structures.h"
#include "semantic_cube.h"
#include "Hash.h"
#include "PatitoParser.tab.h"

SemanticContext semantic_context;

/* Imprimir errores semánticos */
static void semantic_error(const char *message, const char *name) {
    fprintf(stderr, "[SEMANTIC ERROR] %s: %s\n", message, name);
    semantic_context.semantic_errors++;
}

/* Inicializar las estructuras */
void init_semantic_context(void) {
    initializeHashMap(&semantic_context.global_variables);
    initializeHashMap(&semantic_context.functions);

    semantic_context.current_function = NULL;
    semantic_context.semantic_errors = 0;
}

/* Crear una variable */
void declare_variable(const char *name, int type) {

    struct hashMap* table;

    /* Determinar dónde se registra */
    if (semantic_context.current_function != NULL) {
        table = &semantic_context.current_function->variables;
        
    } else {
        table = &semantic_context.global_variables;
    }

    /* Verificar duplicados a nivel local */
    if (contains(table, name)) {
        semantic_error("Variable doblemente declarada", name);
        return;
    }     
    /* Verificar duplicados a nivel global */
    if (contains(&semantic_context.global_variables, name)) {
        semantic_error("Variable doblemente declarada a nivel global", name);
        return;
    }

    Variable *variable = malloc(sizeof(Variable));

    if (!variable) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    variable->type = type;

    insert(table, name, variable);
}

/* Buscar una variable */
Variable *lookup_variable(const char *name) {

    /* Primero buscar en la tabla local */
    if (semantic_context.current_function != NULL) {

        Variable *variable = search(
            &semantic_context.current_function->variables,
            name
        );

        if (variable != NULL) {
            return variable;
        }
    }

    /* Después buscar en la tabla global */
    return search(&semantic_context.global_variables, name);
}

/* Iniciar una función */
void begin_function(const char *name, int return_type) {

    if (semantic_context.current_function != NULL) {
        semantic_error("Declaración de función anidada", name);
        return;
    }

    Function *function = malloc(sizeof(Function));

    if (!function) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    function->return_type = return_type;
    function->registered = 0;

    initializeHashMap(&function->variables);

    /* Intentar registrar la función */
    if (contains(&semantic_context.functions, name)) {

        semantic_error("Función doblemente declarada", name);

    } else {

        insert(&semantic_context.functions, name, function);
        function->registered = 1;
    }

    /*
     * Aunque exista un duplicado, mantenemos una estructura
     * temporal para analizar correctamente sus parámetros
     * y variables locales.
     */
    semantic_context.current_function = function;
}

/* Registrar parámetros como variables locales */
void declare_parameter(const char *name, int type) {

    if (semantic_context.current_function == NULL) {
        semantic_error("Parámetro fuera de una función", name);
        return;
    }

    declare_variable(name, type);
}

/* Finalizar una función */
void finish_function(void) {

    Function *function = semantic_context.current_function;

    if (function == NULL) {
        return;
    }

    /*
     * Si la función estaba duplicada, nunca fue registrada.
     * Por lo tanto, debemos liberar su estructura temporal.
     */
    if (!function->registered) {

        /* Liberar las variables locales */
        for (int i = 0; i < function->variables.capacity; i++) {

            struct node *current = function->variables.arr[i];

            while (current != NULL) {
                free(current->value);
                current = current->next;
            }
        }

        destroyHashMap(&function->variables);
        free(function);
    }

    semantic_context.current_function = NULL;
}

IdList *idlist_create(char *name) {

    IdList *node = malloc(sizeof(IdList));

    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    node->name = name;
    node->next = NULL;

    return node;
}

IdList *idlist_append(IdList *list, char *name) {

    IdList *new_node = idlist_create(name);

    if (list == NULL) {
        return new_node;
    }

    IdList *current = list;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;

    return list;
}

void declare_id_list(IdList *list, int type) {

    IdList *current = list;

    while (current != NULL) {

        declare_variable(current->name, type);

        current = current->next;
    }
}

void idlist_destroy(IdList *list) {

    while (list != NULL) {

        IdList *next = list->next;

        free(list->name);
        free(list);

        list = next;
    }
}
// Validaciones con el cubo semantico
int validate_assignment(const char *name, int expression_type) {
    if (expression_type == TYPE_ERROR) {
    return 0;
    }
    Variable *variable = lookup_variable(name);

    if (variable == NULL) {
        semantic_error("Variable no declarada", name);
        return 0;
    }

    int result = semantic_cube_lookup(
        variable->type,
        assign_op,
        expression_type
    );

    if (result == TYPE_ERROR) {
        semantic_error("Tipos incompatibles en asignación", name);
        return 0;
    }

    return 1;
}

int validate_read(const char *name) {

    if (lookup_variable(name) == NULL) {
        semantic_error("Variable no declarada en read", name);
        return 0;
    }

    return 1;
}

int validate_condition(int expression_type) {
    if (expression_type == TYPE_ERROR) {
    return 0;
    }
    if (expression_type != Tint) {
        semantic_error("La condición debe ser de tipo entero", "if/while");
        return 0;
    }

    return 1;
}

int validate_return(int expression_type) {

    Function *function = semantic_context.current_function;

    if (function == NULL) {
        semantic_error("Return fuera de una función", "");
        return 0;
    }

    if (function->return_type == Tvoid) {
        semantic_error("Una función void no puede retornar un valor", "");
        return 0;
    }

    int result = semantic_cube_lookup(
        function->return_type,
        assign_op,
        expression_type
    );

    if (result == TYPE_ERROR) {
        semantic_error("Tipo de retorno incompatible", "");
        return 0;
    }

    return 1;
}

/* Operaciones aritméticas y relacionales */
int validate_operation(int left, int op, int right) {

    if (left == TYPE_ERROR || right == TYPE_ERROR) {
        return TYPE_ERROR;
    }

    int result = semantic_cube_lookup(left, op, right);

    if (result == TYPE_ERROR) {
        fprintf(stderr,
            "[SEMANTIC ERROR] Operación incompatible: %s\n",
            token_to_string(op)
        );

        semantic_context.semantic_errors++;
    }

    return result;
}


int get_variable_type(const char *name) {

    Variable *variable = lookup_variable(name);

    if (variable == NULL) {
        semantic_error("Variable no declarada", name);
        return TYPE_ERROR;
    }

    return variable->type;
}

int get_function_return_type(const char *name) {

    Function *function = search(&semantic_context.functions, name);

    if (function == NULL) {
        semantic_error("Función no declarada", name);
        return TYPE_ERROR;
    }

    return function->return_type;
}
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
void generate_temp(char *buffer, size_t size, int *temp_counter) {
    snprintf(buffer, size, "T%d", ++(*temp_counter));
}

/* Guarda un operando y su tipo en sus respectivas pilas. */
void push_expression_value(const char *operand, int type, Stack *operand_stack, Stack *type_stack) {
    if (!stack_push_operand(operand_stack, operand)) {
        fprintf(stderr, "Error: could not push operand.\n");
        exit(EXIT_FAILURE);
    }

    if (!stack_push_type(type_stack, type)) {
        fprintf(stderr, "Error: could not push type.\n");
        exit(EXIT_FAILURE);
    }
}

/*
 * Extrae un operando y su tipo.
 * La función transfiere la propiedad del string al llamador.
 */
int pop_expression_value(char **operand, int *type, Stack *operand_stack, Stack *type_stack) {
    StackItem operand_item;
    StackItem type_item;

    if (!stack_pop(operand_stack, &operand_item)) {
        fprintf(stderr, "Error: operand stack is empty.\n");
        return 0;
    }

    if (!stack_pop(type_stack, &type_item)) {
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
int reduce_pending_operation(Stack *operator_stack, QuadrupleList *quadruples, Stack *operand_stack, Stack *type_stack, int *temp_counter) {
    StackItem operator_item;
    char *right_operand = NULL;
    char *left_operand = NULL;

    int right_type;
    int left_type;

    char result_temp[QUAD_FIELD_SIZE];

    if (!stack_pop(operator_stack, &operator_item)) {
        fprintf(stderr, "Error: operator stack is empty.\n");
        return TYPE_ERROR;
    }

    int operator_token = operator_item.token;
    stack_item_destroy(&operator_item);

    /* Primero extraemos el operando derecho. */
    if (!pop_expression_value(&right_operand, &right_type, operand_stack, type_stack)) {
        return TYPE_ERROR;
    }

    /* Después extraemos el operando izquierdo. */
    if (!pop_expression_value(&left_operand, &left_type, operand_stack, type_stack)) {
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
        push_expression_value("ERROR", TYPE_ERROR, operand_stack, type_stack);

        return TYPE_ERROR;
    }

    generate_temp(result_temp, sizeof(result_temp),temp_counter);

    quadruples_add(
        quadruples,
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
    push_expression_value(result_temp, result_type, operand_stack, type_stack);

    return result_type;
}

/* Aplica el operador unario negativo. */
int apply_unary_minus(QuadrupleList *quadruples,Stack *operand_stack, Stack *type_stack,int *temp_counter) {
    char *operand = NULL;
    int operand_type;

    char result_temp[QUAD_FIELD_SIZE];

    if (!pop_expression_value(&operand, &operand_type, operand_stack,type_stack)) {
        return TYPE_ERROR;
    }

    if (operand_type == TYPE_ERROR) {
        push_expression_value("ERROR", TYPE_ERROR, operand_stack, type_stack);
        free(operand);
        return TYPE_ERROR;
    }

    generate_temp(result_temp, sizeof(result_temp),temp_counter);

    quadruples_add(
        quadruples,
        "NEG",
        operand,
        "-",
        result_temp
    );

    free(operand);

    push_expression_value(result_temp, operand_type, operand_stack, type_stack);

    return operand_type;
}
/* Consume el resultado de una expresión y genera un cuádruplo PRINT. */
void emit_print(QuadrupleList *quadruples,Stack *operand_stack, Stack *type_stack) {
    char *operand = NULL;
    int type;

    if (!pop_expression_value(&operand, &type, operand_stack, type_stack)) {
        return;
    }

    quadruples_add(
        quadruples,
        "PRINT",
        operand,
        "-",
        "-"
    );

    free(operand);
}

/* Consume el resultado de una expresión y genera un cuádruplo RETURN. */
void emit_return(QuadrupleList *quadruples, Stack *operand_stack, Stack *type_stack) {
    char *operand = NULL;
    int type;

    if (!pop_expression_value(&operand, &type, operand_stack, type_stack)) {
        return;
    }

    quadruples_add(
        quadruples,
        "RETURN",
        operand,
        "-",
        "-"
    );

    free(operand);
}

/* Descarta el resultado de una expresión después de validarlo. */
void discard_expression(Stack *operand_stack, Stack *type_stack) {
    char *operand = NULL;
    int type;

    if (pop_expression_value(&operand, &type, operand_stack, type_stack)) {
        free(operand);
    }
}
