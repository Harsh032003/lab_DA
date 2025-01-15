%{
#include <stdio.h>
%}
%token NUM VARIABLE
%left '+' '-'
%left '*'
%left '/'
%right NEGATIVE
%%
S: E { printf("\n"); }
 ;
E: E '+' E { printf("+"); }
 | E '*' E { printf("*"); }
 | E '-' E { printf("-"); }
 | E '/' E { printf("/"); }
 | '(' E ')'
 | '-' E %prec NEGATIVE { printf("-"); }
 | NUM { printf("%d", yylval); }
 | VARIABLE { printf("%c", yylval); }
 ;
%%
int main() {
 yyparse();
}
int yyerror(char *msg) {
 return printf("error YACC: %s\n", msg);
}
