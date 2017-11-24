/*Построить дерево в соответствии со своим вариантом задания. 
Вывести его на экран в виде дерева. 
Реализовать основные операции работы с деревом: обход дерева, включение,  исключение и поиск узлов. 
Сравнить эффективность алгоритмов сортировки и поиска в зависимости от высоты деревьев и степени их ветвления.*/

/*1. В текстовом файле содержатся целые числа. 
Построить двоичное дерево из чисел файла. 
Вывести его на экран в виде дерева. 
Используя подпрограмму, определить количество узлов дерева на каждом уровне. 
Добавить число в дерево и в файл. 
Сравнить время добавление в указанные структуры.*/

#include <stdio.h>

#include "main.h" //структуры
#include "createnode.h"//создание узла дерева
#include "insert.h"//вставка зла в двоичное дерево
#include "applypre.h"//пямой обход дерева
#include "getnum.h"//получение чисел из файла и создание дерева.

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
  }

  return 0;
}