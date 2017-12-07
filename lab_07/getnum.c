#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев

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