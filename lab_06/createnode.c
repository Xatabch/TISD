#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct tree_node* create_node(const int num, struct tree_node *parent)
{
    struct tree_node *node;

    node = malloc(sizeof(struct tree_node));
    
    if (node)
    {
        node->name = num;

        node->left = NULL;
        node->right = NULL;
        node->parent = parent;
    }

    return node;
}