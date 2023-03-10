#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "abstract_tree.h"

struct abstract_tree* add_node(char* value, enum node_type type, struct abstract_tree* left, struct abstract_tree* right);
struct abstract_tree* add_variable(char *value, struct abstract_tree* variables);
struct abstract_tree* add_assignment(char *name, struct abstract_tree* expression);
struct abstract_tree* add_condition(enum node_type type, struct abstract_tree* condition, struct abstract_tree* condition_block, struct abstract_tree* else_block);

struct abstract_tree* get_variable(char *name);
struct abstract_tree* get_constant(char *value);

#endif //ABSTRACT_TREE_UTIL_H