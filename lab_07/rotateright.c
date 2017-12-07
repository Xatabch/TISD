#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "helpfunc.h"

tree *rotateright(tree *a)
{
  tree *b = a->left;
  b->left = a->right;
  a->right = b;
  fixheight(b);
  fixheight(a);
  return a;
}