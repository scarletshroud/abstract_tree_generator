%{
#include <stdio.h>
%}

%%
    "Var"   { printf("Var\n");      return VAR; }
    "Begin" { printf("Begin\n");    return BEGIN; }
    "End"   { printf("End\n");      return END; }

    "IF"    { printf("IF\n");   return IF; }
    "ELSE"  { printf("ELSE\n"); return ELSE; }

    ":="    { printf(":=\n");   return ASSIGN; }

    ","     { printf(",\n");    return COMMA; }
    "("     { printf("(\n");    return LBRACKET; }
    ")"     { printf("(\n");    return RBRACKET; }

    "-"     { printf("-\n");    return MINUS; }
    
    "+"     { printf("+\n");    return PLUS; }
    "*"     { printf("*\n");    return MUL;}
    "/"     { printf("/\n");    return SLASH;}
    ">>"    { printf(">>\n");   return RSHIFT;}
    "<<"    { printf("<<\n");   return LSHIFT;}
    ">"     { printf(">\n");    return MORE;}
    "<"     { printf("<\n");    return LESS;}
    "="     { printf("=\n");    return EQUALS;}

    [a-zA-Z]+   {

                }

    [0-9]+      {

                }

%%
