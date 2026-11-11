#ifndef QUADRUPLES_H
#define QUADRUPLES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define QUAD_FIELD_SIZE 64


typedef struct {

    char operator[QUAD_FIELD_SIZE];

    char operand1[QUAD_FIELD_SIZE];

    char operand2[QUAD_FIELD_SIZE];

    char result[QUAD_FIELD_SIZE];

} Quadruple;


typedef struct {

    Quadruple *items;

    size_t count;

    size_t capacity;

} QuadrupleList;


// Inicialización y destrucción
bool quadruples_init(
    QuadrupleList *list,
    size_t initial_capacity
);

void quadruples_destroy(QuadrupleList *list);


// Consultas
size_t quadruples_count(const QuadrupleList *list);

const Quadruple *quadruples_get(
    const QuadrupleList *list,
    size_t index
);


// Inserción
size_t quadruples_add(
    QuadrupleList *list,
    const char *operator,
    const char *operand1,
    const char *operand2,
    const char *result
);


// Modificación
bool quadruples_update(
    QuadrupleList *list,
    size_t index,
    const char *operator,
    const char *operand1,
    const char *operand2,
    const char *result
);


// Modificar solamente el resultado
bool quadruples_set_result(
    QuadrupleList *list,
    size_t index,
    const char *result
);


// Imprimir
void quadruples_print(
    const QuadrupleList *list,
    FILE *output
);

#endif