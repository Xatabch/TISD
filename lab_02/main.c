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
  int i,j;
  int a;
  char str2[100];

  i = 0;
  j = 0;
  a = 0;
  while(str[i] != '\n')
  {
    if(str[i] != ' ')
    {
      str2[j] = str[i];
      j++;
    }
    else
    {
      if(j < 2)
      {
        if(str2[0] == '1')
          a = 1;
        if(str2[0] == '2')
          a = 2;
      }
      j = 0;
    }
    i++;
  }

  return a;
}

void choose_pole_for_tech(const char *str, int pole,int i,struct technical *pol)
{
  if(pole == 0)
    pol->author[i] = str[i];
  if(pole == 1)
    pol->title[i] = str[i];
  if(pole == 2)
    pol->publisher[i] = str[i];
}

void get_technical_book(const char *str,struct literature_list *data)
{
  int i;
  int pole;
  i = 0;
  pole = 0;
  printf("%s\n", str);
  //пока не встречу символ переноса строки бежать по полученной строке
  while(str[i] != '\n')
  {
    //если символ не равен "" то бежать по строке
    if(str[i] != '"')
    {
      //если символ равен пробелу то записать слово в нужное поле
      if(str[i] == ' ')
      {
        pole+=1;
      }
      if(str[i] != ' ')
      {
        choose_pole_for_tech(str,pole,i,*data.item.technical);
      }
    }
    i++;
}

struct literature_list get_records(FILE *f,int (*kind_book)(const char *),void (*get_technical_book)(const char *))
{
  char str[100];
  int i;
  int kind;
  struct literature_list data;
  //char *num;

  i = 1;
  //считал строку
  if(fgets(str,sizeof(str),f))
  {
    kind = kind_book(str);
    if(kind == 2)
    {
      data.number = i;
      data.kind = KIND_TECHNICAL;
    }
  }
  //printf("%c\n", str[0]);

  return data;
}

int main(void)
{
  FILE *f;
  struct literature_list array[100];

  f = fopen("in.txt","r");
  if(f == NULL)
  {
    printf("Can't open file\n");
  }
  else
  {
    get_records(f,kind_book,get_technical_book);
  }
}
