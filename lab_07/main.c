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

/*Используя предыдущую программу (задача №6), сбалансировать полученное дерево. Вывести его на экран в виде дерева. 
Построить хеш-таблицу из чисел файла. Осуществить поиск введенного целого числа в двоичном дереве поиска, в сбалансированном дереве и в хеш-таблице. 
Сравнить время поиска, объем памяти и количество сравнений при использовании различных структур данных.*/


#include <stdio.h>
#include <stdlib.h>

#include "main.h" //структуры
#include "insert.h"//вставка зла в двоичное дерево
#include "apply.h"//пямой обход дерева
#include "getnum.h"//получение чисел из файла и создание дерева.
#include "createdot.h"//создание .gv файла
#include "tick.h"//замер времени.
#include "rotateright.h"//// правый поворот вокруг p
#include "rotateleft.h"// левый поворот вокруг q
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев
#include "balance.h"//балансировка дерева
#include "insertavl.h"

tree *apply_balance(tree *tree)
{
  if (tree == NULL)
        return NULL;
  apply_balance(tree->left);
  printf("N: [%d %d]\n",tree->name,tree->height );
  if((tree->right) != NULL)
    printf("R: [%d %d]\n",(tree->right)->name,(tree->right)->height);
  if((tree->left) != NULL)
    printf("L: [%d %d]\n",(tree->left)->name,(tree->left)->height);
  tree = balance(tree); 
  apply_balance(tree->right); 

  return tree;
 }


int main(void)
{
  FILE *f;
  struct tree_node *root = NULL;
  //struct tree_node *avl_root = NULL;

  f = fopen("in.txt","r");
  if(!f)
    printf("Can't open file\n");
  else
  {
    root = get_num(f);
    fclose(f);

    printf("\nПрямой обход: ");
    apply_pre(root, print, "%d ");
    printf("\n");

    // f = fopen("in.txt","r");
    // if(!f)
    //   printf("Can't open file\n");
    // else
    // {
    //   avl_root = get_avl_tree(f);
    //   fclose(f);
    //   printf("\nПрямой обход(1): ");
    //   apply_pre(avl_root, print, "%d ");
    //   printf("\n");

    // }

    root = apply_balance(root);
    printf("\nПрямой обход(2): ");
    apply_pre(root, print, "%d ");
    printf("\n");


  }

  f = fopen("tree.gv", "w");
  if(!f)
    printf("Can't open file\n");
  else
  {
    export_to_dot(f, "tree", root);
    fclose(f);
  }

  return 0;
}