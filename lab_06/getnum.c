#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево

struct tree_node* get_num(FILE *f)
{
  struct tree_node *root = NULL;
  struct tree_node *node;
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    node = create_node(num);
    root = insert(root, node);
    while(fscanf(f, "%d",&num) == 1)
    {
      node = create_node(num);
      root = insert(root, node);
    }
  }

  return root;
}