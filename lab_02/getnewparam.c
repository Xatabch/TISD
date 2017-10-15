#include <stdio.h>

#include "main.h"
#include "decidepole.h"

//j-номер структуры
void get_first_params(int kind,int j,const char *str,struct literature_list *data)
{
  int i = 0;
  int k = 0;
  int pole = 0;
  char str2[200];

  data[j].number = j+1;
  while(str[i] != '\n')
  {
    if(str[i] != '|')
    {
      str2[k] = str[i];
      k++;
    }
    if(str[i] == '|')
    {      
      str2[k] = '\0';
      decide_pole(kind,pole,j,k,data,str2);
      k = 0;
      pole++;
    }
    i++;
  }
}