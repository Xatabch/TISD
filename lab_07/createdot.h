//this fuctions creates .gv files
#ifndef __CREATEDOT_H__
#define __CREATEDOT_H__
void to_dot(tree *tree, void *param);
void export_to_dot(FILE *f, const char *tree_name, tree *tree);
#endif