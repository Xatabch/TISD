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

struct skobka//Структура, отвечающая за скобки
{
	char skobka;
	struct skobka *next;
};

struct skobka* create_skobka(char ch)//Создание элемента списка
{
    struct skobka *chr = malloc(sizeof(struct skobka));//Выделение памяти для списка

    if (chr)//если все корректно выделилось
    {
        chr->skobka = ch;//Присваиваю знаку его знак
        chr->next = NULL;//Это односвязный список, поэтому это указатель на следующий элемент(впринципе по моим рассуждениям, это похоже на реализацию стека)
    }
        
    return chr;//Созданная структура
}

//это значит добавить перед элементом заданным да
struct skobka* add_front(struct skobka *head,//сюда передаем голову эелемента, ну, че добавлять то будем да)Ну, в голову да)
                                   struct skobka *skobk)//а сюда соответсна структурку мою саму да
{
    skobk->next = head;//вот это интересно бл, тут добавили короче к нехту голову да, во дела, хотя вроде как доабвили указатель на след элемент да
    return skobk;//вернули структурку да
}

void apply(struct skobka *head,
             void (*f)(struct skobka*, void*),
                                         void* arg)
{
    for ( ; head; head = head->next)
        f(head, arg);
}


void print_person(struct skobka *skobk, void *arg)
{
    char *fmt = arg;

    printf(fmt, skobk->skobka);
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

//РЕАЛИЗАЦИЯ СТЕКА ОДНОСВЯЗНЫМ СПИСКОМ
//===================================================================

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В СПИСКЕ
int proverca_list(struct skobka *head,char *str)
{
  int i = strlen(str);

  struct skobka *tmp;


  while(i>=0)
  {

    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      printf("\n\n%c\n\n", head->skobka);
      if(str[i] == ')' && (head->skobka + 1) == str[i])
      {
        printf("SKOBKA: %c\n", (head->skobka + 1));
        tmp = pop_list(&head);
        free(tmp);
      }
      if(str[i] == ']' && (head->skobka + 2) == str[i])
      {
        printf("SKOBKA: %c\n", (head->skobka + 2));
        tmp = pop_list(&head);
        free(tmp);
      }
      if(str[i] == '}')
      {
        if((head->skobka+2) == str[i])
        {
          printf("SKOBKA: %c\n", (head->skobka + 2));
          tmp = pop_list(&head);
          free(tmp);
        }
      }
    }
    i--;
  }

  return 0;
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
struct skobka* get_char_list(char *str,int *n)
{
  int i = 0;

  struct skobka *head = NULL;
  struct skobka *node = NULL;

  int check_open = 0;

	while(str[i] != '\0')
	{
		if(str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
      check_open = 1;
      node = create_skobka(str[i]);
      head = add_front(head, node);
      *n = *n + 1;
    }
    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(check_open)
      {
        
      }
      if(!check_open)
        head = NULL;
    }
    i++;
  }
  return head;
}

//УДАЛЕНИЕ ИЗ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
struct skobka *pop_list(struct skobka **head)
{
    struct skobka *out;
    if ((*head) == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}

//======================================================================

int main(void)
{
  struct skobka *head = NULL;
  char str[128];
  int n = 0;
  int error;

	printf("Введите выражние: ");
  enter(str);
  printf("%s\n", str);
  head = get_char_list(str,&n);
  if(head)
  {
    apply(head,print_person,"%c\n");
    error = proverca_list(head,str);
    printf("%d\n",error);
  }
  else
    printf("ERRRRORRR");


}