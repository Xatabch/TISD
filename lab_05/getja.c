#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "pushpop.h"

struct cscMatrix *get_ja(int n, int m,struct cscMatrix *Matrix, char *file)
{
  int i = 0;
  int j = 0;

  FILE *f;
  double num;

  struct colIndex *head = NULL;
  double *matrix = malloc(Matrix->N * sizeof(double));

  f = fopen(file,"r");
  if(!f)
  {
    printf("Ошибка файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      matrix[i] = num;
      i++;
      while(fscanf(f,"%lf",&num) == 1)
      {
        matrix[i] = num;
        i++;
      }
    }
  }
  fclose(f);

  int *ia = calloc(m+1,sizeof(int));

  for(i = 0; i < m+1; i++)
    ia[i] = 0;

  ia[0] = Matrix->NZ + 1;

  j = 1;
  int c_n_z = Matrix->NZ;
  i = (n * m) - 1;
  while(i >= 0)
  {
    if(j == m + 1)
      j = 1;
    if(matrix[i] != 0)
    {
      ia[j] = c_n_z;
      c_n_z--;
    }
    j++;
    i--;
  }

  for(i = 0; i < m+1; i++)
  {
    if(ia[i] == 0)
      ia[i] = ia[i-1];
  }
  for(i = 0; i < m+1; i++)
    ia[i] -= 1;

  for(i = 0; i < m + 1; i++)
    push(&head,(ia[i] + 1));

  Matrix->colindex = malloc(sizeof(struct colIndex));
  Matrix->colindex = head;

  return Matrix;

  free(matrix);
  free(ia);
  free(head);

}