#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "helpfunc.h"

tree *rotateleft(tree *a)
{
  tree *parent = a->parent;
  tree *b = a->right;

  a->right = b->left;
  b->left = a;
  b->parent = a->parent;
  if(a->parent != NULL)
  {
    if(parent->right)
      if(((parent)->right)->name == a->name)
        (a->parent)->right = b;

    if(parent->left)
      if(((parent)->left)->name == a->name)
        (a->parent)->left = b;
    a->parent = b->parent;
  }
  
  fixheight(a);
  fixheight(b);
  
  return b;
}