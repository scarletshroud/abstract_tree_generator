#ifndef _ABSTRACT_TREE_H_
#define _ABSTRACT_TREE_H_

enum node_type {
    Root,
    Variables_Declaration,
    Variables,
    Identifier,
    Program_Body,
    Expression,
    Operators,
    Operator,
    Const,
    If,
    If_Else,
    Condition_Expression,
    Undefined
};

struct abstract_tree {
    char *value;
    enum node_type type;
    struct abstract_tree *left;
    struct abstract_tree *right;
};

#endif