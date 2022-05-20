#ifndef _GENERATOR_H_
#define _GENERATOR_H_

enum node_type {
    PROGRAM, 
    VARIABLE_DECLARATION, 
    OPERATORS,
    OPERATOR,
    VARIABLES,
    VARIABLE,
    IDENTIFIER,
    EXPRESSION,
    CONDITION,
    CONST,
};

struct abstract_tree {
    char* value;
    enum node_type type;
    struct abstract_tree* left; 
    struct abstract_tree* right;
};

struct abstract_tree* create_node(const char* value, enum node_type type, const struct abstract_tree* const left, const struct abstract_tree* const right);
struct abstract_tree* create_variable(const char* value, struct abstract_tree* const variable);
struct abstract_tree* create_assignment(const char* name, struct abstract_tree* expression);
struct abstract_tree* create_condition(enum node_type type, struct abstract_tree* condition, struct abstract_tree* if_block, struct abstract_tree* else_block); 


#endif