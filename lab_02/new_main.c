#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 15
#define TITLE_LEN 30
#define PUBLISHER_LEN 10
#define INDUSTRY_LEN 15
#define TYPE_LEN 15
#define KIND 15

struct technical_t {
  char industry[INDUSTRY_LEN + 1];
  char type[TYPE_LEN + 1];
  int year;
};

struct artistic_t {
  char kind[KIND + 1];
};

union item_t{
  struct technical_t technical;
  struct artistic_t artistic;
};

struct literature_list {
  int number;
  char author[NAME_LEN + 1];
  char title [TITLE_LEN + 1];
  char publisher[PUBLISHER_LEN + 1];
  int pages_number;
  int type1;
  union item_t item;
};

int kind_book(const char *str)
{
  int i = 0;
  int a = 0;
  int symbol_count = 0;
  //char str2[100];

  while(str[i] != '\n')
  {
  	if(str[i] == '|')
  	{
  		//printf("%d\n", symbol_count);
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


//=================================================================================
//ПОДУМАЙ НАД СЧИТЫВАНИЕМ

/*void decide_pole(int i,int k,int pole,struct literature_list *data,const char *str)
{
  //long int a = 0;


	if(pole == 0 && str[k] != '\0')
    data[i].item.technical.author[k] = str[k];

	if(pole == 1 && str[k] != '\0')
      data[i].item.technical.title[k] = str[k];

	if(pole == 2 && str[k] != '\0')
      data[i].item.technical.publisher[k] = str[k];

  if(pole == 3 && str[k] != '\0')
  {
    a = atol(str);
    data[i].item.technical.pages_number = a;
  }

  if(pole == 4 && str[k] != '\0')
  {
    data[i].item.technical.type1 = 1;
  }
  if(pole == 5 && str[k] != '\0')
    data[i].item.technical.industry[k] = str[k];

  if(pole == 6 && str[k] != '\0')
      data[i].item.technical.type[k] = str[k];

  if(pole == 7 && str[j] != '\0')
  {
    a = atol(str);
    data[i].item.technical.year = a;
  }
}*/

/*void get_tech(int j,const char *str,struct literature_list *data)
{
	int i = 0,k = 0;;
	int pole = 0;
  char str2[200];

  //printf("%s\n",str);
	while(str[i] != '\n')
	{
		if (str[i] == '|')
    {
      //decide_pole(j,k,pole,data,str2);
      str2[k] = '\0';
      //printf("%s\n", str2);
      k = 0;
      //printf("%s %d\n", str2, pole);
			pole++;
    }
		if(str[i] != '|')
    {
      str2[k] = str[i];
      //printf("%s\n", str2);
      //decide_pole(j,k,pole,data,str2);
    }
    k++;
    i++;
	}
}*/

//====================================================================================



void decide_pole(int kind,int pole,int j, int k,struct literature_list *data,const char *str)
{
  long int a = 0;

  if(pole == 0)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].author[i] = str[i];
    }
  }
  if(pole == 1)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].title[i] = str[i];
    }
  }
  if(pole == 2)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].publisher[i] = str[i];
    }
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
  }
  if(pole == 5 && kind == 2)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].item.artistic.kind[i] = str[i];
    }
  }
  if(pole == 6)
  {
    for (int i = 0; i < k; i++)
    {
      data[j].item.technical.type[i] = str[i];
    }
  }
  if(pole == 7)
  {
    a=atol(str);
    data[j].item.technical.year = a;
  }
}


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
    }
    if(str[i] == '|')
    {
      decide_pole(kind,pole,j,k,data,str2);
      k = -1;
      pole++;
    }
    k++;
    i++;
  }
}

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

int main(void)
{
	FILE *f;
	struct literature_list data[100];
  int size = 0;

	f = fopen("in.txt","r");
  	if(f == NULL)
  	{
    	printf("Can't open file\n");
  	}
  	else
  	{
    	size = get_records(f,data);
      printf("%d\n", size);
      f = fopen("out.txt","w");
      for(int i = 0; i < size; i++)
      {
        if(data[i].type1 == 1)
          fprintf(f, "%d %s %s %s %d %d %s %s %d\r\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
          //printf("%d %s %s %s %d %d %s %s %d\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
        else
          fprintf(f, "%d %s %s %s %d %d %s\r\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
          //printf("%d %s %s %s %d %d %s\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
      }
  	}
}