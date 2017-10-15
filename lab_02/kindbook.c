#include <stdio.h>

int kind_book(const char *str)
{
  int i = 0;
  int a = 0;
  int symbol_count = 0;

  while(str[i] != '\n')
  {
  	if(str[i] == '|')
  	{
  		if(symbol_count <= 2 && str[i-1] == '1')
  			a = 1;
  		if(symbol_count <= 2 && str[i-1] == '2')
  			a = 2;
  		symbol_count = 0;
  	}
  	symbol_count++;
  	i++;
  }

  return a;
}