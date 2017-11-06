//Создать программу работы со стеком, 
//выполняющую операции добавление, 
//удаления элементов и вывод текущего состояния стека. 
//Реализовать стек: а) массивом; б) списком. 
//Все стандартные операции со стеком должны быть оформлены подпрограммами. 
//При реализации стека списком в вывод текущего состояния стека добавить просмотр адресов элементов стека и 
//создать свой список или массив свободных областей (адресов освобождаемых элементов) с выводом его на экран.

//Проверить правильность расстановки скобок трех типов (круглых, квадратных и фигурных) в выражении.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define STACK_UNDERFLOW -100
#define STACK_OVERFLOW -200
#define STACK_MAX_SIZE 101
#define OK 0
#define BRACKET_ERROR -1

unsigned long long tick(void)
{
  unsigned long long d;
  __asm__ __volatile__ ("rdtsc" : "=A" (d) );
  return d;
}

long long
mtime()
{
  struct timeval t;
  gettimeofday(&t, NULL);
  long long mt = (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
  return mt;
}

void enter(char *str)
{
  int c;
  int i = 0;

  while((c = getchar()) != EOF && c != '\n')
  {
    str[i] = c;
    i++;
  }
  str[i] = '\0';
}

//РЕАЛИЗАЦИЯ СТЕКА СТАТИЧЕСКИМ МАССИВОМ
//======================================================

//СТАТИЧЕСКИЙ МАССИВ
struct skobka_array {

  char data[STACK_MAX_SIZE];
  size_t size;

};

//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СТЕК,РЕАЛИЗОВАННЫЙ МАССИВОМ
void push_array(struct skobka_array *array, const char value)
{
  if(array->size >= STACK_MAX_SIZE) {
    printf("Стек переполнен\n");
    exit(STACK_OVERFLOW);
  }
  array->data[array->size] = value;
  array->size++;
}

//УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ СТЕКА, РЕАЛИЗОВАННОГО МАССИВОМ
char pop_array(struct skobka_array *array) 
{
  if(array->size == 0) {
    printf("Нижняя граница стека\n");
    exit(STACK_UNDERFLOW);
  }
  array->size--;
  return array->data[array->size];
}

//ПЕЧАТЬ СТЕКА, РЕАЛИЗОВАННОГО МАССИВОМ
void printStackValue(char value) 
{
  printf("|%13c             |\n", value);
}

void printStack(const struct skobka_array *array, void (*printStackValue)(const char)) 
{
  int i;
  int len = array->size - 1;

  for (i = 0; i < len; i++)
  {
    printStackValue(array->data[i]);
  }
  if(array->size != 0) {
    printStackValue(array->data[i]);
  }
  printf("\n");
}

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В МАССИВЕ
void proverca_array(int i, struct skobka_array *array, char *str, int *count, int *count1, int *n)
{
  char tmp;

  while(str[i] != '\0')
  {
    if (str[i] == '(' || str[i] == '[' || str[i] == '{')
      break;

    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(str[i] == ')' && (array->data[array->size - 1] + 1) == str[i])
      {
        *count = *count + 1;
        *count1 = *count1 + 1;
        *n = *n - 1;
        tmp = pop_array(array);
        printf("%c\n", tmp);
      }
      if(str[i] == ']' && (array->data[array->size - 1] + 2) == str[i])
      {
        *count = *count + 1;
        *count1 = *count1 + 1;
        *n = *n - 1;
        tmp = pop_array(array);
        printf("%c\n", tmp);
      } 
      if(str[i] == '}' && (array->data[array->size - 1] + 2) == str[i])
      {
        *count = *count + 1;
        *count1 = *count1 + 1;
        *n = *n - 1;
        tmp = pop_array(array);
        printf("%c\n",tmp);
      }
    }
  i++;
  }
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО МАССИВОМ
int get_char_array(char *str,int *n,int *count, int *bracket_count,int *count_open_brackets)
{
  int i = 0;
  int check_open = 0;
  int count1 = 0;//веду подсчет элементов в стеке

  struct skobka_array array;
  array.size = 0;

  while(str[i] != '\0')
  {
    if(str[i] == '(' || str[i] == '[' || str[i] == '{')
    {
      check_open = 1;
      push_array(&array,str[i]);
      *count_open_brackets = *count_open_brackets + 1;
      *n = *n + 1;
    }
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(check_open)
        proverca_array(i, &array, str, count, &count1, n);
      if(!check_open)
        return BRACKET_ERROR;
    }
    i++;
  }

  i = 0;
  while(str[i] != '\0')
  {
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
      *bracket_count = *bracket_count + 1;
    i++;
  }

  return OK;
}

//======================================================



//РЕАЛИЗАЦИЯ СТЕКА ОДНОСВЯЗНЫМ СПИСКОМ
//===================================================================

//СТРУКТУРА ОТВЕЧАЮЩАЯ ЗА СКОБКИ
struct skobka
{
  char skobka;
  struct skobka *next;
};

//СОЗДАНИЕ ЭЛЕМЕНТА СПИСКА
struct skobka* create_skobka(char ch)//Создание элемента списка
{
  struct skobka *chr = malloc(sizeof(struct skobka));

  if (chr)
  {
      chr->skobka = ch;
      chr->next = NULL;
  }
        
  return chr;
}
struct skobka* add_front(struct skobka *head,
                                   struct skobka *skobk)
{
    skobk->next = head;
    return skobk;
}

void count(struct skobka *ch, void *arg)
{
    int *counter = arg;

    (*counter)++;
}

//УДАЛЕНИЕ ИЗ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
struct skobka *pop_list(struct skobka **head)
{
    struct skobka *out;

    if ((*head) == NULL) 
    {
      printf("Нижняя граница стека\n");
      exit(STACK_UNDERFLOW);
    }

    out = *head;
    *head = (*head)->next;
    return out;
}

void apply(struct skobka *head,
             void (*f)(struct skobka*, void*),
                                         void* arg)
{
    for ( ; head; head = head->next)
        f(head, arg);
}

//ВЫВОД СТЕКА
void print_ch(struct skobka *skobk, void *arg)
{
    char *fmt = arg;

    printf(fmt, skobk->skobka, &skobk->skobka);
}

//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СТЕК
void push_list(char str,struct skobka **head)
{
  //int n = 0;

  //apply(*head,count,&n);
  //if(n >= STACK_MAX_SIZE)
  //{
  //  printf("Стек переполнен\n");
  //  exit(STACK_OVERFLOW);
  //}
  struct skobka *node = NULL;

  node = create_skobka(str);
  *head = add_front(*head, node);
}

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В СПИСКЕ
struct skobka *proverca_list(int i, struct skobka *head, char *str,int *count, int *count1,int *n)
{
  struct skobka *tmp;

  while(str[i] != '\0' && *n > 0)
  {
    if (str[i] == '(' || str[i] == '[' || str[i] == '{')
      break;

    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(head != NULL)
      {
        if(str[i] == ')' && (head->skobka + 1) == str[i])
        {
          *count = *count + 1;
          *count1 = *count1 + 1;
          *n = *n - 1;
          tmp = pop_list(&head);
          //printf("|%c|\n",tmp->skobka);
          free(tmp);
        }
        if(str[i] == ']' && (head->skobka + 2) == str[i])
        {
          *count = *count + 1;
          *count1 = *count1 + 1;
          *n = *n - 1;
          tmp = pop_list(&head);
          //printf("|%c|\n",tmp->skobka);
          free(tmp);
        }
        if(str[i] == '}' && (head->skobka+2) == str[i])
        {
          *count = *count + 1;
          *count1 = *count1 + 1;
          *n = *n - 1;
          tmp = pop_list(&head);
          //printf("|%c|\n",tmp->skobka);
          free(tmp);
        }
      }
    }
  i++;
  }

  return head;
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
int get_char_list(char *str,int *n,int *count, int *bracket_count,int *count_open_brackets)
{
  int i = 0;
  int check_open = 0;
  int count1 = 0;//веду подсчет элементов в стеке

  struct skobka *head = NULL;

	while(str[i] != '\0')
	{
		if(str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
      check_open = 1;
      push_list(str[i],&head);
      *n = *n + 1;
      *count_open_brackets = *count_open_brackets + 1;
    }
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(check_open)
        head = proverca_list(i, head, str, count, &count1, n);
      if(!check_open)
       return BRACKET_ERROR;
    }
    i++;
  }

  i = 0;
  while(str[i] != '\0')
  {
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
      *bracket_count = *bracket_count + 1;
    i++;
  }
  return OK;
}

//======================================================================

void times()
{
  //unsigned long long tb, te;
  struct skobka *head3 = NULL;
  struct skobka_array array3;
  array3.size = 0;
  struct timeval ta, tz;

  //te = tick();
  gettimeofday(&ta,NULL);
  for(int i = 0; i < 100; i++)
    push_list('v',&head3);
  for(int i = 0; i < 100; i++)
  {
    pop_list(&head3);
  }
  gettimeofday(&tz,NULL);
  //tb = tick();
  printf("Время добавление и удаления элемента в стек, реализованный списком: %lf (мс)\n", tz.tv_sec - ta.tv_sec + (tz.tv_usec - ta.tv_usec)/1000000.0);

  //te = tick();
  gettimeofday(&ta,NULL);
  for(int i = 0; i < 100; i++)
    push_array(&array3,'v');
  for(int i = 0; i < 100; i++)
  {
    pop_array(&array3);
  }
  gettimeofday(&tz,NULL);
  //tb = tick();
  printf("Время добавления и удаления элемента в стек, реализованный массивом: %lf (мс)\n", tz.tv_sec - ta.tv_sec + (tz.tv_usec - ta.tv_usec)/1000000.0);
  printf("\n");

}


int main(void)
{
  struct skobka *head2 = NULL;
  struct skobka *delete_list = NULL;

  struct skobka_array array2;
  array2.size = 0;
  char delete_array;

  char str[128];
  char *delete[50];//массив для удаленных элементов
  int k = 0;//счетски для удаленных элементов
  int n = 0;
  int count = 0;
  int ask;
  int error;
  int count_open_brackets;
  int bracket_count;

  char ch;

  while(ask != 0)
  {
    printf("Меню\n");
    printf("1 - проверить скобки в выражении (СПИСОК)\n");
    printf("2 - проверить скобки в выражении (МАССИВ)\n");
    printf("3 - добавить новый элемент в стек (СПИСОК)\n");
    printf("4 - добавить новый элемент в стек (МАССИВ)\n");
    printf("5 - удалить элемент из стека (СПИСОК)\n");
    printf("6 - удалить элемент из стека (МАССИВ)\n");
    printf("7 - показать стек (СПИСОК)\n");
    printf("8 - показать стек (МАССИВ)\n");
    printf("9 - показать список доступной памяти\n");
    printf("10 - замерить время выполнения и память реализаций стека массивом и списком\n");
    printf("0 - выход\n");
    printf("\n>> ");
    scanf("%d",&ask);
    printf("\n\n");

    if (ask == 1)
    {
      n = 0;
      count_open_brackets = 0;
      count = 0;
      bracket_count = 0;
      error = 0;
      enter(str);
      printf("Введите выражние: ");
      enter(str);
      error = get_char_list(str,&n,&count,&bracket_count,&count_open_brackets);
      if(!error)
      {
        if(count_open_brackets == count && count_open_brackets == bracket_count)
          printf("\n\nСкобки расставлены верно\n\n");
        else
          printf("\n\nСкобки расставлены неверно\n\n");
      }
      else
        printf("Ошибка выполнения операции проверки скобок");
    }
    if(ask == 2)
    {
      n = 0;
      count_open_brackets = 0;
      count = 0;
      bracket_count = 0;
      error = 0;
      enter(str);
      printf("Введите выражение: ");
      enter(str);

      error = get_char_array(str, &n, &count,&bracket_count,&count_open_brackets);
      if(!error)
      {
        if(count_open_brackets == count && count_open_brackets == bracket_count)
          printf("\n\nСкобки расставлены верно\n\n");
        else
          printf("\n\nСкобки расставлены неверно\n\n");
      }
      else
        printf("Ошибка выполнения операции проверки скобок\n");

    }

    if(ask == 3)
    {
      scanf("%c",&ch);
      printf("Введите элемент, который вы хотите добавить в стек: ");
      scanf("%c",&ch);

      push_list(ch,&head2);
    }

    if(ask == 4)
    {
      scanf("%c",&ch);
      printf("Введите элемент, который вы хотите добавить в стек: ");
      scanf("%c",&ch);
      push_array(&array2,ch);

    }

    if(ask == 5)
    {
      printf("----------------------------\n");
      printf("|   Элемент  |    Адрес    |\n");
      printf("----------------------------\n");
      delete_list = pop_list(&head2);
      delete[k] = &delete_list->skobka;
      k++;
      printf("|%8c    |  %4p|\n",delete_list->skobka,&delete_list->skobka);

      free(delete_list);
    }

    if(ask == 6)
    {
      printf("----------------------------\n");
      printf("|          Элемент         |\n");
      printf("----------------------------\n");
      delete_array = pop_array(&array2);
      printf("|%13c             |\n", delete_array);
    }

    if(ask == 7)
    {
      if(head2 != NULL)
      {
        printf("----------------------------\n");
        printf("|   Элемент  |    Адрес    |\n");
        printf("----------------------------\n");
        apply(head2,print_ch,"|%8c    |  %4p|\n");
      }
      else
        printf("\nСтек пуст\n");
    }

    if(ask == 8)
    {
      if(array2.size != 0)
      {
        printf("----------------------------\n");
        printf("|          Элемент         |\n");
        printf("----------------------------\n");
        printStack(&array2,printStackValue);
      }
      else
        printf("\nСтек пуст\n");
    }

    if(ask == 9)
    {
      printf("----------------------------\n");
      printf("|           Адрес          |\n");
      printf("----------------------------\n");
      for (int i = 0; i < k; i++)
        printf("|%20p      |\n",delete[i]);
    }

    if(ask == 10)
    {
      times();
    }
  }

  return 0;


}