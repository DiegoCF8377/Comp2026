#ifndef SEMANTIC_STRUCTURES_H
#define SEMANTIC_STRUCTURES_H

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

#endif