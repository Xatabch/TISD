#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
  struct literature_list tech;
  //int i;
  char p[] = "большой черный";
  //tech = malloc(sizeof(struct literature_list));

  tech.number = 1;
  tech.kind = KIND_TECHNICAL;
  for (int i = 0; i < sizeof(p); i++)
  {
    tech.item.technical.author[i] = p[i];
  }
  //i=0;
  printf("%s\n", tech.item.technical.author);
  tech.item.technical.year = 2015;



}