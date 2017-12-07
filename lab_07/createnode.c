#include <stdio.h>
#include <stdlib.h>

#include "main.h"

tree* create_node(const int num, tree *parent)
{
    tree *node;

    node = malloc(sizeof(tree));
    
    if (node)
    {
        node->name = num;

        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
    }

    return node;
}