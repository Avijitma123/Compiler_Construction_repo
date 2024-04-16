%{
#include <stdio.h>
%}

%%

0|1|10|010|011|110|1001|10110|01010  { printf("Matched token: %s\n", yytext); }
.                                     { printf("Invalid token: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

