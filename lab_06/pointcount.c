#include <stdio.h>

#include "main.h"

int printTree(struct tree_node *root, const char *dir, int level) 
{
	int max = -1;
    if (root) 
    {
        printf("lvl %d %s = %d\n", level, dir, root->name);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }

    return max;
}

void count_points(struct tree_node *tree)
{
	int max = 0;

	while (tree->right) 
	{
       tree = tree->right;
       max++;
    }
	
}