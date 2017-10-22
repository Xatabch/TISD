#include <stdio.h>
#include <string.h>

#include "main.h"

void puzir_table(struct literature_list *data,int size)
{
  struct literature_list middle;

  if(size != 0 && size >= 39)
  {
    for(int i = 0 ; i < size; i++) 
    { 
      for(int j = 0 ; j < size - i - 1 ; j++) 
      {
        if(strcmp(data[j].author,data[j+1].author) > 0)
        {
          middle = data[j];
          data[j] = data[j+1];
          data[j+1] = middle;
        }
      }
    }
  }
}

void rascheska_table(struct literature_list *data,int size)
{
  struct literature_list middle;
  int left = 0, right = size - 1;
  int flag = 1;

  while ((left < right) && flag > 0)
  {
    flag = 0;
    for (int i = left; i<right; i++)
    {
      if (strcmp(data[i].author,data[i+1].author) > 0)
      {             // меняем их местами
        middle = data[i];
        data[i] = data[i+1];
        data[i+1] = middle;
        flag = 1;
      }
    }
    right--;
    for (int i = right; i>left; i--)
    {
      if (strcmp(data[i-1].author,data[i].author) > 0)
      {
        middle = data[i];
        data[i] = data[i-1];
        data[i-1] = middle;
        flag = 1;
      }
    }
    left++;
  }
}