//this fuctions creates .gv files
#ifndef __CREATEDOT_H__
#define __CREATEDOT_H__
void to_dot(struct tree_node *tree, void *param);
void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree);
#endif