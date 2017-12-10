#include <stdio.h>

#include "main.h"
#include "insert.h"
#include "balance.h"
#include "balancetree.h"//балансировка дерева

void insert_avl(tree **p, int k)
{
  insert(p,k);
  (*p) = balance_tree(*p);
}