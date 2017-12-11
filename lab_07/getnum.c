#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев
#include "balance.h"//балансировка дерева
#include "balancetree.h"
#include "find.h"//поиск в бинарном дереве поиска
#include "apply.h"//пямой обход дерева
#include "find.h"//поиск в бинарном дереве поиска
#include "tick.h"//замер времени.

void apply(tree *tree)
{   
    if (tree == NULL)
        return;

    apply(tree->left);
    tree->height = tree_height(tree);
    apply(tree->right);
}

void tree_middle_time(tree *tree,int *time,int *sravn,struct tree_node *tree2)
{   
    int sravneniya = 0;
    unsigned long long tb, te;

    if (tree == NULL)
        return;

    tb = tick();
    lookup(tree2,tree->name,&sravneniya);
    te = tick();
    (*sravn) = (*sravn) + sravneniya;
    (*time) = (*time) + (int)(te-tb);

    tree_middle_time(tree->left,time,sravn,tree2);
    tree_middle_time(tree->right,time,sravn,tree2);
}


tree* get_num(FILE *f,int *time,int *sravn)
{
  tree *root = NULL;
  int num;
  (*time) = 0;
  int size = 0;
  (*sravn) = 0;

  if(fscanf(f,"%d",&num) == 1)
  {
    insert(&root, num);
    size++;
    while(fscanf(f, "%d",&num) == 1)
    {
      insert(&root, num);
      size++;
    }
  }

  tree_middle_time(root,time,sravn,root);

  (*time) = (*time)/size;
  (*sravn) = (*sravn)/size;

  return root;
}











tree* rotateright1(tree* p) // правый поворот вокруг p
{
  tree* q = p->left;
  p->left = q->right;
  q->right = p;
  fixheight(p);
  fixheight(q);
  return q;
}

tree* rotateleft1(tree* q) // левый поворот вокруг q
{
  tree* p = q->right;
  q->right = p->left;
  p->left = q;
  fixheight(q);
  fixheight(p);
  return p;
}

tree* balance1(tree* p) // балансировка узла p
{
  fixheight(p);
  if( bfactor(p) == 2 )
  {;
    if( bfactor(p->right) < 0 )
      p->right = rotateright1(p->right);
    return rotateleft1(p);
  }
  if( bfactor(p)==-2 )
  {
    if( bfactor(p->left) > 0  )
      p->left = rotateleft1(p->left);
    return rotateright1(p);
  }
  return p; // балансировка не нужна
}

tree *get_avl_tree(FILE *f)
{
  tree *root = NULL;
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    insert(&root, num);
    apply(root);
    // apply_pre(root,print,"[%d %d]");
    // printf("\n----\n");
    root = balance1(root);
    while(fscanf(f, "%d",&num) == 1)
    {
      insert(&root, num);
      apply(root);
      // apply_pre(root,print,"[%d %d]");
      // printf("\n----\n");
      root = balance1(root);
    }
  }

  apply(root);
  root = balance1(root);

  return root;  
}