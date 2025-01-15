%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaration for yylex
int yylex();

// Declaration for yyerror
void yyerror(const char *s);

// Counter for temporary variable generation
int tempCount = 0;

// Function to create a new temporary variable
char* newTemp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}
%}

%union {
    int ival;
    char* sval;
}

%token <sval> IDENTIFIER
%token <ival> NUMBER
%token INT RETURN
%token ASSIGN PLUS SEMICOLON LPAREN RPAREN

%type <sval> expr assignment

// Define precedence and associativity
%left PLUS

%%

program:
    program statement
    | /* empty */
    ;

statement:
    declaration
    | assignment
    | return_statement
    ;

declaration:
    INT IDENTIFIER SEMICOLON
    ;

assignment:
    IDENTIFIER ASSIGN expr SEMICOLON {
        printf("%s = %s\n", $1, $3);
    }
    ;

return_statement:
    RETURN expr SEMICOLON {
        printf("return %s\n", $2);
    }
    ;

expr:
    expr PLUS expr {
        char* temp = newTemp();
        printf("%s = %s + %s\n", temp, $1, $3);
        $$ = temp;
    }
    | IDENTIFIER {
        $$ = strdup($1);
    }
    | NUMBER {
        char* temp = newTemp();
        printf("%s = %d\n", temp, $1);
        $$ = temp;
    }
    ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
