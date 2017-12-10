//delete list
#ifndef __DELETE_H__
#define __DELETE_H__
struct tree_node *getMaxNode(struct tree_node *root);
void deleteValue(struct tree_node *root,const int value);
void removeNodeByPtr(struct tree_node *target);
#endif