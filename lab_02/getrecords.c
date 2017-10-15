#include <stdio.h>

#include "main.h"
#include "kindbook.h"
#include "decidepole.h"
#include "getnewparam.h"

int get_records(FILE *f,struct literature_list *data)
{
  char str[200];
  int i;
  int kind;

  i = 0;
  kind = 0;
  //считал строку
  if(fgets(str,sizeof(str),f))
  {
  	kind = kind_book(str);
    data[i].type1 = kind;
    get_first_params(kind,i,str,data);
  	i++;
  	while(fgets(str,sizeof(str),f))
  	{
  		kind = kind_book(str);
      get_first_params(kind,i,str,data);
      data[i].type1 = kind;
  		i++;
  	}
  }
  return i;

}