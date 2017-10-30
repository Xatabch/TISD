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
    if ((*head) == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}

//ПРОВЕРКА НА КОРРЕКТНОСТЬ РАССТАВЛЕННЫХ СКОБОК В СПИСКЕ
void proverca_list(int i, struct skobka *head, char *str,int *count)
{
  struct skobka *tmp;

  while(str[i] != '\0')
  {
    if (str[i] == '(' || str[i] == '[' || str[i] == '{')
      break;

    if(str[i] == ')' || str[i] == ']' || str[i] == '}')
    {
      if(str[i] == ')' && (head->skobka + 1) == str[i])
      {
        *count = *count + 1;
        tmp = pop_list(&head);
        free(tmp);
      }
      if(str[i] == ']' && (head->skobka + 2) == str[i])
      {
        *count = *count + 1;
        tmp = pop_list(&head);
        free(tmp);
      }
      if(str[i] == '}')
      {
        if((head->skobka+2) == str[i])
        {
          *count = *count + 1;
          tmp = pop_list(&head);
          free(tmp);
        }
      }
    }
  i++;
  }
}

//ЗАПОЛНЕНИЕ СТЕКА, РЕАЛИЗУЕМОГО СПИСКОМ
struct skobka* get_char_list(char *str,int *n,int *count)
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
        proverca_list(i, head, str, count);
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
  char str[128];
  int n = 0;
  int count = 0;
  //int error;

	printf("Введите выражние: ");
  enter(str);
  head = get_char_list(str,&n,&count);
  if(head)
  {
    if(n != count)
      printf("Вы допустили ошибку в расстановке скобок\n");
    else
      printf("Скобки расставлены верно\n");
  }
  else
    printf("ERRRRORRR");


}