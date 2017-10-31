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

#define STACK_UNDERFLOW -100
#define STACK_OVERFLOW -200
#define STACK_MAX_SIZE 20
#define OK 0
#define BRACKET_ERROR -1

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
  printf("%c", value);
}

void printStack(const struct skobka_array *array, void (*printStackValue)(const char)) 
{
  int i;
  int len = array->size - 1;

  printf("stack %lu >",array->size);

  for (i = 0; i < len; i++)
  {
    printStackValue(array->data[i]);
    printf(" | ");
  }
  if(array->size != 0) {
    printStackValue(array->data[i]);
  }
  printf("\n");
}

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В МАССИВЕ
void proverca_array(int i, struct skobka_array *array, char *str,int *count)
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
        tmp = pop_array(array);
        printf("%c\n", tmp);
      }
      if(str[i] == ']' && (array->data[array->size - 1] + 2) == str[i])
      {
        *count = *count + 1;
        tmp = pop_array(array);
        printf("%c\n", tmp);
      }
      if(str[i] == '}')
      {
        if((array->data[array->size - 1] + 2) == str[i])
        {
          *count = *count + 1;
          tmp = pop_array(array);
        }
      }
    }
  i++;
  }
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО МАССИВОМ
int get_char_array(char *str,int *n,int *count)
{
  int i = 0;

  int check_open = 0;

  struct skobka_array array;
  array.size = 0;

  while(str[i] != '\0')
  {
    if(str[i] == '(' || str[i] == '[' || str[i] == '{')
    {
      check_open = 1;
      push_array(&array,str[i]);
      *n = *n + 1;
    }
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(check_open)
        proverca_array(i, &array, str, count);
      if(!check_open)
        return BRACKET_ERROR;
    }
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

//ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СТЕК
void push_list(char str,struct skobka **head)
{
  struct skobka *node = NULL;

  node = create_skobka(str);
  *head = add_front(*head, node);
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

    printf(fmt, skobk->skobka);
}

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В СПИСКЕ
void proverca_list(int i, struct skobka *head, char *str,int *count, int *bracket_count)
{
  struct skobka *tmp;

  while(str[i] != '\0')
  {
    if (str[i] == '(' || str[i] == '[' || str[i] == '{')
      break;

    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      *bracket_count = *bracket_count + 1;
      if(str[i] == ')' && (head->skobka + 1) == str[i])
      {
        *count = *count + 1;
        tmp = pop_list(&head);
        printf("%c",tmp->skobka);
        //free(tmp);
      }
      if(str[i] == ']' && (head->skobka + 2) == str[i])
      {
        *count = *count + 1;
        tmp = pop_list(&head);
        printf("%c",tmp->skobka);
        //free(tmp);
      }
      if(str[i] == '}' && (head->skobka+2) == str[i])
      {
        *count = *count + 1;
        tmp = pop_list(&head);
        printf("%c",tmp->skobka);
        //free(tmp);
      }
    }
  i++;
  }
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
struct skobka* get_char_list(char *str,int *n,int *count, int *bracket_count)
{
  int i = 0;
  int check_open = 0;

  struct skobka *head = NULL;

	while(str[i] != '\0')
	{
		if(str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
      check_open = 1;
      push_list(str[i],&head);
      *n = *n + 1;
    }
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(check_open)
        proverca_list(i, head, str, count, bracket_count);
      if(!check_open)
        head = NULL;
    }
    i++;
  }
  return head;
}

//======================================================================


int main(void)
{
  struct skobka *head = NULL;
  struct skobka *head2 = NULL;
  struct skobka *delete_list = NULL;

  struct skobka_array array2;
  array2.size = 0;
  char delete_array;

  char str[128];
  int n = 0;
  int count = 0;
  int ask;
  int error;
  int bracket_count;

  char ch;

  while(ask != 9)
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
    printf("9 - выход\n");
    printf("\n>> ");
    scanf("%d",&ask);
    printf("\n\n");

    if (ask == 1)
    {
      n = 0;
      count = 0;
      bracket_count = 0;
      enter(str);
      printf("Введите выражние: ");
      enter(str);
      head = get_char_list(str,&n,&count,&bracket_count);
      if(head)
      {
        if(n == count && n == bracket_count)
          printf("Скобки расставлены верно\n");
        else
          printf("Скобки расставлены неверно\n");
         printf("%d\t%d",count,bracket_count);
      }
      else
        printf("ERRRRORRR");
    }
    if(ask == 2)
    {
      n = 0;
      count = 0;
      enter(str);
      printf("Введите выражение: ");
      enter(str);

      error = get_char_array(str, &n, &count);
      if(error == OK)
      {
        if(n == count)
          printf("Скобки расставлены верно\n");
        else
          printf("Ошибка в расставлении скобок\n");
      }
      else
        printf("Ошибка в расставлении скобок\n");

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
      delete_list = pop_list(&head2);
      printf("\n|%c|\n",delete_list->skobka);
    }

    if(ask == 6)
    {
      delete_array = pop_array(&array2);
      printf("%c",delete_array);
    }

    if(ask == 7)
    {
      if(head2 != NULL)
        apply(head2,print_ch,"\n|%c|\n");
      else
        printf("Стек пуст");
    }

    if(ask == 8)
    {
      printStack(&array2,printStackValue);
    }
  }


}