#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNCORRECT_SYMBOL -1;
#define OK 0;

#include "main.h"
#include "pushpop.h"
#include "getkeybarr.h"
#include "getia.h"
#include "getja.h"
#include "transp.h"
#include "mult1.h"

int main(void)
{
  int n = 0;
  int n1 = 0;
  int m = 0;

  struct cscMatrix *matrix;
  struct cscMatrix *vector_matrix;
  struct cscMatrix *TMatrix;
  struct cscMatrix *Mult1;

  printf("Введите количество строк: ");
  scanf("%d",&n);
  if(n > 0)
  {
    printf("Введите количество столбцов: ");
    scanf("%d",&m);
    if(m > 0)
    {
      matrix = get_array_from_keyboard(n, m);
      if(matrix)
      {
        matrix = get_ia(m,matrix);
        /*printf("A: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%f ", matrix->Value[i]);
        printf("\n");
        printf("N: %d\n",matrix->N);
        printf("NZ: %d\n",matrix->NZ);
        printf("IA: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%d ", matrix->Row[i]);
        printf("\n");
        matrix = get_ja(n, m, matrix);*/
        /*printf("JA: ");
        for(  ;matrix->colindex; matrix->colindex = matrix->colindex->next)
          printf("%d ", matrix->colindex->Nk);*/
        //printf("\n");

        TMatrix = transponse(m,n,matrix);
        if(TMatrix)
        {
          /*printf("\nTMatrix A: ");
          for(int i = 0; i < TMatrix->NZ;i++)
            printf("%f ", TMatrix->Value[i]);
          printf("\nTMatrix IA: ");
          for(int i = 0; i < TMatrix->NZ;i++)
            printf("%d ", TMatrix->Row[i]);*/
          /*printf("\nTMatrix JA: ");
          for(  ;TMatrix->colindex; TMatrix->colindex = TMatrix->colindex->next)
            printf("%d ", TMatrix->colindex->Nk);*/
        }
      }

      printf("\n");

      printf("Введите количество строк для вектора-столбца: ");
      scanf("%d", &n1);
      if(n1 > 0)
      {
        vector_matrix = get_array_from_keyboard(n1, 1);
        if(vector_matrix)
        {
          vector_matrix = get_ia(1,vector_matrix);
          /*printf("B: ");
          for(int i = 0; i < vector_matrix->NZ;i++)
            printf("%f ", vector_matrix->Value[i]);
          printf("\n");
          printf("N: %d\n",vector_matrix->N);
          printf("NZ: %d\n",vector_matrix->NZ);
          printf("IB: ");
          for(int i = 0; i < vector_matrix->NZ;i++)
            printf("%d ", vector_matrix->Row[i]);
          printf("\n");
          vector_matrix = get_ja(n1, 1, vector_matrix);*/
          /*printf("JB: ");
          for(  ;vector_matrix->colindex; vector_matrix->colindex = vector_matrix->colindex->next)
            printf("%d ", vector_matrix->colindex->Nk);*/

          printf("\n");

          Mult1 = multiply(n, m, TMatrix, vector_matrix);
          if(Mult1)
          {
            printf("Mult1: ");
            for(int i = 0; i < Mult1->NZ;i++)
              printf("%f ", Mult1->Value[i]);
            printf("\n");
            printf("N: %d\n",Mult1->N);
            printf("NZ: %d\n",Mult1->NZ);
            printf("IM: ");
            for(int i = 0; i < Mult1->NZ;i++)
              printf("%d ", Mult1->Row[i]);
            printf("\n");
            printf("JM: ");
            for(  ;Mult1->colindex; Mult1->colindex = Mult1->colindex->next)
              printf("%d ", Mult1->colindex->Nk);
          }


        }
      }
    }
    else
      printf("Некорректное количество столбцов\n");
  }
  else
    printf("Некорректное количество строк\n");

}