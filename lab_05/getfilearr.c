#include <stdio.h>
#include <stdlib.h>

double ** get_matrix_from_file(FILE *f,double ** (*alloc)(int,int), int n, int m)
{
  double num;
  int i,j;
  double **matrix;

  i=0;
  j=0;
  matrix = alloc(n, m);

  if(fscanf(f,"%lf",&num) == 1)
  {
    matrix[i][j] = num;
    j++;
    if(j == m)
    {
      j=0;
      i++;
    }
    while(fscanf(f,"%lf",&num) == 1)
    {
      matrix[i][j] = num;
      j++;
      if(j == m)
      {
        j=0;
        i++;
      }
    }
  }

  return matrix;
}