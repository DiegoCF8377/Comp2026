#include <stdio.h>
#include <stdbool.h>
#include "parser.tab.h" // Includes your token definitions

// Internal type indices for the cube dimensions
typedef enum {
    IDX_INT = 0,
    IDX_FLOAT = 1,
    NUM_TYPES = 2
} TypeIndex;

// Internal operator indices
typedef enum {
    IDX_PLUS = 0,
    IDX_MINUS,
    IDX_MULT,
    IDX_DIV,
    IDX_ASSIGN,
    IDX_GT,
    IDX_LT,
    IDX_EQ,
    IDX_NE,
    NUM_OPS
} OpIndex;

// Result type representation (using token values or ERROR)
#define TYPE_ERROR -1

// 3D Semantic Cube: [Left Type][Operator][Right Type]
int semantic_cube[NUM_TYPES][NUM_OPS][NUM_TYPES];

// Helper to map Bison type tokens to compact indices
TypeIndex map_type(int token) {
    switch (token) {
        case Tint:   return IDX_INT;
        case Tfloat: return IDX_FLOAT;
        default:     return -1; // Fallback
    }
}

// Helper to map Bison operator tokens to compact indices
OpIndex map_op(int token) {
    switch (token) {
        case plus:      return IDX_PLUS;
        case minus:     return IDX_MINUS;
        case mult:      return IDX_MULT;
        case divi:      return IDX_DIV;
        case assign_op: return IDX_ASSIGN;
        case gt:        return IDX_GT;
        case lt:        return IDX_LT;
        case eq:        return IDX_EQ;
        case ne:        return IDX_NE;
        default:        return -1; // Fallback
    }
}

// Helper to get string name for printing results
const char* token_to_string(int token) {
    switch (token) {
        case Tint:        return "Tint (Entero)";
        case Tfloat:      return "Tfloat (Decimal)";
        case plus:        return "+";
        case minus:       return "-";
        case mult:        return "*";
        case divi:        return "/";
        case assign_op:   return "=";
        case gt:          return ">";
        case lt:          return "<";
        case eq:          return "==";
        case ne:          return "!=";
        case TYPE_ERROR:  return "ERROR";
        default:          return "UNKNOWN";
    }
}

// Initialize the semantic cube according to your table rules
void init_semantic_cube() {
    // 1. Initialize all cells to TYPE_ERROR by default
    for (int i = 0; i < NUM_TYPES; i++) {
        for (int j = 0; j < NUM_OPS; j++) {
            for (int k = 0; k < NUM_TYPES; k++) {
                semantic_cube[i][j][k] = TYPE_ERROR;
            }
        }
    }

    // --- ADDITION (+) ---
    semantic_cube[IDX_INT][IDX_PLUS][IDX_INT]     = Tint;
    semantic_cube[IDX_INT][IDX_PLUS][IDX_FLOAT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_PLUS][IDX_INT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_PLUS][IDX_FLOAT] = Tfloat;

    // --- SUBTRACTION (-) ---
    semantic_cube[IDX_INT][IDX_MINUS][IDX_INT]     = Tint;
    semantic_cube[IDX_INT][IDX_MINUS][IDX_FLOAT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_MINUS][IDX_INT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_MINUS][IDX_FLOAT] = Tfloat;

    // --- MULTIPLICATION (*) ---
    semantic_cube[IDX_INT][IDX_MULT][IDX_INT]     = Tint;
    semantic_cube[IDX_INT][IDX_MULT][IDX_FLOAT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_MULT][IDX_INT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_MULT][IDX_FLOAT] = Tfloat;

    // --- DIVISION (/) ---
    semantic_cube[IDX_INT][IDX_DIV][IDX_INT]     = Tfloat;
    semantic_cube[IDX_INT][IDX_DIV][IDX_FLOAT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_DIV][IDX_INT]   = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_DIV][IDX_FLOAT] = Tfloat;

    // --- ASSIGNMENT (=) ---
    semantic_cube[IDX_INT][IDX_ASSIGN][IDX_INT]     = Tint;
    semantic_cube[IDX_INT][IDX_ASSIGN][IDX_FLOAT]   = TYPE_ERROR; // Int = Float -> ERROR
    semantic_cube[IDX_FLOAT][IDX_ASSIGN][IDX_FLOAT] = Tfloat;
    semantic_cube[IDX_FLOAT][IDX_ASSIGN][IDX_INT]   = Tfloat;   // Float = Int -> Float (coercion)

    // --- RELATIONAL OPERATORS (>, <, ==, !=) ---
    // All return Tint (acting as boolean in this language spec)
    OpIndex rel_ops[] = {IDX_GT, IDX_LT, IDX_EQ, IDX_NE};
    for (int o = 0; o < 4; o++) {
        OpIndex op = rel_ops[o];
        semantic_cube[IDX_INT][op][IDX_INT]     = Tint;
        semantic_cube[IDX_INT][op][IDX_FLOAT]   = Tint;
        semantic_cube[IDX_FLOAT][op][IDX_INT]   = Tint;
        semantic_cube[IDX_FLOAT][op][IDX_FLOAT] = Tint;
    }
}

// Cube lookup function
int semantic_cube_lookup(int left_type_token, int op_token, int right_type_token) {
    TypeIndex left = map_type(left_type_token);
    OpIndex op = map_op(op_token);
    TypeIndex right = map_type(right_type_token);

    if (left < 0 || op < 0 || right < 0) {
        return TYPE_ERROR;
    }

    return semantic_cube[left][op][right];
}

int main() {
    init_semantic_cube();

    // Test 1: Tint + Tfloat -> should yield Tfloat
    int res1 = semantic_cube_lookup(Tint, plus, Tfloat);
    printf("%s + %s = %s\n", token_to_string(Tint), token_to_string(Tfloat), token_to_string(res1));

    // Test 2: Tint = Tfloat -> should yield ERROR
    int res2 = semantic_cube_lookup(Tint, assign_op, Tfloat);
    printf("%s = %s = %s\n", token_to_string(Tint), token_to_string(Tfloat), token_to_string(res2));

    // Test 3: Tfloat = Tint -> should yield Tfloat (coercion)
    int res3 = semantic_cube_lookup(Tfloat, assign_op, Tint);
    printf("%s = %s = %s\n", token_to_string(Tfloat), token_to_string(Tint), token_to_string(res3));

    return 0;
}