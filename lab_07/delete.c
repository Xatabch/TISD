#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "find.h"
#include "apply.h"
#include "balancetree.h"//балансировка дерева

void removeNodeByPtr(struct tree_node *target);

struct tree_node *getMaxNode(struct tree_node *root) 
{
    while (root->right) {
        root = root->right;
    }
    return root;
}

void deleteValue(struct tree_node *root,const int value) 
{   
    int sravneniya = 0;
    struct tree_node *target = lookup(root, value,&sravneniya);
    removeNodeByPtr(target);
}

void removeNodeByPtr(struct tree_node *target) 
{
    if (target->left && target->right) 
    {
        struct tree_node *localMax = getMaxNode(target->left);
        target->name = localMax->name;
        removeNodeByPtr(localMax);
        return;
    } 

    else if (target->left) 
    {
        if (target == target->parent->left) 
            target->parent->left = target->left; 
        else 
            target->parent->right = target->left;
    } 
    else if (target->right) 
    {
        if (target == target->parent->right) 
            target->parent->right = target->right;
        else 
            target->parent->left = target->right;
    } 
    else 
    {
        if (target == target->parent->left) 
            target->parent->left = NULL; 
        else 
            target->parent->right = NULL;
    }

    free(target);
}