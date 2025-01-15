%{
#include <stdio.h>
int flag = 0;
%}

%option noyywrap

%%
[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}   {printf("Valid email: %s\n", yytext);flag=1;}

. {}

\n {return 1;}
%%

int main() {
    printf("Enter email addresses (Ctrl+D to stop):\n");
    yylex();
    if (flag == 0) {
        printf("Invalid Email Address");
    }
    return 0;
}