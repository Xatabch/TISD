#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 40
#define TITLE_LEN 40
#define PUBLISHER_LEN 40
#define INDUSTRY_LEN 40
#define TYPE_LEN 40
#define KIND 40

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
      f = fopen("out.txt","w");
      for(int i = 0; i < size; i++)
      {
        if(data[i].type1 == 1)
          fprintf(f, "%d %s %s %s %d %d %s %s %d\r\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
          //printf("%d %s %s %s %d %d %s %s %d\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
          //printf("%d | %s | %s |\n",data[i].number, data[i].author,data[i].title);
        if(data[i].type1 == 2)
          fprintf(f, "%d %s %s %s %d %d %s\r\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
          //printf("%d %s %s %s %d %d %s\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
          //printf("%d | %s\n",data[i].number, data[i].author);
      }
  	}
}