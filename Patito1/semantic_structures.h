#include "Hash.c"

typedef struct {

    char* name;
    int type;

} Variable;

typedef struct {

    char* name;

    int return_type;

    struct hashMap variables; //storage of variables and also parameters

    int parameter_count;

} Function;

typedef struct {

    struct hashMap globals;

    struct hashMap functions;

    Function* current_function;

} SemanticContext;