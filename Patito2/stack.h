#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    STACK_OPERATOR,
    STACK_OPERAND,
    STACK_TYPE
} StackItemKind;

typedef struct {
    StackItemKind kind;

    int token;       // Token del operador
    int data_type;   // Tipo de dato (Tint, Tfloat)
    char *lexeme;    // Identificador, constante o temporal

} StackItem;

typedef struct {
    StackItem *items;
    size_t top;
    size_t capacity;
} Stack;


// Inicialización y destrucción
bool stack_init(Stack *stack, size_t initial_capacity);
void stack_destroy(Stack *stack);


// Consultas
bool stack_is_empty(const Stack *stack);
size_t stack_size(const Stack *stack);


// Inserciones
bool stack_push_operator(Stack *stack, int operator_token);
bool stack_push_operand(Stack *stack, const char *operand);
bool stack_push_type(Stack *stack, int type_token);


// Extracción y consulta
bool stack_pop(Stack *stack, StackItem *out);
const StackItem *stack_peek(const Stack *stack);


// Liberar elemento extraído
void stack_item_destroy(StackItem *item);


// Debug
void stack_print(const Stack *stack, const char *title);

#endif