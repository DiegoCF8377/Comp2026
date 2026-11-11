#ifndef SEMANTIC_CUBE_H
#define SEMANTIC_CUBE_H

#define TYPE_ERROR -1

void init_semantic_cube(void);

int semantic_cube_lookup(
    int left_type_token,
    int op_token,
    int right_type_token
);

const char *token_to_string(int token);

#endif