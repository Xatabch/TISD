#include <stdio.h>

#include "main.h" //структуры
#include "balance.h"//балансировка дерева

tree *apply_balance(tree *_tree,int *res)
{
  tree *tree = _tree;
  if (tree == NULL)
        return NULL;
  int check = 0;
  apply_balance(tree->left,res);
  tree = balance(tree,&check);
  if(check == 1)
    *res = 1;
  apply_balance(tree->right,res); 

  return tree;
}

tree *balance_tree(tree *root)
{
  int res = 0;
  while(1)
  { 
    res = 0;
    root = apply_balance(root,&res);
    if(res == 0)
      break;
  }

  return root;
}