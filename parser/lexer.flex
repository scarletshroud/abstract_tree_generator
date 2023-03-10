%option noyywrap

%{
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "../src/generator.h"

int line_cnt = 1;
void yyerror(char* str);

%}
%%

"Var"       { printf("Var\n");  return VAR; }
"Begin"     { printf("Begin\n"); return BBEGIN; }
"End"       { printf("End\n"); return EEND; }

";"         { printf(";\n"); return SEMICOLON; }
","         { printf(",\n"); return COMMA; }
"("         { printf("(\n"); return LBRACKET; }
")"         { printf(")\n"); return RBRACKET; }

"IF"        { printf("IF\n");   return IF; }
"THEN"      { printf("THEN\n"); return THEN; }
"ELSE"      { printf("ELSE\n"); return ELSE; }

"-"         { printf("-\n"); return MINUS; }
"+"         { printf("+\n"); return PLUS; }
"/"         { printf("/\n"); return DIV; }
"*"         { printf("*\n"); return MUL; }
">"         { printf(">\n"); return MORE; }
"<"         { printf("<\n"); return LESS; }
":="         { printf(":=\n"); return ASSIGN; }

"=="        { printf("equal\n"); return EQUALS; }

[a-zA-Z]+   {
                yylval.str = strdup(yytext);
                printf("%s\n", yylval.str);
                return ID;
            }

[0-9]+      {
                yylval.str = strdup(yytext);
                printf("%s\n", yylval.str);
                return CONST;
            }

"\n"        { printf("endline\n"); line_cnt++; }

[ \t\r\f]+  { }

.           { yyerror("Unrecognized character"); }
