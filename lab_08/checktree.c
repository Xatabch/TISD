#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "allocmtr.h"

#define NEOR 1
#define HAVE_CYCLES 2
#define NO_CONNECT 3
#define OK 0
#define CANNOT_MAKE_TREE 4

int check_or(Graph *graph)
{

  for(int i = 0; i < graph->n; i++)
  {
    for (int j = 0; j < graph->n; j++)
    {
      if((graph->matrix[i][j] == 1) && (graph->matrix[j][i] == 1) && (i != j))
      {
        return NEOR;
      }
    }
  }

  return OK;
}


int check_cycles(Graph *graph)
{

  for(int i = 0;i < graph->n; i++)
  {
    if(graph->matrix[i][i] == 1)
    {
      return HAVE_CYCLES;
    }
  }

  return OK;
}


int check_connect(Graph *graph)
{
  int count_rows = 0;
  int count_columns = 0;

  for(int i = 0; i < graph->n; i++)
  {
    for (int j = 0; j < graph->n; j++)
    {
      if(graph->matrix[i][j] == 0)
        count_columns++;
      if(graph->matrix[j][i] == 0)
        count_rows++;
    }
    if((count_columns == graph->n) && (count_rows == graph->n))
      return NO_CONNECT;
    count_rows = 0;
    count_columns = 0;
  }

  return OK;
}


int check_graph(Graph *graph)
{
  int or = check_or(graph);
  int cycles = check_cycles(graph);
  int connect = check_connect(graph);

  return (or + cycles + connect);
}

// void print(Graph *graph)
// {
//     for (int i = 0; i < graph->n; i++)
//     {
//       for (int j = 0; j < graph->n; j++)
//       {
//         printf("%d ", graph->matrix[i][j]);
//       }
//       printf("\n");
//     }
// }


int check_graph_for_tree(Graph *graph)
{
  Graph *graph1 = malloc(sizeof(Graph));
  graph1->n = graph->n;
  graph1->matrix = allocate_matrix((graph1->n),(graph1->n));
  int indicate = 0;

  for(int k = 0; k < graph->n; k++)
  {
    for(int i = 0; i < graph->n; i++)
    {
      for (int j = 0; j < graph->n; j++)
      {
        if(i == k || j == k)
          graph1->matrix[i][j] = -1;
        else
          graph1->matrix[i][j] = graph->matrix[i][j];
      }
    }
    indicate = check_graph(graph1);
    if(indicate == 0)
      return OK;
    indicate = 0;
  }

  return CANNOT_MAKE_TREE;
}


