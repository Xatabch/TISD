#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "main.h"

struct tree_node* insert(struct tree_node *tree, struct tree_node *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = (node->name - tree->name);
    if (cmp == 0)
    {
        assert(0);
    }
    else if (cmp < 0)
    {
        tree->left = insert(tree->left, node);
    }
    else
    {
        tree->right = insert(tree->right, node);
    }

    return tree;
}