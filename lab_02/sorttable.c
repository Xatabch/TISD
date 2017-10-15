#include <stdio.h>

#include "main.h"

void puzir_table(struct literature_list *data,int size)
{
  struct literature_list middle;
  size = size - 1;

  if(size != 0 && size >= 39)
  {
    while (size > 0)
    {
      for (int i = 0; i < size; i++)
      {
        if(data[i].pages_number > data[i+1].pages_number)
        {
          middle = data[i+1];
          data[i+1] = data[i];
          data[i] = middle;
        }
      }
      size--;
    }
  }
}

void rascheska_table(struct literature_list *data,int size)
{
  int k;
  struct literature_list middle;
  int s = size;
  long long cnt = 0;

  while(size > 1)
  {
    s/=1.247f;
    if(s<1)
      s=1;
    k=0;
    for (int i = 0; (i+s) < size; ++i)
    {
      if(data[i].pages_number/10 > data[i+s].pages_number/10)
      {
        middle = data[i];
        data[i] = data[i+s];
        data[i+1] = middle;
        k=i;
      }
      ++cnt;
    }
    if(s == 1)
      size = k + 1;
  }
}