#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "pushpop.h"

struct cscMatrix *transponse(int m, int n, struct cscMatrix *Matrix)
{
  FILE *f;
  int i = 0;
  int j = 0;
  int check = 0;
  double num;
  int str_count = 0;//определяет к какой строке принадлежит транспонированная матрица

  struct cscMatrix *TMatrix = malloc(sizeof(struct cscMatrix));
  TMatrix->N = Matrix->N;
  TMatrix->NZ = Matrix->NZ;
  TMatrix->Value = malloc(TMatrix->NZ * sizeof(double));
  TMatrix->Row = malloc(TMatrix->NZ * sizeof(int));
  int *ia = calloc((n+1), sizeof(int));
  struct colIndex *head = NULL;

  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка открытия файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f, "%lf", &num) == 1)
    {

      if(num != 0)
      {
        TMatrix->Value[i] = num;
        TMatrix->Row[i] = str_count + 1;
        i++;
      }

      if(num != 0 && check == 0)
      {
        ia[j] = i;
        check = 1;
      }

      str_count++;

      if(str_count == m)
      {
        str_count = 0;
        j++;
        check = 0;
      }

      while(fscanf(f, "%lf", &num) == 1)
      {

        if(num != 0)
        {
          TMatrix->Value[i] = num;
          TMatrix->Row[i] = str_count + 1;
          i++;
        }

        if(num != 0 && check == 0)
        {
          ia[j] = i;
          check = 1;
        }

        str_count++;

        if(str_count == m)
        {
          str_count = 0;
          j++;
          check = 0;
        }
      }
    }

    ia[n] = TMatrix->NZ;

    /*for(i = 0; i < (n+1); i++)
      printf("[%d] ", ia[i]);*/

    for(i = n+1; i >= 0; i--)
    {
      if(ia[i] == 0)
        ia[i] = ia[i+1];
    }

    for(i = 0; i < n; i++)
      ia[i] = ia[i] - 1;

    for(i = n; i >= 0; i--)
      push(&head,(ia[i] + 1));

    TMatrix->colindex = malloc(sizeof(struct colIndex));
    TMatrix->colindex = head;
  }

  return TMatrix;

}