#ifndef _ASM_PRINTER_H_
#define _ASM_PRINTER_H_

#include "abstract_tree.h"

void print_tree(struct abstract_tree *node, int offset);
void print_assembly(struct abstract_tree *root);

#endif
