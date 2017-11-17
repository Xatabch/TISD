#include <stdio.h>
#include <stdlib.h>

double ** allocate_matrix(int n,int m)
{
  double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));

  if(!data)
    return NULL;

  for(int i = 0;i < n; i++)
    data[i] = (double*)((char*) data + n * sizeof(double*) + i * m * sizeof(double));
  
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
      data[i][j] = 0;
  }

  return data;
}