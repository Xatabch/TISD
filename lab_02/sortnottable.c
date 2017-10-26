#include <stdio.h>
#include <string.h>

#include "main.h"

void puzir_not_table(struct literature_list *data,struct dop_array *dop,int size)
{
  struct dop_array middle;

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    strcpy(dop[i].author,data[i].author);
  }

  for(int i = 0 ; i < size; i++) 
  { 
    for(int j = 0 ; j < size - i - 1 ; j++) 
    {
      if(strcmp(dop[j].author,dop[j+1].author) > 0)
      {
        middle = dop[j];
        dop[j] = dop[j+1];
        dop[j+1] = middle;
      }
    }
  }
}

void rascheska_not_table(struct literature_list *data,int size)
{
  struct dop_array middle;
  struct dop_array dop[size];
  int left = 0, right = size - 1;
  int flag = 1;

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    strcpy(dop[i].author,data[i].author);
  }

  while ((left < right) && flag > 0)
  {
    flag = 0;
    for (int i = left; i<right; i++)
    {
      if (strcmp(dop[i].author,dop[i+1].author) > 0)
      {             // меняем их местами
        middle = dop[i];
        dop[i] = dop[i+1];
        dop[i+1] = middle;
        flag = 1;
      }
    }
    right--;
    for (int i = right; i>left; i--)
    {
      if (strcmp(dop[i-1].author,dop[i].author) > 0)
      {
        middle = dop[i];
        dop[i] = dop[i-1];
        dop[i-1] = middle;
        flag = 1;
      }
    }
    left++;
  }
}