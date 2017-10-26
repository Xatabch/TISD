//sructs
#ifndef __MAIN_H__
#define __MAIN_H__

#define NAME_LEN 40
#define TITLE_LEN 50
#define PUBLISHER_LEN 40
#define INDUSTRY_LEN 40
#define TYPE_LEN 40
#define KIND 40

struct dop_array {
  int n;
  char author[NAME_LEN+1];
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
#endif