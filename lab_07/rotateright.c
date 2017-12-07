#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "helpfunc.h"

tree *rotateright(tree *a)
{
  tree *b = a->left;
  a->left = b->right;
  b->right = a;
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
  //   printf("%d\n", ((a->parent)->right)->name);
   printf("B: %d \n",b->name);
   printf("L: %d \n",(b->right)->name);
   printf("R: %d \n",(b->left)->name);
  fixheight(b);
  fixheight(a);

  return b;
}