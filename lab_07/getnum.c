#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев
#include "balance.h"//балансировка дерева

 //struct tree_node *apply_balance(tree *tree)
 // {
 //   if (tree == NULL)
 //         return NULL;

 //   apply_balance(tree->left);
 //   tree = balance(tree);
 //   apply_balance(tree->right);

 //   return tree;
 //  }

void apply(tree *tree)
{
    if (tree == NULL)
        return;

    tree->height = tree_height(tree);
    apply(tree->left);
    apply(tree->right);
}

tree* get_num(FILE *f)
{
  tree *root = NULL;
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    insert(&root, num);
    while(fscanf(f, "%d",&num) == 1)
    {
      insert(&root, num);
    }
  }

  apply(root);

  return root;
}

tree *get_avl_tree(FILE *f)
{
  tree *root = NULL;
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    insert(&root, num);
    apply(root);
    root = balance(root);
    while(fscanf(f, "%d",&num) == 1)
    {
      insert(&root, num);
      apply(root);
      root = balance(root);
    }
  }

  apply(root);

  return root;  
}