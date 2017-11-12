#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "pushpop.h"
#include "tick.h"

int *make_ip(int tmp1, int tmp2, int m, int *j)
{
  int *IP = calloc(m, sizeof(int));
  int i = 0;
  int k = 1;

  if(!IP)
    return NULL;
  else
  {
    for(i = tmp1; i < tmp2; i++)
    {
      IP[j[i] - 1] = k;
      k++;
    }
  }

  return IP;

  free(IP);

}

struct cscMatrix *multiply(int n, int m, struct cscMatrix *Matrix, struct cscMatrix *vector_matrix)
{
  int tmp1 = pop(&Matrix->colindex);
  int tmp2;
  int i = 0;
  int j = 0;
  int k = 0;
  int *IP;
  struct cscMatrix *Result = malloc(sizeof(struct cscMatrix));
  double *val = calloc(n, sizeof(double));
  double h = 0;
  struct colIndex *head = NULL;
  unsigned long long tb, te;

  Result->NZ = 0;
  Result->N = n;

  IP = make_ip(0, vector_matrix->NZ, m, vector_matrix->Row);
  if(!IP)
  {
    printf("Error alloc memory\n");
    return NULL;
  }

  tb = tick();
  for(i = 0; i < n; i++)
  {
    tmp2 = pop(&Matrix->colindex);

    if(tmp1 != tmp2)
    {
      for(j = (tmp1 - 1); j < (tmp2 - 1); j++)
      {
        if(IP[Matrix->Row[j] - 1] > 0)
          h += vector_matrix->Value[IP[Matrix->Row[j] - 1]-1] * Matrix->Value[j];
      }
      if(h > 0)
        Result->NZ++;
    }
    val[i] = h;
    h = 0;
    tmp1 = tmp2;
  }
  te = tick();

  printf("Время занимаемое скалярным умножением: %llu\n", te-tb);

  Result->Row = malloc(Result->NZ * sizeof(int));
  for (i = 0; i < n; i++)
  {
    if(val[i] != 0)
    {
      Result->Row[k] = i+1;
      k++;
    }
  }

  k = 0;
  Result->Value = malloc(Result->NZ * sizeof(double));
  for(i = 0; i < n; i++)
  {
    if(val[i] != 0)
    {
      Result->Value[k] = val[i];
      k++;
    }
  }
  /*printf("\n");
  printf("VAL: ");
  for (i = 0; i < n; i++)
    printf("%lf ", val[i]);
  printf("\nROW: ");
  for(i = 0; i < k; i++)
    printf("%d ", Result->Row[i]);*/
  push(&head,(Result->NZ+1));
  push(&head,Result->Row[0]);
  Result->colindex = malloc(sizeof(struct colIndex));
  Result->colindex = head;

  return Result;
}