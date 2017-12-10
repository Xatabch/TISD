/*Цель работы – построить и обработать хеш-таблицы, 
сравнить эффективность поиска в сбалансированных деревьях, 
в двоичных деревьях поиска и в хеш-таблицах. 
Сравнить эффективность устранения коллизий при внешнем и внутреннем хешировании.*/

/*Задание: 
построить хеш-таблицу по указанным данным. 
Сравнить эффективность поиска в сбалансированном двоичном дереве, в двоичном дереве поиска и в хеш-таблице (используя открытую и закрытую адресацию). 
Вывести на экран деревья и хеш-таблицы. 
Подсчитать среднее количество сравнений для поиска данных в указанных структурах. 
Произвести реструктуризацию хеш-таблицы, если среднее количество сравнений больше указанного. 
Оценить эффективность использования этих структур (по времени и памяти) для поставленной задачи. 
Оценить эффективность поиска в хеш-таблице при различном количестве коллизий и при различных методах  их разрешения.*/

/*Используя предыдущую программу (задача №6), сбалансировать полученное дерево . Вывести его на экран в виде дерева.---
Построить хеш-таблицу из чисел файла.---
Осуществить поиск введенного целого числа в двоичном дереве поиска, в сбалансированном дереве и в хеш-таблице.--- 
Сравнить время поиска, объем памяти и количество сравнений при использовании различных структур данных.*/


#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "insert.h"//вставка элемента в двоичное дерево
#include "delete.h"//удаление элемента из двоичного дерева
#include "apply.h"//пямой обход дерева
#include "getnum.h"//получение чисел из файла и создание дерева.
#include "createdot.h"//создание .gv файла
#include "tick.h"//замер времени.
#include "rotateright.h"// правый поворот вокруг p
#include "rotateleft.h"// левый поворот вокруг q
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев
#include "balance.h"//балансировка дерева
#include "insertavl.h"//функция вставки в балансированное дерево(пока что не требуется)
#include "balancetree.h"//балансировка дерева
#include "openhash.h"//хеш-таблица с использованием открытой адресации(метод цепочек)
#include "closehash.h"//хеш-таблица с использованием закрытой адрсации(линейная адресация)
#include "find.h"//поиск в бинарном дереве поиска

int main(void)
{
  FILE *f;
  tree *root = NULL;
  tree *avl_root = NULL;
  tree *fnd = NULL;
  Hashmap *map = NULL;
  Hasharray *array = NULL;
  int v;
  int sravneniya = 0;
  unsigned long long tb, te;
  int ask = -1;
  int find_element;

  f = fopen("in.txt","r");
  if(!f)
    printf("Can't open file\n");
  else
  {
    printf("\n\n\t\t\t\tМЕНЮ\n\n");
    printf("\t1 - Построить и вывести несбалансированное дерево\n");
    printf("\t2 - Сбаласировать дерево и вывести\n");
    printf("\t3 - Построить хеш-табицу с открытой адресацией(метод цепочек)\n");
    printf("\t4 - Построить хеш-таблицу с закрытой адресацией(линейная адресация)\n");
    printf("\t5 - Ввести элемент для поиска и вывести замеры времени сравнения и память в различных структурах\n");

    root = get_num(f);
    fclose(f);
    f = fopen("in.txt","r");
    avl_root = get_num(f);
    fclose(f);
    f = fopen("in.txt","r");
    map = get_open_hash(f);
    fclose(f);
    f = fopen("in.txt","r");
    array = get_close_hash(array,f);
    fclose(f);

    while(1)
    {
      printf("\n\n>> ");
      scanf("%d",&ask);
      if((ask >= 0) && (ask <= 5))
      {
        if(ask == 1)
        {
          printf("\n\tПрямой обход несбалансированного дерева: ");
          apply_pre(root, print, "%d ");
        }

        if(ask == 2)
        { 
          avl_root = balance_tree(avl_root);
          printf("\n\tПрямой обход авл дерева: ");
          apply_pre(avl_root, print, "%d ");
        }

        if(ask == 3)
        {
          printf("\n\t'Обход' хеш-таблицы с открытой адресацией:\n\n");
          mapIterate(map,printEntry, NULL);
        }

        if(ask == 4)
        {
          printf("\n\t'Обход' хеш-таблицы с закрытой адресацией:\n\n");
          for(int i = 0; i < array->size; i++)
            printf("\t\t\t%d:%d\n", i, array->arr[i]);
        }

        if(ask == 5)
        {
          printf("\n Введите элемент для поиска: ");
          scanf("%d",&find_element);
          printf("\n\n");
          if(find_element)
          {
            tb = tick();
            fnd = lookup(root, find_element,&sravneniya);
            te = tick();
            if(fnd)
            {
              printf("\t\t\tНЕСБАЛАНСИРОВАННОЕ ДЕРЕВО\n\n");
              printf(">>\t|Элемент %d найден|\n",fnd->name);
              printf(">>\t|Время поиска: %llu|\n", te-tb);
              printf(">>\t|Сравнения: %d|\n",sravneniya);
              printf("\n\n");
            }
            else
            {
              printf(" Такого элемента в структурах нет\n");
              break;
            }
            sravneniya = 0;

            tb = tick();
            fnd = lookup(avl_root, find_element,&sravneniya);
            te = tick();
            printf("\t\t\tАВЛ ДЕРЕВО\n\n");
            printf(">>\t|Время поиска: %llu|\n", te-tb);
            if(fnd)
              printf(">>\t|Элемент %d найден для его получения потребовалось %d сравнение(ий) заняло n памяти|\n", fnd->name,sravneniya);
            sravneniya = 0;

            tb = tick();
            v = get_open(map,find_element,&sravneniya);
            te =tick();
            printf("\nВремя поиска элемента в хеш-таблице с открытой адресацией: %llu", te-tb);
            if(v != -100000000)
              printf("\nЭлемент %d найден, для его получения потребовалось %d сравнение(ий)\n", v,sravneniya);
            sravneniya = 0;

            tb = tick();
            v = get_close(array,find_element,&sravneniya);
            te =tick();
            printf("\nВремя поиска элемента с закрытой адресацией: %llu", te-tb);
            if(v != -10000000)
              printf("\nЭлемент %d найден, для его получения потребовалось %d сравнение(ий)\n\n", v, sravneniya);
          }

          if(ask == 0)
            break;
        }
      }
    }

  }

  f = fopen("tree_not_balance.gv", "w");
  if(!f)
    printf("Can't open file\n");
  else
  {
    export_to_dot(f, "tree_not_balance",root);
    fclose(f);
  }

  f = fopen("tree_balance.gv", "w");
  if(!f)
    printf("Can't open file\n");
  else
  {
    export_to_dot(f, "tree_balance",avl_root);
    fclose(f);
  }

  return 0;
}