#include "asm_printer.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define STEP 5

static void print_assembly_operators(struct abstract_tree *node);

static void print_assembly_assign(struct abstract_tree *node);

static void print_assembly_expression(struct abstract_tree *node, char *name);

static void print_assembly_if(struct abstract_tree *node);

static char* create_tmp();

static char* create_label();

static char *get_node_type(struct abstract_tree *node);

void print_tree(struct abstract_tree *node, int offset) {
    if (node == NULL) {
        return;
    }

    offset += STEP;
    print_tree(node->right, offset);
    for (int i = STEP; i < offset; i++) {
        if (offset > STEP && i >= offset - STEP) {
            if (i == offset - STEP) {
                printf("+");
            } else {
                printf("-");
            }
        } else {
            printf(" ");
        }
    }

    char* node_type = get_node_type(node);

    if (node_type) {
        printf("[%s]", node_type);
    } else {
        printf("Happened something wrong");
    }
    if (node->value) {
        printf("(%s)\n", node->value);
    } else {
        printf("(NULL)\n");
    }

    print_tree(node->left, offset);
}


void print_assembly(struct abstract_tree *root) {
    if (!root) {
        return;
    }

    if (!root->right) {
        printf("Empty body\n");
        return;
    }

    print_assembly_operators(root->right->left);
}

void print_assembly_operators(struct abstract_tree *node) {
    if (!node) {
        return;
    }

    switch (node->type) {
        case Operators:
            print_assembly_operators(node->left);
            print_assembly_operators(node->right);
            break;

        case Operator:
            print_assembly_assign(node);
            break;

        case If:
        case If_Else:
            print_assembly_if(node);
            break;
        default:
            printf("OPERATORS ERROR\n");
            break;
    }
}

void print_assembly_assign(struct abstract_tree *node) {
    if (!node) {
        return;
    }

    struct abstract_tree *variable = node->left;
    struct abstract_tree *expression = node->right;

    char *tmp_name;

    switch (expression->type) {
        case Const:
        case Identifier:
            printf("%s %s %s\n", variable->value, node->value, expression->value);
            break;

        case Expression:
            tmp_name = create_tmp();
            print_assembly_expression(expression, tmp_name);
            printf("%s %s %s\n", variable->value, node->value, tmp_name);
            break;

        default:
            printf("ASSIGN ERROR\n");
            break;
    }
}

void print_assembly_expression(struct abstract_tree *node, char *name) {
    if (!node) {
        return;
    }

    struct abstract_tree *left = node->left;
    struct abstract_tree *right = node->right;

    char *tmp_name = NULL;

    if (left) {
        switch (left->type) {
            case Expression:
                tmp_name = create_tmp();
                print_assembly_expression(left, tmp_name);
                break;

            case Const:
            case Identifier:
                tmp_name = left->value;
                break;

            default:
                printf("EXPRESSION ERROR!\n");
                tmp_name = "EXPRESSION ERROR!";
                break;
        }
    }
    char *tmp_name_2 = NULL;

    if (right) {
        switch (right->type) {
            case Expression:
                tmp_name_2 = create_tmp();
                print_assembly_expression(right, tmp_name_2);
                break;

            case Const:
            case Identifier:
                tmp_name_2 = right->value;
                break;

            default:
                printf("EXPRESSION ERROR!\n");
                tmp_name_2 = "EXPRESSION ERROR!";
                break;
        }
    }

    if (strcmp(node->value, "-") == 0
        || strcmp(node->value, "+") == 0
        || strcmp(node->value, "*") == 0
        || strcmp(node->value, "/") == 0
        || strcmp(node->value, ">") == 0
        || strcmp(node->value, "<") == 0
        || strcmp(node->value, "==") == 0) {
        printf("%s = %s %s %s\n", name, tmp_name, node->value, tmp_name_2);
    } else if (strcmp(node->value, "MINUS") == 0) {
        printf("%s = %s %s\n", name, node->value, tmp_name_2);
    } else {
        printf("EXPRESSION ERROR!\n");
    }

}

void print_assembly_if(struct abstract_tree *node) {
    if (!node) {
        return;
    }

    char *tmp_name = create_tmp();
    char *l = create_label();
    char *end_l = create_label();

    print_assembly_expression(node->left, tmp_name);
    printf("cmp_true %s %s\n", tmp_name, l);
    print_assembly_operators(node->right->left);
    printf("goto %s\n", end_l);
    printf("%s:\n", l);
    if (node->right->right) {
        print_assembly_operators(node->right->right);
    }
    printf("%s:\n", end_l);
}

char* create_tmp() {
    static int tmp_count = 0;
    char *name = malloc(sizeof(char) * 16);
    snprintf(name, 16, "tmp_%d", tmp_count);
    tmp_count += 1;
    return name;
}

char* create_label() {
    static int label_count = 0;
    char *l = malloc(sizeof(char) * 16);
    snprintf(l, 16, "label_%d", label_count);
    label_count += 1;
    return l;
}

char *get_node_type(struct abstract_tree *node) {
    if (node == NULL) {
        return NULL;
    }

    switch (node->type) {
        case Root:
            return "Root";

        case Variables_Declaration:
            return "Variables_Declaration";

        case Variables:
            return "Variables";

        case Identifier:
            return "Identifier";

        case Program_Body:
            return "Program_Body";

        case Expression:
            return "Expression";

        case Operators:
            return "Operators";

        case Operator:
            return "Operator";

        case Const:
            return "Const";

        case If:
            return "If";

        case If_Else:
            return "If_Else";

        case Condition_Expression:
            return "Condition_Expression";

        default:
            return NULL;
    }
}


