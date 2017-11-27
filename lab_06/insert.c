#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

#include "main.h"
#include "createnode.h"

void insert(struct tree_node **head, int value) 
{
    struct tree_node *tmp = NULL;
    if (*head == NULL) 
    {
        *head = create_node(value, NULL);
        return;
    }
     
    tmp = *head;
    while (tmp) 
    {
        if (CMP_GT(value, tmp->name)) 
        {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } 
            else 
            {
                tmp->right = create_node(value, tmp);
                return;
            }
        } 
        else if (CMP_LT(value, tmp->name)) 
        {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } 
            else 
            {
                tmp->left = create_node(value, tmp);
                return;
            }
        } 
        else 
            exit(2);
    }
}