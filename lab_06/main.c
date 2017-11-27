/*Построить дерево в соответствии со своим вариантом задания. 
Вывести его на экран в виде дерева.----
Реализовать основные операции работы с деревом:--- обход дерева, включение,  исключение и поиск узлов.---*/

/*1. В текстовом файле содержатся целые числа.

Построить двоичное дерево из чисел файла. ----
Вывести его на экран в виде дерева. -----
Используя подпрограмму, определить количество узлов дерева на каждом уровне. 
Добавить число в дерево и в файл. 
Сравнить время добавление в указанные структуры.*/

#include <stdio.h>

#include "main.h" //структуры
#include "insert.h"//вставка зла в двоичное дерево
#include "apply.h"//пямой обход дерева
#include "getnum.h"//получение чисел из файла и создание дерева.
#include "createdot.h"//создание .gv файла
#include "find.h"//поиск в дереве узла
#include "delete.h"//удаление узла из дерева
#include "pointcount.h"//подпрограмму, которая определяет количество узлов дерева на каждом уровне.

#define CANT_OPEN_FILE -1

int main(void)
{
  FILE *f;
  struct tree_node *root = NULL;

  f = fopen("in.txt","r");
  if(!f)
    printf("Can't open file\n");
  else
  {
    root = get_num(f);
    apply_pre(root, print, "%d ");
    count_points(root);

    f = fopen("tree.gv", "w");

    if(!f)
    {
      printf("Can't open file\n");
      return CANT_OPEN_FILE;
    }
    else
    {
      export_to_dot(f, "tree", root);
      fclose(f);
    }

  }

  return 0;
}