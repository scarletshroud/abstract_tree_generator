#include "generator.h"
#include "asm_printer.h"

static char **variable_list;
static uint64_t counter = 0;

static void add_variable_to_list(char *name) {
    static uint64_t current_size = 0;
    if (current_size == 0) {
        variable_list = (malloc(sizeof(char *) * 16));
        current_size += 16;
    }

    if (current_size == counter - 1) {
        variable_list = (realloc(variable_list, sizeof(uint64_t) * (current_size + 16)));
        current_size += 16;
    }

    variable_list[counter] = name;
    counter++;
}

struct abstract_tree *add_node(char *value, enum node_type type, struct abstract_tree *left, struct abstract_tree *right) {
    struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
    node->type = type;

    if (value == NULL) {
        node->value = NULL;
    } else {
        node->value = strdup(value);
    }

    node->left = left;
    node->right = right;

    if (type == Root) {
        print_tree(node, 0);
        print_assembly(node);
    }

    return node;
}

struct abstract_tree *add_variable(char* value, struct abstract_tree* variables) {
    struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
    node->type = Variables;

    if (value == NULL) {
        node->value = NULL;
    } else {
        node->value = strdup(value);
    }

    node->right = variables;

    add_variable_to_list(node->value);

    return node;
}

struct abstract_tree *add_assignment(char* name, struct abstract_tree *expression) {
    struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
    node->type = Operator;
    node->value = ":=";
    node->left = get_variable(name);
    node->right = expression;
    return node;
}

struct abstract_tree* add_condition(enum node_type type, struct abstract_tree *condition, struct abstract_tree *condition_block, struct abstract_tree *else_block) {
    struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
    node->type = type;
    node->value = NULL;
    node->left = condition;

    if (else_block) {
        node->right = add_node(NULL, Condition_Expression, condition_block, else_block);
    } else {
        node->right = add_node(NULL, Condition_Expression, condition_block, NULL);
    }

    return node;
}

//get variable by name
struct abstract_tree *get_variable(char *name) {
    for (uint64_t i = 0; i < counter; i++) {
        if (strcmp(variable_list[i], name) == 0) {
            struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
            node->type = Identifier;
            node->value = name;
            node->left = NULL;
            node->right = NULL;
            return node;
        }
    }

    fprintf(stderr, "Variable %s was nod declared!\n", name);
    exit(EXIT_FAILURE);
}

struct abstract_tree *get_constant(char *value) {
    struct abstract_tree *node = malloc(sizeof(struct abstract_tree));
    node->type = Identifier;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}