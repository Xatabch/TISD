//structs
#ifndef __MAIN_H__
#define __MAIN_H__
struct tree_node
{
  int name;

  //меньшие
  struct tree_node *left;
  //большие
  struct tree_node *right;
};
#endif