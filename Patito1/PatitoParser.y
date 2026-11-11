%{
#include <stdio.h>
void yyerror(const char *s);
int yylex(void);
%}

%define parse.trace
%define parse.error detailed


%token Tprogram
%token Tmain
%token Tend
%token Tvar
%token Tint
%token Tfloat
%token Tvoid
%token Tif
%token Telse
%token Twhile
%token Tdo
%token Tprint
%token Tread
%token Treturn

%token semicolon
%token colon
%token comma
%token assign_op
%token lbrace
%token rbrace
%token lparen
%token rparen
%token lbracket
%token rbracket

%token gt
%token lt
%token ne
%token eq
%token plus
%token minus
%token mult
%token divi

%token cte_string
%token cte_float
%token cte_int
%token id

%token unknown

%%
PROGRAMA : Tprogram id semicolon VarsOpcional ProgramaFuncs Tmain BODY Tend;

ProgramaFuncs
    : FUNCS ProgramaFuncs
    | %empty
    ;

EXPRESION : EXP Simb;

Simb
    : gt EXP
    | lt EXP
    | ne EXP
    | %empty
    ;

ASSIGN : id assign_op EXPRESION semicolon;

CTE : cte_int | cte_float;

STATEMENT
    : RETURN
    | ASSIGN
    | CONDITION
    | CYCLE
    | F_CALL
    | PRINT
    | READ
    | lbracket StatementInBrackets rbracket
    ;

StatementInBrackets
    : %empty
    | STATEMENT StatementInBrackets
    ;

BODY : lbrace BodyCont rbrace;

BodyCont
    : STATEMENT BodyCont
    | %empty
    ;

EXP
    : EXP plus TERMINO
    | EXP minus TERMINO
    | TERMINO
    ;

TERMINO
    : TERMINO mult FACTOR
    | TERMINO divi FACTOR
    | FACTOR
    ;

InnerF_CALL : id lparen FCallInitial rparen;

F_CALL : InnerF_CALL semicolon;

FCallInitial
    : FCallContinuation
    | %empty
    ;

FCallContinuation : EXPRESION FCallMultiple;

FCallMultiple
    : comma FCallContinuation
    | %empty
    ;

RETURN : Treturn EXPRESION semicolon;

READ : Tread lparen id rparen semicolon;

VarsOpcional
    : VARS
    | %empty
    ;

VARS : Tvar VarStart;

VarStart
    : VarDeclare colon TYPE semicolon VarStart
    | VarDeclare colon TYPE semicolon
    ;

VarDeclare
    : id VarContinuation
    ;

VarContinuation
    : comma VarDeclare
    | %empty
    ;

TYPE
    : Tint
    | Tfloat
    ;

PRINT
    : Tprint lparen PrintContenido rparen semicolon
    ;

PrintContenido
    : EXPRESION PrintContenidoContinuacion
    | cte_string PrintContenidoContinuacion
    ;

PrintContenidoContinuacion
    : comma PrintContenido
    | %empty
    ;

CYCLE : Twhile lparen EXPRESION rparen Tdo STATEMENT semicolon;

CONDITION : Tif lparen EXPRESION rparen STATEMENT ConditionElse semicolon;

ConditionElse
    : Telse STATEMENT
    | %empty
    ;

FACTOR : FactorStart;

FactorStart
    : lparen EXPRESION rparen
    | InnerF_CALL
    | FactorContinuacion
    | plus FactorContinuacion
    | minus FactorContinuacion
    ;

FactorContinuacion
    : id
    | CTE
    ;

FUNCS
    : FuncsType id lparen FuncsIDsOpcional rparen
      lbracket VarsOpcional BODY rbracket semicolon
    ;

FuncsType
    : Tvoid
    | TYPE
    ;

FuncsIDsOpcional
    : FuncsIDs
    | %empty
    ;

FuncsIDs
    : id colon TYPE FuncsIDsContinuacion
    ;

FuncsIDsContinuacion
    : comma FuncsIDs
    | %empty
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "\n[SYNTAX ERROR] %s\n", s);
}

int main() {

    yydebug = 0;

    int result = yyparse();

    if (result == 0) {
        printf("\nSyntax analysis successful!\n");
    } else {
        printf("\nSyntax analysis failed.\n");
    }

    return result;
}