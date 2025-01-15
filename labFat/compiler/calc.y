%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // For abs()

// Function prototype for Flex
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left '(' ')'
%right ABS

%%
input:
    /* empty */
    | input line
    ;

line:
    '\n'
    | expression '\n' { printf("Result: %d\n", $1); }
    ;

expression:
    NUMBER { $$ = $1; }
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { 
        if ($3 == 0) {
            yyerror("Division by zero");
            exit(1);
        } else {
            $$ = $1 / $3; 
        }
    }
    | '(' expression ')' { $$ = $2; }
    | ABS '(' expression ')' { $$ = abs($3); }  // Absolute value operation
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
