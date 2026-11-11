%{
#include <stdio.h>
#include <stdlib.h>
#include "PatitoParser.tab.h"
%}

%option noyywrap
%option yylineno


%%

[ \t\r\n]+              ;

"program"               { return(Tprogram); }
"main"                  { return(Tmain); }
"end"                   { return(Tend); }
"var"                   { return(Tvar); }
"int"                   { return(Tint); }
"float"                 { return(Tfloat); }
"void"                  { return(Tvoid); }
"if"                    { return(Tif); }
"else"                  { return(Telse); }
"while"                 { return(Twhile); }
"do"                    { return(Tdo); }
"print"                 { return(Tprint); }
"read"                  { return(Tread); }
"return"                { return(Treturn); }

";"                     { return(semicolon); }
":"                     { return(colon); }
","                     { return(comma); }
"="                     { return(assign_op); }
"{"                     { return(lbrace); }
"}"                     { return(rbrace); }
"("                     { return(lparen); }
")"                     { return(rparen); }
"["                     { return(lbracket); }
"]"                     { return(rbracket); }

">"                     { return(gt); }
"<"                     { return(lt); }
"!="                    { return(ne); }
"=="                    { return(eq); }
"+"                     { return(plus); }
"-"                     { return(minus); }
"*"                     { return(mult); }
"/"                     { return(divi); }


\"[^\"]*\" {
    yylval.str = strdup(yytext);
    return cte_string;
    }

[0-9]+\.[0-9]+ {
    yylval.str = strdup(yytext);
    return cte_float;
    }

[0-9]+ {
    yylval.str = strdup(yytext);
    return cte_int;
    }

[a-zA-Z][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return id;
    }

. {
    fprintf(stderr,
        "[LEXICAL ERROR] Line %d: Unexpected character '%s'\n",
        yylineno, yytext);

    return unknown;
}

%%