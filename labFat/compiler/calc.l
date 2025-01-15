%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[\t ]+      /* ignore whitespace */
\n          return '\n';
"abs"       return ABS;         // Recognize the 'abs' keyword
.           return yytext[0];
%%

int yywrap(void) {
    return 1;
}
