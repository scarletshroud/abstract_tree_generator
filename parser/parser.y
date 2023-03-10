%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/generator.h"
extern int yylex();
extern char* yyval;
extern int line_cnt;
void yyerror(char* str);
%}

%token VAR BBEGIN EEND
%token SEMICOLON COMMA LBRACKET RBRACKET
%token IF THEN ELSE
%token MINUS
%token PLUS MUL DIV LESS MORE EQUALS
%token ASSIGN
%token ID CONST

%start program

%right ASSIGN
%left PLUS MINUS
%left MUL DIV

%union {
    struct abstract_tree *tree;
    char *str;
}

%type<tree> program program_body variables_declaration variables operators operator expression subexpression
%type<str> ID CONST
%%
program:
    variables_declaration program_body { $$ = add_node(NULL, Root, $1, $2); }
    ;

program_body:
    operators { $$ = add_node(NULL, Program_Body, $1, NULL); }
    ;

variables_declaration:
    VAR variables SEMICOLON { $$ = add_node(NULL, Variables_Declaration, NULL, $2); }
    ;

variables:
    ID { $$ = add_variable($1, NULL); }
    | ID COMMA variables { $$ = add_variable($1, $3); }
    ;

operators:
    operator { $$ = $1; }
    | operator operators { $$ = add_node(NULL, Operators, $1, $2); }
    ;

operator:
    ID ASSIGN expression SEMICOLON { $$ = add_assignment($1, $3); }
    | BBEGIN operators EEND { $$ = add_node(NULL, Operators, $2, NULL); }
    | IF expression THEN operator { $$ = add_condition(If, $2, $4, NULL); }
    | IF expression THEN operator ELSE operator { $$ = add_condition(If_Else, $2, $4, $6); }
    ;

expression:
    MINUS subexpression { $$ = add_node("MINUS", Expression, NULL, $2); }
    | subexpression { $$ = $1; }
    ;

subexpression:
    LBRACKET expression RBRACKET { $$ = $2; }
    | ID { $$ = get_variable($1); }
    | CONST { $$ = get_constant($1); }
    | subexpression MINUS subexpression { $$ = add_node( "-", Expression, $1, $3); }
    | subexpression PLUS subexpression { $$ = add_node("+", Expression, $1, $3); }
    | subexpression MUL subexpression { $$ = add_node("*", Expression, $1, $3); }
    | subexpression DIV subexpression { $$ = add_node("/", Expression, $1, $3); }
    | subexpression MORE subexpression { $$ = add_node(">", Expression, $1, $3); }
    | subexpression LESS subexpression { $$ = add_node("<", Expression, $1, $3); }
    | subexpression EQUALS subexpression { $$ = add_node("==", Expression, $1, $3); }
    ;

%%

void yyerror(char* str) {
    fprintf(stderr, "Syntax error at line %d\n", line_cnt);
    exit(1);
}

int main(int argc, char **argv) {
    return yyparse();
}

