#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct cscMatrix *get_array_from_keyboard(int n,int m)
{
  FILE *f;
  int i = 0;
  int c;
  double num;
  struct cscMatrix *Matrix = malloc(sizeof(struct cscMatrix));
  Matrix->NZ = 0;
  Matrix->N = 0;

  f = fopen("in.txt","w");

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

  f = fopen("in.txt","r");
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
        if(num != 0)
        {
          Matrix->NZ++;
        }
    }
  }

  fclose(f);

  Matrix->Value = malloc(Matrix->NZ * sizeof(double));
  i = 0;
  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      Matrix->N++;

      if(num != 0)
      {
        Matrix->Value[i] = num;
        i++;
      }
      while(fscanf(f,"%lf",&num) == 1)
      {
        Matrix->N++;

        if(num != 0)
        {
          Matrix->Value[i] = num;
          i++;
        }
      }
    }
  }
  fclose(f);

  if(Matrix->N != n * m)
  {
    printf("Неверное количество элементов\n");
    return NULL;
  }

  return Matrix;

  free(Matrix->Value);
  free(Matrix);
}