#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 40
#define TITLE_LEN 50
#define PUBLISHER_LEN 40
#define INDUSTRY_LEN 40
#define TYPE_LEN 40
#define KIND 40

unsigned long long tick(void)
{
  unsigned long long d;
  __asm__ __volatile__ ("rdtsc" : "=A" (d) );
  return d;
}

struct dop_array {
  int n;
  int pages_number;
};

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

void puzir_table(struct literature_list *data,int size)
{
  struct literature_list middle;
  size = size - 1;

  if(size != 0 && size >= 39)
  {
    while (size > 0)
    {
      for (int i = 0; i < size; i++)
      {
        if(data[i].pages_number > data[i+1].pages_number)
        {
          middle = data[i+1];
          data[i+1] = data[i];
          data[i] = middle;
        }
      }
      size--;
    }
  }
}

void rascheska_table(struct literature_list *data,int size)
{
  int k;
  struct literature_list middle;
  int s = size;
  long long cnt = 0;

  while(size > 1)
  {
    s/=1.247f;
    if(s<1)
      s=1;
    k=0;
    for (int i = 0; (i+s) < size; ++i)
    {
      if(data[i].pages_number/10 > data[i+s].pages_number/10)
      {
        middle = data[i];
        data[i] = data[i+s];
        data[i+1] = middle;
        k=i;
      }
      ++cnt;
    }
    if(s == 1)
      size = k + 1;
  }
}

void puzir_not_table(struct literature_list *data,int size)
{
  struct dop_array middle;
  struct dop_array dop[size];

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    dop[i].pages_number = data[i].pages_number;
  }

  while (size > 0)
  {
    for (int i = 0; i < size; i++)
    {
      if(dop[i].pages_number > dop[i+1].pages_number)
      {
        middle = dop[i+1];
        dop[i+1] = dop[i];
        dop[i] = middle;
      }
    }
    size--;
  }
}

void rascheska_not_table(struct literature_list *data,int size)
{
  struct dop_array middle;
  struct dop_array dop[size];
  int k;
  int s = size;
  long long cnt = 0;

  for (int i = 0; i < size; i++)
  {
    dop[i].n = i;
    dop[i].pages_number = data[i].pages_number;
  }

  while(size > 1)
  {
    s/=1.247f;
    if(s<1)
      s=1;
    k=0;
    for (int i = 0; (i+s) < size; ++i)
    {
      if(dop[i].pages_number/10 > dop[i+s].pages_number/10)
      {
        middle = dop[i];
        dop[i] = dop[i+s];
        dop[i+1] = middle;
        k=i;
      }
      ++cnt;
    }
    if(s == 1)
      size = k + 1;
  }
}

void write_file(void)
{
  FILE *f_in;
  FILE *f_out;
  char str[200];
  int i;

  f_in = fopen("in2.txt","w");
  f_out = fopen("out.txt","r");

  i = 0;
  //считал строку
  if(fgets(str,sizeof(str),f_out))
  {
    fprintf(f_in, "%s\r", str);
    i++;
    while(fgets(str,sizeof(str),f_out))
    {
      fprintf(f_in, "%s\r", str);
      i++;
    }
  }
  fclose(f_in);
  fclose(f_out);

}


int main(void)
{
	FILE *f;
	struct literature_list data[100];
  struct literature_list sort1[100];
  struct literature_list sort2[100];
  struct literature_list sort3[100];
  struct literature_list sort4[100];
  int size = 0;
  int ask = -1;
  int ask_type = -1;
  int ask_year = 0;
  char ask_industry[INDUSTRY_LEN+1];
  int find_count = 0;
  char type[TYPE_LEN+1] = "переводная";
  unsigned long long tb, te;
  char author[NAME_LEN + 1];
  char title [TITLE_LEN + 1];
  char publisher[PUBLISHER_LEN + 1];
  char pages_number[5];
  char industry[INDUSTRY_LEN + 1];
  char type_l[TYPE_LEN + 1];
  char year[5];
  char kostil[1];
  char kind[KIND + 1];

  printf("Здравствуйте!В этой программе вам предоставлен список литературы");
  printf(",содержащий фамилию автора, название книги,издательство, количество"); 
  printf("страниц, вид литературы(1:техническая-отрасль, отечественная/"); 
  printf("переводная, год издания;2:художественная-роман, пьеса, стихи).\n");

  printf("Меню:\n1-вывести таблицу\n2-добавить запись в"); 
  printf(" таблицу\n3-удалить запись из таблицы\n4-отсортировать и вывести"); 
  printf("результаты времени сортировки различными методами\n");

  f = fopen("in2.txt","r");
  if(f == NULL)
    printf("Can't open file");
  else
  {
    size = get_records(f,data);
    fclose(f);
  }

  printf("Введите пункт меню: ");
  scanf("%d",&ask);
  if(ask > 0 && ask < 5)
  {
    if(ask == 1)
    {
      if(size != 0)
      {
        printf("Введите отрасль литературу по которой вы хотите получить: ");
        scanf("%s",ask_industry);
        printf("Введите год литературу до которого вы хотите получить: ");
        scanf("%d",&ask_year);
        if(strlen(ask_industry) > 0 && ask_year)
        {
          for(int i = 0; i < size; i++)
          {
            if(data[i].type1 == 1 && data[i].type1 == 1 && data[i].item.technical.year < ask_year && !strcmp(ask_industry,data[i].item.technical.industry) && !strcmp(type,data[i].item.technical.type))
            {
              printf("%d %s %s %s %d %d %s %s %d\n", data[i].number,data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
              find_count++;
            }
          }
          if(find_count == 0)
            printf("По вашему запросу ничего не найдено\n");
        }
        else
          printf("Вы некорректно ввели год или отрасль\n");
      }
      else
        printf("Файл пуст\n");
    }

    if(ask == 2)
    {
      f = fopen("out.txt","w");
      for(int i = 0; i < size; i++)
      {
        if(data[i].type1 == 1)
          fprintf(f, "%s|%s|%s|%d|%d|%s|%s|%d|\r\n",data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
        if(data[i].type1 == 2)
          fprintf(f, "%s|%s|%s|%d|%d|%s|\r\n",data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
      }
      data[size].number = size + 1;
      gets(kostil);
      printf("Введите фамилию автора: ");
      gets(author);
      decide_pole(0,0,size,strlen(author),data,author);
      printf("Введите название произведения: ");
      gets(title);
      decide_pole(0,1,size,strlen(title),data,title);
      printf("Введите издательство: ");
      gets(publisher);
      decide_pole(0,2,size,strlen(publisher),data,publisher);
      printf("Введите количество страниц: ");
      gets(pages_number);
      decide_pole(0,3,size,strlen(pages_number),data,pages_number);
      printf("Введите тип записи(1-технологическая,2-художественная): ");
      scanf("%d",&ask_type);
      if(ask_type != -1)
      {
        data[size].type1 = ask_type;
        if(ask_type == 1)
        {
          gets(kostil);
          printf("Введите отрасль: ");
          gets(industry);
          decide_pole(ask_type,5,size,strlen(industry),data,industry);
          printf("Введите тип(отечественная/переводая): ");
          gets(type_l);
          decide_pole(ask_type,6,size,strlen(type_l),data,type_l);
          printf("Введите год издания: ");
          gets(year);
          decide_pole(ask_type,7,size,strlen(year),data,year);
          fprintf(f, "%s|%s|%s|%d|%d|%s|%s|%d|\r\n",data[size].author,data[size].title,data[size].publisher,data[size].pages_number,data[size].type1,data[size].item.technical.industry,data[size].item.technical.type,data[size].item.technical.year);
          printf("%d %s %s %s %d %d %s %s %d\n", data[size].number,data[size].author,data[size].title,data[size].publisher,data[size].pages_number,data[size].type1,data[size].item.technical.industry,data[size].item.technical.type,data[size].item.technical.year);
        }
        if(ask_type == 2)
        {
          gets(kostil);
          printf("Введите тип художественной лиетратуры: ");
          gets(kind);
          decide_pole(ask_type,5,size,strlen(kind),data,kind);
          fprintf(f, "%s|%s|%s|%d|%d|%s|\r\n",data[size].author,data[size].title,data[size].publisher,data[size].pages_number,data[size].type1,data[size].item.artistic.kind);
          printf("%s|%s|%s|%d|%d|%s|\r\n",data[size].author,data[size].title,data[size].publisher,data[size].pages_number,data[size].type1,data[size].item.artistic.kind);
        }
      }
      fclose(f);
      write_file();
    }

    if(ask == 3)
    {
     for(int i = 0; i < size; i++)
      {
        if(data[i].type1 == 1)
          printf("%d %s %s %s %d %d %s %s %d \n",(i+1),data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
        if(data[i].type1 == 2)
          printf("%d %s %s %s %d %d %s \n",(i+1),data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
      }
    }
    if(ask ==  4)
    {
      for (int i = 0; i < size; i++)
      {
        sort1[i] = data[i];
        sort2[i] = data[i];
        sort3[i] = data[i];
        sort4[i] = data[i];
      }

      tb = tick(); 
      puzir_table(sort1,size);
      te = tick();
      printf("Пузырек таблицей: %llu\n", te - tb);

      tb = tick();
      rascheska_table(sort2,size);
      te = tick();
      printf("Расческа таблицей: %llu\n", te - tb);

      tb = tick();
      puzir_not_table(sort3,size);
      te = tick();
      printf("Пузырек без таблицы: %llu\n", te - tb);

      tb = tick();
      rascheska_not_table(sort4,size);
      te = tick();
      printf("Расческа без таблицы: %llu\n", te - tb);
    }
    //write_file();
  }
  else
    printf("Такого пункта меню нет\n");
}