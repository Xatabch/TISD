#include <stdio.h>

#include "main.h"

struct tree_node* lookup(struct tree_node *tree, const int name)
{
    int cmp;

    while (tree != NULL)
    {
		cmp = (name - tree->name);

        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}