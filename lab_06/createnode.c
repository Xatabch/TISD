#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct tree_node* create_node(const char *name)
{
    struct tree_node *node;

    node = malloc(sizeof(struct tree_node));
    
    if (node)
    {
        node->name = name;

        node->left = NULL;
        node->right = NULL;
    }

    return node;
}