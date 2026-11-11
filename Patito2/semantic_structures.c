#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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