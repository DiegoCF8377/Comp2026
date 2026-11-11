#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int yylex(void) {
    char line[1024];
    char token_name[256];

    while (fgets(line, sizeof(line), stdin)) {

        if (sscanf(line, "%255s", token_name) != 1) {
            continue;
        }

        if (strcmp(token_name, "Tprogram") == 0) return Tprogram;
        if (strcmp(token_name, "Tmain") == 0) return Tmain;
        if (strcmp(token_name, "Tend") == 0) return Tend;
        if (strcmp(token_name, "Tvar") == 0) return Tvar;
        if (strcmp(token_name, "Tint") == 0) return Tint;
        if (strcmp(token_name, "Tfloat") == 0) return Tfloat;
        if (strcmp(token_name, "Tvoid") == 0) return Tvoid;
        if (strcmp(token_name, "Tif") == 0) return Tif;
        if (strcmp(token_name, "Telse") == 0) return Telse;
        if (strcmp(token_name, "Twhile") == 0) return Twhile;
        if (strcmp(token_name, "Tdo") == 0) return Tdo;
        if (strcmp(token_name, "Tprint") == 0) return Tprint;
        if (strcmp(token_name, "Tread") == 0) return Tread;
        if (strcmp(token_name, "Treturn") == 0) return Treturn;

        if (strcmp(token_name, "semicolon") == 0) return semicolon;
        if (strcmp(token_name, "colon") == 0) return colon;
        if (strcmp(token_name, "comma") == 0) return comma;
        if (strcmp(token_name, "assign_op") == 0) return assign_op;
        if (strcmp(token_name, "lbrace") == 0) return lbrace;
        if (strcmp(token_name, "rbrace") == 0) return rbrace;
        if (strcmp(token_name, "lparen") == 0) return lparen;
        if (strcmp(token_name, "rparen") == 0) return rparen;
        if (strcmp(token_name, "lbracket") == 0) return lbracket;
        if (strcmp(token_name, "rbracket") == 0) return rbracket;

        if (strcmp(token_name, "gt") == 0) return gt;
        if (strcmp(token_name, "lt") == 0) return lt;
        if (strcmp(token_name, "ne") == 0) return ne;
        if (strcmp(token_name, "eq") == 0) return eq;
        if (strcmp(token_name, "plus") == 0) return plus;
        if (strcmp(token_name, "minus") == 0) return minus;
        if (strcmp(token_name, "mult") == 0) return mult;
        if (strcmp(token_name, "divi") == 0) return divi;

        if (strcmp(token_name, "cte_string") == 0) return cte_string;
        if (strcmp(token_name, "cte_float") == 0) return cte_float;
        if (strcmp(token_name, "cte_int") == 0) return cte_int;
        if (strcmp(token_name, "id") == 0) return id;

        if (strcmp(token_name, "unknown") == 0) return unknown;

        fprintf(stderr, "Unknown token: %s\n", token_name);
        exit(EXIT_FAILURE);
    }

    return 0;
}