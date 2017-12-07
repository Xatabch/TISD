//apply tree
#ifndef __APPLY_H__
#define __APPLY_H__
void apply_pre(tree *tree, void (*f)(struct tree_node*, void*), void *arg);
void apply_in(tree *tree, void (*f)(struct tree_node*, void*), void *arg);
void apply_post(tree *tree, void (*f)(struct tree_node*, void*), void *arg);
void print(tree *node, void *param);
#endif