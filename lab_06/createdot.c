#include <stdio.h>

#include "main.h"
#include "apply.h"

void to_dot(struct tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->name, tree->left->name);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->name, tree->right->name);
}

void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(tree, to_dot, f);

    fprintf(f, "}\n");
}