//structs
#ifndef __MAIN_H__
#define __MAIN_H__
typedef struct tree_node tree;
struct tree_node
{
  int name;

  unsigned char height;//высота данного поддерева
  //меньшие
  struct tree_node *left;
  //большие
  struct tree_node *right;
  //родитель
  struct tree_node *parent;
};

struct avl_node
{
  int name;
  unsigned char height;
  struct avl_node *left;
  struct avl_node *right;
};
#endif