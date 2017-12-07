#include <stdio.h>

#include "main.h"
#include "insert.h"
#include "balance.h"

void insert_avl(tree **p, int k)
{
  insert(&(*p),k);

  //(*p) = balance((*p));
}