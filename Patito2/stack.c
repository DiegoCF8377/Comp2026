#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Copiar strings dinámicamente
static char *copy_string(const char *source) {

    if (source == NULL)
        return NULL;

    size_t length = strlen(source) + 1;

    char *copy = malloc(length);

    if (copy != NULL)
        memcpy(copy, source, length);

    return copy;
}


// Aumentar capacidad
static bool stack_grow(Stack *stack) {

    size_t new_capacity =
        (stack->capacity == 0) ? 8 : stack->capacity * 2;

    StackItem *new_items = realloc(
        stack->items,
        new_capacity * sizeof(StackItem)
    );

    if (new_items == NULL)
        return false;

    stack->items = new_items;
    stack->capacity = new_capacity;

    return true;
}


// Inicializar
bool stack_init(Stack *stack, size_t initial_capacity) {

    if (stack == NULL)
        return false;

    if (initial_capacity == 0)
        initial_capacity = 8;

    stack->items = malloc(
        initial_capacity * sizeof(StackItem)
    );

    if (stack->items == NULL) {
        stack->top = 0;
        stack->capacity = 0;
        return false;
    }

    stack->top = 0;
    stack->capacity = initial_capacity;

    return true;
}


// Destruir
void stack_destroy(Stack *stack) {

    if (stack == NULL)
        return;

    for (size_t i = 0; i < stack->top; i++) {
        stack_item_destroy(&stack->items[i]);
    }

    free(stack->items);

    stack->items = NULL;
    stack->top = 0;
    stack->capacity = 0;
}


// Verificar si está vacía
bool stack_is_empty(const Stack *stack) {

    return stack == NULL || stack->top == 0;
}


// Obtener tamaño
size_t stack_size(const Stack *stack) {

    return stack == NULL ? 0 : stack->top;
}


// Inserción genérica
static bool stack_push_item(Stack *stack, StackItem item) {

    if (stack == NULL) {
        stack_item_destroy(&item);
        return false;
    }

    if (stack->top == stack->capacity) {

        if (!stack_grow(stack)) {
            stack_item_destroy(&item);
            return false;
        }
    }

    stack->items[stack->top++] = item;

    return true;
}


// Push de operadores
bool stack_push_operator(Stack *stack, int operator_token) {

    StackItem item = {
        .kind = STACK_OPERATOR,
        .token = operator_token,
        .data_type = 0,
        .lexeme = NULL
    };

    return stack_push_item(stack, item);
}


// Push de operandos
bool stack_push_operand(Stack *stack, const char *operand) {

    if (operand == NULL)
        return false;

    StackItem item = {
        .kind = STACK_OPERAND,
        .token = 0,
        .data_type = 0,
        .lexeme = copy_string(operand)
    };

    if (item.lexeme == NULL)
        return false;

    return stack_push_item(stack, item);
}


// Push de tipos
bool stack_push_type(Stack *stack, int type_token) {

    StackItem item = {
        .kind = STACK_TYPE,
        .token = 0,
        .data_type = type_token,
        .lexeme = NULL
    };

    return stack_push_item(stack, item);
}


// Pop
bool stack_pop(Stack *stack, StackItem *out) {

    if (stack == NULL || out == NULL || stack->top == 0)
        return false;

    *out = stack->items[--stack->top];

    // Transferimos la propiedad del string al elemento extraído.
    stack->items[stack->top].lexeme = NULL;

    return true;
}


// Peek
const StackItem *stack_peek(const Stack *stack) {

    if (stack == NULL || stack->top == 0)
        return NULL;

    return &stack->items[stack->top - 1];
}


// Liberar elemento
void stack_item_destroy(StackItem *item) {

    if (item == NULL)
        return;

    free(item->lexeme);

    item->lexeme = NULL;
}


// Imprimir pila
void stack_print(const Stack *stack, const char *title) {

    printf("\n%s\n", title);

    if (stack_is_empty(stack)) {
        printf("[EMPTY]\n");
        return;
    }

    for (size_t i = stack->top; i > 0; i--) {

        StackItem *item = &stack->items[i - 1];

        switch (item->kind) {

            case STACK_OPERATOR:
                printf("Operator token: %d\n", item->token);
                break;

            case STACK_OPERAND:
                printf("Operand: %s\n", item->lexeme);
                break;

            case STACK_TYPE:
                printf("Type token: %d\n", item->data_type);
                break;
        }
    }
}