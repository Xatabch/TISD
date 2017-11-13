#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "alloc.h"
#include "getfilearr.h"
#include "pushpop.h"

struct cscMatrix *get_array_from_keyboard(int n, int m,const char *file, int kind_of_enter)
{
  FILE *f;

  int i = 0;
  int z = 0;
  int k = 0;
  int row = 0;
  int c;
  double num;
  double **matrix;
  int check = 0;

  struct cscMatrix *Matrix = malloc(sizeof(struct cscMatrix));
  struct colIndex *head = NULL;

  Matrix->NZ = 0;
  Matrix->N = 0;

  if(kind_of_enter == 1)
  {
    f = fopen(file,"w");

    c = getchar();

    for(i = 0; i< n; i++)
    {
      printf("Введите элементы %d-й строки через пробел: ",(i+1));
      while((c = getchar()) != '\n')
      {
        fprintf(f, "%c", c);
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
          printf("Вы ввели некорректный символы\n");
          return NULL;
        }
      }
      fprintf(f, "\r\n");
    }

    fclose(f);
  }

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

      if(num != 0)
      {
        Matrix->NZ++;
      }

      while(fscanf(f,"%lf",&num) == 1)
      {
        if(num != 0)
        {
          Matrix->NZ++;
        }
      }
    }
  }

  fclose(f);

  f = fopen(file,"r");
  matrix = get_matrix_from_file(f,allocate_matrix, n, m);
  fclose(f);

  Matrix->Value = malloc(Matrix->NZ * sizeof(double));
  Matrix->Row = malloc(Matrix->NZ * sizeof(int));
  int *ia = calloc((m+1),sizeof(int));

  k = 0;
  ia[m] = Matrix->N;
  for(int j = 0; j < m; j++)
  {
    for(int i = 0; i < n; i++)
    {
      Matrix->N++;
      row++;
      if(matrix[i][j] != 0)
      {
        Matrix->Value[k] = matrix[i][j];
        Matrix->Row[k] = row;
        k++;
      }

      if(matrix[i][j] != 0 && check == 0)
      {
        check = 1;
        ia[z] = k - 1;
        z++;
      }
    }
    check = 0;
    row = 0;
  }

  ia[m] = Matrix->NZ;
  for(i = 0; i < m+1; i++)
  {
    if(ia[i] == 0)
      ia[i] = ia[i-1];
  }

  for(i = m; i >= 0; i--)
    push(&head,(ia[i] + 1));

  Matrix->colindex = malloc(sizeof(struct colIndex));
  Matrix->colindex = head;

  return Matrix;

  free(Matrix->Value);
  free(Matrix);
  free(head);
}