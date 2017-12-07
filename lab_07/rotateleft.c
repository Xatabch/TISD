#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "helpfunc.h"

tree *rotateleft(tree *a)
{
  tree *b = a->right;
  a->right = b->left;
  b->left = a;
  fixheight(a);
  fixheight(b);
  
  return b;
}