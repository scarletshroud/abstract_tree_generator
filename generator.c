#include "generator.h"
#include <stddef.h>

struct abstract_tree* create_node(const char* value, enum node_type type, const struct abstract_tree* const left, const struct abstract_tree* const right) {
    struct abstract_tree* node = malloc(sizeof(struct abstract_tree));

    node->value = value;
    node->type = type;
    node->left = left;
    node->right = right;

    return node; 
}

struct abstract_tree* create_variable(const char* value, struct abstract_tree* const variable) {
    return create_node(value, VARIABLE, NULL, variable);
}

#define EQUALS "="
struct abstract_tree* create_assignment(const char* name, struct abstract_tree* expression) {
    return create_node(EQUALS, OPERATOR, , expression);
}

struct abstract_tree* create_condition(enum node_type type, struct abstract_tree* condition, struct abstract_tree* if_block, struct abstract_tree* else_block) {
    return (else_block != NULL) ? 
        create_node(NULL, type, condition, create_node(NULL, CONDITION, if_block, else_block))
        :
        create_node(NULL, type, condition, create_node(NULL, CONDITION, if_block, NULL))  
}


