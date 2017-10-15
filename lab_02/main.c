#include <stdio.h>
#include <string.h>

#include "kindbook.h"
#include "main.h"
#include "decidepole.h"
#include "getnewparam.h"
#include "getrecords.h"
#include "sorttable.h"
#include "sortnottable.h"
#include "writefile.h"
#include "readline.h"
#include "tick.h"

#define NAME_LEN 40
#define TITLE_LEN 50
#define PUBLISHER_LEN 40
#define INDUSTRY_LEN 40
#define TYPE_LEN 40
#define KIND 40

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
  int delete = -1;

  printf("\n\nЗдравствуйте! В этой программе вам представлен список литературы");
  printf(", содержащий фамилию автора, название книги,издательство, количество"); 
  printf(" страниц, вид литературы(1: техническая- отрасль, отечественная/"); 
  printf("переводная, год издания; 2: художественная- роман, пьеса, стихи).\n\n");

  printf("Меню:\n1- вывести таблицу из переводных записей по выбору\n2- добавить запись в"); 
  printf(" таблицу новую запись\n3- удалить запись из таблицы\n4- отсортировать и вывести"); 
  printf(" результаты времени сортировки различными методами\n\n");

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
        printf("\n");
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
      read_line(kostil,sizeof(kostil));
      printf("Введите фамилию автора: ");
      read_line(author,sizeof(author));

      printf("Введите название произведения: ");
      read_line(title,sizeof(title));

      printf("Введите издательство: ");
      read_line(publisher,sizeof(publisher));

      printf("Введите количество страниц: ");
      read_line(pages_number,sizeof(pages_number));

      printf("Введите тип записи(1-технологическая,2-художественная): ");
      scanf("%d",&ask_type);
      if(ask_type != -1)
      {
        if(ask_type == 1)
        {
          read_line(kostil,sizeof(kostil));
          printf("Введите отрасль: ");
          read_line(industry,sizeof(industry));

          printf("Введите тип(отечественная/переводая): ");
          read_line(type_l,sizeof(type_l));

          printf("Введите год издания: ");
          read_line(year,sizeof(year));

          fprintf(f, "%s|%s|%s|%s|1|%s|%s|%s|\r\n",author,title,publisher,pages_number,industry,type_l,year);
          
        }
        if(ask_type == 2)
        {
          read_line(kostil,sizeof(kostil));
          printf("Введите тип художественной лиетратуры: ");
          read_line(kind,sizeof(kind));

          fprintf(f, "%s|%s|%s|%s|2|%s|\r\n",author,title,publisher,pages_number,kind);
        }
      }

      fclose(f);
      write_file(-1);
    }



    if(ask == 3)
    {
      f = fopen("out.txt","w");
      for(int i = 0; i < size; i++)
      {
        if(data[i].type1 == 1)
        {
          fprintf(f, "%s|%s|%s|%d|%d|%s|%s|%d|\r\n",data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
          printf("%d %s %s %s %d %d %s %s %d \n",(i+1),data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.technical.industry,data[i].item.technical.type,data[i].item.technical.year);
        }
        if(data[i].type1 == 2)
        {
          fprintf(f, "%s|%s|%s|%d|%d|%s|\r\n",data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
          printf("%d %s %s %s %d %d %s \n",(i+1),data[i].author,data[i].title,data[i].publisher,data[i].pages_number,data[i].type1,data[i].item.artistic.kind);
        }
      }
      fclose(f);

      printf("Введите номер строки, которую вы хотите удалить: ");
      scanf("%d",&delete);
      if(delete != -1 && (size - 1) >= 40)
        write_file(delete);
      else
        printf("Таблица должна состоять из более чем 40 элементов, вы не можете удалить данный элемент\n");

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
  }
  else
    printf("Такого пункта меню нет\n");
}