#include "quadruples.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Copiar campo de un cuádruplo
static bool copy_field(
    char destination[QUAD_FIELD_SIZE],
    const char *source
) {

    if (source == NULL)
        source = "-";

    int written = snprintf(
        destination,
        QUAD_FIELD_SIZE,
        "%s",
        source
    );

    return written >= 0 && written < QUAD_FIELD_SIZE;
}


// Llenar cuádruplo
static bool fill_quadruple(
    Quadruple *quad,
    const char *operator,
    const char *operand1,
    const char *operand2,
    const char *result
) {

    return
        copy_field(quad->operator, operator) &&
        copy_field(quad->operand1, operand1) &&
        copy_field(quad->operand2, operand2) &&
        copy_field(quad->result, result);
}


// Aumentar capacidad
static bool quadruples_grow(QuadrupleList *list) {

    size_t new_capacity =
        (list->capacity == 0) ? 16 : list->capacity * 2;

    if (new_capacity < list->capacity)
        return false;

    Quadruple *new_items = realloc(
        list->items,
        new_capacity * sizeof(Quadruple)
    );

    if (new_items == NULL)
        return false;

    list->items = new_items;
    list->capacity = new_capacity;

    return true;
}


// Inicializar
bool quadruples_init(
    QuadrupleList *list,
    size_t initial_capacity
) {

    if (list == NULL)
        return false;

    if (initial_capacity == 0)
        initial_capacity = 16;

    list->items = malloc(
        initial_capacity * sizeof(Quadruple)
    );

    if (list->items == NULL) {

        list->count = 0;
        list->capacity = 0;

        return false;
    }

    list->count = 0;
    list->capacity = initial_capacity;

    return true;
}


// Destruir
void quadruples_destroy(QuadrupleList *list) {

    if (list == NULL)
        return;

    free(list->items);

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}


// Cantidad de cuádruplos
size_t quadruples_count(const QuadrupleList *list) {

    return list == NULL ? 0 : list->count;
}


// Obtener cuádruplo
const Quadruple *quadruples_get(
    const QuadrupleList *list,
    size_t index
) {

    if (list == NULL || index >= list->count)
        return NULL;

    return &list->items[index];
}


// Agregar cuádruplo
size_t quadruples_add(
    QuadrupleList *list,
    const char *operator,
    const char *operand1,
    const char *operand2,
    const char *result
) {

    if (list == NULL)
        return SIZE_MAX;

    if (list->count == list->capacity) {

        if (!quadruples_grow(list))
            return SIZE_MAX;
    }

    Quadruple new_quad;

    if (!fill_quadruple(
        &new_quad,
        operator,
        operand1,
        operand2,
        result
    )) {
        return SIZE_MAX;
    }

    size_t index = list->count;

    list->items[list->count++] = new_quad;

    return index;
}


// Actualizar cuádruplo completo
bool quadruples_update(
    QuadrupleList *list,
    size_t index,
    const char *operator,
    const char *operand1,
    const char *operand2,
    const char *result
) {

    if (list == NULL || index >= list->count)
        return false;

    Quadruple updated;

    if (!fill_quadruple(
        &updated,
        operator,
        operand1,
        operand2,
        result
    )) {
        return false;
    }

    list->items[index] = updated;

    return true;
}


// Actualizar destino de salto
bool quadruples_set_result(
    QuadrupleList *list,
    size_t index,
    const char *result
) {

    if (list == NULL || index >= list->count)
        return false;

    return copy_field(
        list->items[index].result,
        result
    );
}


// Imprimir todos los cuádruplos
void quadruples_print(
    const QuadrupleList *list,
    FILE *output
) {

    if (output == NULL)
        output = stdout;

    if (list == NULL) {

        fprintf(output, "Quadruple list is NULL.\n");

        return;
    }

    fprintf(
        output,
        "\n%-6s %-12s %-16s %-16s %-16s\n",
        "INDEX",
        "OPERATOR",
        "OPERAND 1",
        "OPERAND 2",
        "RESULT"
    );

    fprintf(
        output,
        "---------------------------------------------------------------"
        "-----------\n"
    );

    for (size_t i = 0; i < list->count; i++) {

        Quadruple *q = &list->items[i];

        fprintf(
            output,
            "%-6zu %-12s %-16s %-16s %-16s\n",
            i,
            q->operator,
            q->operand1,
            q->operand2,
            q->result
        );
    }
}