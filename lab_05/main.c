#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNCORRECT_SYMBOL -1;
#define OK 0;
#define WRONG_MATRIX_SIZE 0

#include "main.h"
#include "pushpop.h"
#include "getkeybarr.h"
#include "getia.h"
#include "getja.h"
#include "transp.h"
#include "mult1.h"
#include "alloc.h"
#include "getfilearr.h"
#include "mult2.h"
#include "tick.h"

int main(int argc,const char** argv)
{
  FILE *f, *f2;

  int n = 0;
  int n1 = 0;
  int m = 0;

  int i = 0;
  int j = 0;

  struct cscMatrix *matrix;
  struct cscMatrix *vector_matrix;
  struct cscMatrix *TMatrix;
  struct cscMatrix *Mult1;

  unsigned long long tb, te;

  if(!argv[1] && !argv[2])
  {
    printf("Введите количество строк: ");
    scanf("%d",&n);
    if(n > 0)
    {
      printf("Введите количество столбцов: ");
      scanf("%d",&m);
      if(m > 0)
      {
        matrix = get_array_from_keyboard(n, m, "in.txt");
        if(matrix)
        {
          matrix = get_ia(m,matrix,"in.txt");
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
          matrix = get_ja(n, m, matrix,"in.txt");*/
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
        else
          return -1;

        printf("\n");

        printf("Введите количество строк для вектора-столбца: ");
        scanf("%d", &n1);
        if(n1 > 0)
        {
          vector_matrix = get_array_from_keyboard(n1, 1, "in2.txt");
          if(vector_matrix)
          {
            vector_matrix = get_ia(1,vector_matrix,"in2.txt");
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
            vector_matrix = get_ja(n1, 1, vector_matrix,"in2.txt");*/
            /*printf("JB: ");
            for(  ;vector_matrix->colindex; vector_matrix->colindex = vector_matrix->colindex->next)
              printf("%d ", vector_matrix->colindex->Nk);*/

            printf("\n");

            if(m == n1)
            {
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

              f = fopen("in.txt","r");
              f2 = fopen("in2.txt","r");
              if(!f || !f2)
              {
                printf("Open file error\n");
              }
              else
              {
                double **matrix1 = get_matrix_from_file(f,allocate_matrix,n, m);
                double **matrix2 = get_matrix_from_file(f2,allocate_matrix,n1, 1);
                printf("OK\n");

                tb = tick();
                double **multi = mult(allocate_matrix,matrix1,matrix2,n,m,n1,1);
                te = tick();

                printf("\n");

                printf("На умножение классическим алгоритмом ушло: %llu", te-tb);

                printf("\n");
                for(i = 0; i < n; i++)
                {
                  for(j = 0; j < 1; j++)
                  {
                    printf("%lf\n", multi[i][j]);
                  }
                  printf("\n");
                }

              }
            }
            else
              printf("Невозможно умножить(некорректные размеры для умножения)\n");
          }
        }
        else
          printf("Некорректное количество столбцов\n");
      }
      else
        printf("Некорректное количество столбцов\n");
    }
    else
      printf("Некорректное количество строк\n");
  }

}