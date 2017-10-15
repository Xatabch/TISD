#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

void decide_pole(int kind,int pole,int j, int k,struct literature_list *data,const char *str)
{
  long int a = 0;

  if(pole == 0)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].author[i] = str[i];
    }
    data[j].author[k] = '\0';
  }
  if(pole == 1)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].title[i] = str[i];
    }
    data[j].title[k] = '\0';
  }
  if(pole == 2)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].publisher[i] = str[i];
    }
    data[j].publisher[k] = '\0';
  }
  if(pole == 3)
  {
    a = atol(str);
    data[j].pages_number = a;
  }
  if(pole == 5 && kind == 1)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].item.technical.industry[i] = str[i];
    }
    data[j].item.technical.industry[k] = '\0';
  }
  if(pole == 5 && kind == 2)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].item.artistic.kind[i] = str[i];
    }
    data[j].item.artistic.kind[k] = '\0';
  }
  if(pole == 6)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].item.technical.type[i] = str[i];
    }
    data[j].item.technical.type[k] = '\0';
  }
  if(pole == 7)
  {
    a=atol(str);
    data[j].item.technical.year = a;
  }
}