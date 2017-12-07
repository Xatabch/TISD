#include <stdio.h>

#include "main.h"
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев

void apply_pre(tree *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void apply_in(tree *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    apply_in(tree->left, f, arg);
    f(tree, arg);
    apply_in(tree->right, f, arg);
}

void apply_post(tree *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    apply_post(tree->left, f, arg);
    apply_post(tree->right, f, arg);
    f(tree, arg);
}

void print(tree *node, void *param)
{
    const char *fmt = param;
    
    printf(fmt, node->name);
}