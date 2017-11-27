#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево

struct tree_node* get_num(FILE *f)
{
  struct tree_node *root = NULL;
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    insert(&root, num);
    while(fscanf(f, "%d",&num) == 1)
    {
      insert(&root, num);
    }
  }

  return root;
}