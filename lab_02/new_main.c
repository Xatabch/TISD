#include <stdio.h>
#include <string.h>

#define NAME_LEN 15
#define TITLE_LEN 30
#define PUBLISHER_LEN 10
#define INDUSTRY_LEN 15
#define TYPE_LEN 15
#define KIND 15

struct technical_t {
  char author[NAME_LEN + 1];
  char title [TITLE_LEN + 1];
  char publisher[PUBLISHER_LEN + 1];
  int pages_number;
  char industry[INDUSTRY_LEN + 1];
  char type[TYPE_LEN + 1];
  int year;
};

struct artistic_t {
  char author[NAME_LEN + 1];
  char title [TITLE_LEN + 1];
  char publisher[PUBLISHER_LEN + 1];
  int pages_number;
  char kind[KIND + 1];
};

union item_t{
  struct technical_t technical;
  struct artistic_t artistic;
};

typedef enum {KIND_TECHNICAL, KIND_ARTISTIC} kind_item_t;

struct literature_list {
  int number;
  kind_item_t kind;
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

void decide_pole(int i;,int j,int pole,struct literature_list *data,const char *str)
{
	if(pole == 0)
		data[j].item.technical.author = str[i];
	if(pole == 1)
		data[j].item.technical.title = str[i];
	if(pole == 2)
  		data[j].item.technical.publisher = str[i];
  	if(pole == 3)
  char industry[INDUSTRY_LEN + 1];
  char type[TYPE_LEN + 1];
  int year;
}

void get_tech(int j,const char *str,struct literature_list *data)
{
	int i = 0;
	int pole = 0;

	while(str[i] != '\n')
	{
		if (str[i] == '|')
			pole++;
		if(str[i] != '|')
			decide_pole()
	}
}

//====================================================================================

void get_records(FILE *f,struct literature_list *data)
{
  char str[100];
  int i;
  int kind;

  i = 0;
  kind = 0;
  //считал строку
  if(fgets(str,sizeof(str),f))
  {
  	kind = kind_book(str);
  	if(kind == 1)
  	{
  		data[i].number = i+1;
  		data[i].kind = KIND_TECHNICAL;

  	}
  	if(kind == 2)
  		printf("2\n");
  	i++;
  	while(fgets(str,sizeof(str),f))
  	{
  		kind = kind_book(str);
  		if(kind == 1)
  			printf("%s\n",str);
  		if(kind == 2)
  			printf("2\n");
  		i++;
  	}
  }

}

int main(void)
{
	FILE *f;
	struct literature_list data[100];

	f = fopen("in.txt","r");
  	if(f == NULL)
  	{
    	printf("Can't open file\n");
  	}
  	else
  	{
    	get_records(f,data);
  	}
}