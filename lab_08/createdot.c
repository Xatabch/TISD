#include <stdio.h>

#include "main.h"
#include "checktree.h"

void to_dot_neor(Graph *tree, void *param)
{
    FILE *f = param;

    for(int i = 0; i < tree->n; i++)
    {
      for(int j = 0; j < tree->n; j++)
      {
        if(tree->matrix[i][j] == 1)
        {
          fprintf(f,"%d -- %d;\n",(i+1),(j+1));
        }
      }
    }
}


void to_dot_or(Graph *tree, void *param)
{
    FILE *f = param;

    for(int i = 0; i < tree->n; i++)
    {
      for(int j = 0; j < tree->n; j++)
      {
        if(tree->matrix[i][j] == 1)
        {
          fprintf(f,"%d -> %d;\n",(i+1),(j+1));
        }
      }
    }
}


void export_to_dot(FILE *f, const char *tree_name, Graph *tree)
{
    int check = check_or(tree);
    if(check)
    {
      fprintf(f, "graph %s {\n", tree_name);
      to_dot_neor(tree,f);
    }
    else
    {
      fprintf(f, "digraph %s {\n", tree_name);
      to_dot_or(tree, f);
    }

    fprintf(f, "}\n");
}