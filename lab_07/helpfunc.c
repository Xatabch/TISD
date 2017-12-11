#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

int max(int h1, int h2)
{
  return (h1>h2?h1:h2);
}

unsigned char tree_height(tree *p)
{
  int h1=0,h2=0;

  if(p==NULL)
    return 0;
  if(p->left)
    h1=tree_height(p->left);
  if(p->right)
    h2=tree_height(p->right);

  return(max(h1,h2)+1);
}

unsigned char height(tree *p)
{
  if(p)
    return (p->height);
  else
    return 1;
}

void fixheight(tree *p)
{
  unsigned char hl = height(p->left);
  unsigned char hr = height(p->right);
  p->height = (hl>hr?hl:hr) + 1;
}

int bfactor(tree *p)
{
  //printf("%d %d\n",p->name, height(p->right) - height(p->left));
  return (height(p->right) - height(p->left));
}
