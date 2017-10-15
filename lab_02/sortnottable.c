#include <stdio.h>

#include "main.h"

void puzir_not_table(struct literature_list *data,int size)
{
  struct dop_array middle;
  struct dop_array dop[size];

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    dop[i].pages_number = data[i].pages_number;
  }

  while (size > 0)
  {
    for (int i = 0; i < size; i++)
    {
      if(dop[i].pages_number > dop[i+1].pages_number)
      {
        middle = dop[i+1];
        dop[i+1] = dop[i];
        dop[i] = middle;
      }
    }
    size--;
  }
}

void rascheska_not_table(struct literature_list *data,int size)
{
  struct dop_array middle;
  struct dop_array dop[size];
  int k;
  int s = size;
  long long cnt = 0;

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    dop[i].pages_number = data[i].pages_number;
  }

  while(size > 1)
  {
    s/=1.247f;
    if(s<1)
      s=1;
    k=0;
    for (int i = 0; (i+s) < size; ++i)
    {
      if(dop[i].pages_number/10 > dop[i+s].pages_number/10)
      {
        middle = dop[i];
        dop[i] = dop[i+s];
        dop[i+1] = middle;
        k=i;
      }
      ++cnt;
    }
    if(s == 1)
      size = k + 1;
  }
}