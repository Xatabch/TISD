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

int main(void)
{
  struct tree_node *root = NULL;
  struct tree_node *node;

  node = create_node("f");
  root = insert(root, node);

  node = create_node("b");
  root = insert(root, node);

  node = create_node("k");
  root = insert(root, node);

  node = create_node("a");
  root = insert(root, node);

  node = create_node("d");
  root = insert(root, node);

  node = create_node("g");
  root = insert(root, node);

  node = create_node("l");
  root = insert(root, node);

  apply_pre(root, print, "%s ");
  printf("\n");

  return 0;
}