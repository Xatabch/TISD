#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct cscMatrix *get_ia(int m,struct cscMatrix *Matrix,char *file)
{
  FILE *f;
  int fill_rows = 0;;
  double num;
  int waddap = 0;
  int i = 0;
  Matrix->Row = malloc(Matrix->NZ * sizeof(int));

  f = fopen(file,"r");
  if(!f)
    return NULL;
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      if(num != 0)
      {
        Matrix->Row[i] = waddap + 1;
        i++;
      }

      fill_rows++;
      if(fill_rows == m)
      {
        waddap++;
        fill_rows = 0;
      }
      while(fscanf(f,"%lf",&num) == 1)
      {
        if(num != 0)
        {
          Matrix->Row[i] = waddap + 1;
          i++;
        }

        fill_rows++;
        if(fill_rows >= m)
        {
          waddap++;
          fill_rows = 0;
        }
      }
    }
  }
  fclose(f);

  return Matrix;
  free(Matrix->Row);
}