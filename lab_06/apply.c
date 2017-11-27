#include <stdio.h>

#include "main.h"

void apply_pre(struct tree_node *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    //f(tree, arg);
    apply_pre(tree->right, f, arg);
    //f(tree, arg);
}

void print(struct tree_node *node, void *param)
{
    const char *fmt = param;
    
    printf(fmt, node->name);
}