#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNCORRECT_SYMBOL -1;
#define OK 0;
#define WRONG_MATRIX_SIZE 0

#include "main.h"
#include "pushpop.h"
#include "getkeybarr.h"
#include "transp.h" 
#include "mult1.h"
#include "alloc.h"
#include "getfilearr.h"
#include "mult2.h"
#include "tick.h"
#include "transpgust.h"

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
  const char *file1;
  const char *file2;
  int kind_of_enter;

  unsigned long long tb, te;
  //printf("argv[2]: %s\n",argv[2]);

  if(!argv[1])
  {
    file1 = "in.txt";
    file2 = "in2.txt";
    kind_of_enter = 1;
  }
  else
  {
    file1 = argv[1];
    file2 = argv[2];
    kind_of_enter = 2;
  }

  printf("Введите количество строк: ");
  scanf("%d",&n);
  if(n > 0)
  {
    printf("Введите количество столбцов: ");
    scanf("%d",&m);
    if(m > 0)
    {
      matrix = get_array_from_keyboard(n, m, file1, kind_of_enter);
      if(matrix)
      {
      int *LJ = malloc((m+1) * sizeof(int));
      i =  0;
      for(  ;matrix->colindex; matrix->colindex = matrix->colindex->next)
      {
        LJ[i] = matrix->colindex->Nk - 1;
        i++;
      }
      for(i = 0; i < matrix->NZ; i++)
        matrix->Row[i] -= 1;

        int *LJT = malloc((m+1) * sizeof(int));
        struct cscMatrix *matrixT = malloc(sizeof(struct cscMatrix));
        matrixT->Value = malloc(matrix->NZ * sizeof(double));
        matrixT->Row = malloc(matrix->NZ * sizeof(int));
        matrixT->NZ = matrix->NZ;

        printf("A: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%f ", matrix->Value[i]);
        printf("\n");
        printf("IAT: ");
        for(int i = 0; i < matrix->NZ; i++)
          printf("%d ", matrix->Row[i]);
        printf("\n");
        printf("LJT: ");
        for(i = 0; i < (m+1); i++)
          printf("%d ", LJ[i]);
        printf("\n");

        /*memset(LJT, 0, (m+1) * sizeof(int));
        for(i = 0; i < matrix->NZ; i++)
          LJT[matrix->Row[i] + 1]++;

        int S = 0;
        int tmp = 0;
        for(i = 1; i <= m+1; i++)
        {
          tmp = LJT[i];
          LJT[i] = S;
          S = S + tmp;
        }

        int j1 = 0;
        int j2 = 0;
        int Col = 0;
        double V = 0;
        int RIndex = 0;
        int IIndex = 0;
        for(i = 0; i < m; i++)
        {
          j1 = LJ[i] ; j2 = LJ[i+1];
          Col = i;
          for(j = j1; j < j2; j++)
          {
            V = matrix->Value[j];
            RIndex = matrix->Row[j];
            IIndex = LJT[RIndex + 1];
            matrixT->Value[IIndex] = V;
            matrixT->Row[IIndex] = Col;
            LJT[RIndex + 1]++;
          }
        }*/

        printf("transp: ");
        for(int i = 0; i < matrixT->NZ;i++)
          printf("%f ", matrixT->Value[i]);
        printf("\n");
        printf("IAT: ");
        for(int i = 0; i < matrixT->NZ; i++)
          printf("%d ", matrixT->Row[i]);
        printf("\n");
        printf("LJT: ");
        for(i = 0; i < (m+1); i++)
          printf("%d ", LJT[i]);

        TMatrix = transponse(m,n,matrix);
      }
      else
        return -1;

      printf("\n");

      printf("Введите количество строк для вектора-столбца: ");
      scanf("%d", &n1);
      if(n1 > 0)
      {
        vector_matrix = get_array_from_keyboard(n1, 1, file2, kind_of_enter);
        if(vector_matrix)
        {
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
              printf("IM: ");
              for(int i = 0; i < Mult1->NZ;i++)
                printf("%d ", Mult1->Row[i]);
              printf("\n");
              printf("JM: ");
              for(  ;Mult1->colindex; Mult1->colindex = Mult1->colindex->next)
                printf("%d ", Mult1->colindex->Nk);
            }

            f = fopen(file1,"r");
            f2 = fopen(file2,"r");
            if(!f || !f2)
            {
              printf("Open file error\n");
            }
            else
            {
              double **matrix1 = get_matrix_from_file(f,allocate_matrix,n, m);
              double **matrix2 = get_matrix_from_file(f2,allocate_matrix,n1, 1);

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