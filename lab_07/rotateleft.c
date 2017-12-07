#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "helpfunc.h"

tree *rotateleft(tree *a)
{
  tree *b = a->right;
  a->right = b->left;
  b->left = a;
  b->parent = a->parent;
  if(a->parent != NULL)
  {
    if(((a->parent)->right)->name == a->name)
      (a->parent)->right = b;
    if(((a->parent)->left)->name == a->name)
      (a->parent)->left = b;
    a->parent = b->parent;
  }
  // if(a->parent != NULL)
  //   printf("%d\n", ((a->parent)->left)->name);
   printf("B: %d \n",b->name);
   printf("R: %d \n",(b->right)->name);
   printf("L: %d \n",(b->left)->name);
  fixheight(a);
  fixheight(b);
  
  return b;
}