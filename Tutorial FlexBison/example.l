%{
#include "example.tab.h"
%}

%%
[0-9]+      { return NUMBER; }
[ \t\n]+    { /* ignore whitespace */ }
"+"         { return '+'; }
"-"         { return '-'; }
.           { /* ignore unknown characters */ }
%%