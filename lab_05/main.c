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

  int non_zero = 0;
  double element;
  double **matrix1;
  double **matrix2;
  int row;
  int col;

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

  if(!argv[1] && !argv[2])
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
      if(n <= 10 && m <= 10)
        matrix = get_array_from_keyboard(n, m, file1, kind_of_enter);
      if((n > 10 || m > 10) && kind_of_enter == 2)
        matrix = get_array_from_keyboard(n, m, file1, kind_of_enter);
      if((n > 10 || m > 10) && kind_of_enter == 1)
      {
        matrix1 = allocate_matrix(n,m);
        if(matrix1)
        {
          printf("Какое количество ненулевых элементов вы хотите ввести: ");
          scanf("%d", &non_zero);
          if(non_zero > 0)
          {
            for(i = 0; i < non_zero; i++)
            {
              printf("Введите строку, в которой будет находиться элемент: ");
              scanf("%d", &row);
              if(row > 0)
              {
                printf("Введите столбец в котором будет находиться элемент: ");
                scanf("%d", &col);
                if(col > 0)
                {
                  printf("Введите элемент: ");
                  scanf("%lf", &element);
                  if(element != 0)
                    matrix1[row - 1][col - 1] = element;
                  else
                  {
                    printf("Некорректный элемент\n");
                    return -1;
                  }
                }
                else
                {
                  printf("Некорректный столбец\n");
                  return -1;
                }
              }
              else
              {
                printf("Некорректная строка\n");
                return -1;
              }
            }

            f = fopen(file1, "w");
            if(!f)
            {
              printf("Ошибка открытия файла\n");
              return -1;
            }
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < m; j++)
              {
                fprintf(f, "%lf ", matrix1[i][j]);
              }
              fprintf(f, "\r\n");
            }
            fclose(f);

            matrix = get_array_from_keyboard(n, m, file1, 2);
          }
          else
          {
            printf("Некорректная количество ненулевых элементов\n");
            return -1;
          }
        }
      }
      if(matrix)
      {
        /*int *LJ = malloc((m+1) * sizeof(int));
        i =  0;
        for(  ;matrix->colindex; matrix->colindex = matrix->colindex->next)
        {
          LJ[i] = matrix->colindex->Nk - 1;
          i++;
        }
        for(i = 0; i < matrix->NZ; i++)
          matrix->Row[i] -= 1;*/

        //TMatrix = transpgust(m,matrix, LJ);
          TMatrix = transponse(m, n, matrix);
      }
      else
      {
        printf("Недостаточное количество элементов в матрице\n");
        return -1;
      }

      printf("\n");

      printf("Введите количество строк для вектора-столбца: ");
      scanf("%d", &n1);
      if(n1 > 0)
      {
        if(n1 <= 10)
          vector_matrix = get_array_from_keyboard(n1, 1, file2, kind_of_enter);
        if(n1 > 10 && kind_of_enter == 2)
          vector_matrix = get_array_from_keyboard(n1, 1, file2, kind_of_enter);
        if(n1 > 10 && kind_of_enter == 1)
        {
          matrix2 = allocate_matrix(n,m);
          if(matrix2)
          {
            printf("Какое количество ненулевых элементов вы хотите ввести: ");
            scanf("%d", &non_zero);
            if(non_zero > 0)
            {
              for(i = 0; i < non_zero; i++)
              {
                printf("Введите строку, в которой будет находиться элемент: ");
                scanf("%d", &row);
                if(row > 0)
                {
                  printf("Введите элемент: ");
                  scanf("%lf", &element);
                  if(element != 0)
                    matrix2[row - 1][0] = element;
                  else
                  {
                    printf("Некорректный элемент\n");
                    return -1;
                  }
                }
                else
                {
                  printf("Некорректная строка\n");
                  return -1;
                }
              }
            }

            f = fopen(file2, "w");
            if(!f)
            {
              printf("Ошибка открытия файла\n");
              return -1;
            }
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < 1; j++)
              {
                fprintf(f, "%lf ", matrix2[i][j]);
              }
              fprintf(f, "\r\n");
            }
            fclose(f);

            vector_matrix = get_array_from_keyboard(n1, 1, file2, 2);
          }
        }
        if(vector_matrix)
        {
          if(m == n1)
          {
            Mult1 = multiply(n, m, TMatrix, vector_matrix);
            if(Mult1)
            {
              if(n <= 20 && m <= 20)
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
                {
                  if(Mult1->colindex->Nk > 0)
                    printf("%d ", Mult1->colindex->Nk);
                }
              }
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
              printf("\n");

              printf("На умножение классическим алгоритмом ушло: %llu", te-tb);

              printf("\n");
              printf("\n");
              if(n <= 20 && m <= 20)
              {
                for(i = 0; i < n; i++)
                {
                  for(j = 0; j < 1; j++)
                  {
                    printf("%lf", multi[i][j]);
                  }
                  printf("\n");
                }
              }

            }
          }
          else
            printf("Невозможно умножить(некорректные размеры для умножения)\n");
        }
        else
        {
          printf("Недостаточное количество элементов в матрице\n");
          return -1;
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