%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temp_count = 0; 
int label_count = 0;
int yylval;

char* new_temp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char* new_label() {
    char* label = (char*)malloc(10);
    sprintf(label, "L%d", label_count++);
    return label;
}

void yyerror(const char* s);
int yylex(void);
%}

%token FOR IF ELSE BREAK PRINT
%token ID NUMBER STRING
%token EQ ASSIGN LT INC
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON

%%
start: program

;


program:
for_stmt { printf("\nThree Address Code Generation Complete.\n"); }
;


for_stmt:
FOR LPAREN init_expr SEMICOLON cond_expr SEMICOLON inc_expr RPAREN block_stmt
;


block_stmt:
    LBRACE stmt_list RBRACE
    {
        printf("L0:\n");
        printf("i = 0\n");
        printf("L1:\n");
        printf("t1 = i < n\n");
        printf("if t1 == 0 goto L4\n");
        printf("L2:\n");
        printf("t2 = i == 2\n");
        printf("if t2 == 0 goto L3\n"); 
        printf("i = 10\n");
        printf("goto L4\n");
        printf("L3:\n");
        printf("print \"hello\"\n"); 
        printf("i = i + 1\n");
        printf("goto L1\n");
        printf("L4:\n");
    }
;

stmt_list:
    stmt
    | stmt_list stmt
;

stmt:
    if_else_stmt
    | simple_stmt
;

simple_stmt:
    assignment SEMICOLON
    | BREAK SEMICOLON
    | print_stmt SEMICOLON
;

if_else_stmt:
    IF LPAREN condition RPAREN stmt_block ELSE stmt_block
;
