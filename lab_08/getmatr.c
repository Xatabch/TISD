#include <stdio.h>
#include <stdlib.h>

#include "main.h"

Graph *get_matrix(FILE *f,int ** (*alloc)(int,int))
{
  int num;
  int i,j;

  Graph *graph = malloc(sizeof(Graph));

  fscanf(f,"%d",&num);
  graph->n = num;

  i=0;
  j=0;
  graph->matrix = alloc(graph->n,graph->n);

  if(fscanf(f,"%d",&num) == 1)
  {
    graph->matrix[i][j] = num;
      j++;
      if(j == graph->n)
      {
        j=0;
        i++;
      }
    }
    while(fscanf(f,"%d",&num) == 1)
    {
      graph->matrix[i][j] = num;
      j++;
      if(j == graph->n)
      {
        j=0;
        i++;
      }
    }

    return graph;
}