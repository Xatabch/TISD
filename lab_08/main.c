/*Цель работы: 
реализовать алгоритмы обработки графовых структур: 

Обработать графовую структуру в соответствии с указанным вариантом задания. 
Обосновать выбор необходимого алгоритма и выбор структуры для представления графов. 
Ввод данных – на усмотрение программиста. Результат выдать в графической форме.*/

/*Задан граф - не дерево. Проверить, можно ли превратить его в дерево удалением одной вершины вместе с ее ребрами.*/

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "allocmtr.h"
#include "getmatr.h"
#include "checktree.h"
#include "createdot.h"

#define EMPTY_FILE -1

int main(void)
{
  FILE *f;
	Graph *graph;
  int cant = 0;
  int check = 0;

  f = fopen("in.txt","r");
  if(!f)
    printf("Ошибка открытия файла\n");
  else
  {
    graph = get_matrix(f,allocate_matrix);
    if(!graph)
    {
      printf("Файл пуст, либо содержит недопустимые символы, проверьте файл.\n");
      exit(EMPTY_FILE);
    }
    cant = check_graph_for_tree(graph);
    check = check_or(graph);

    if(!cant && !check)
      printf("Можно\n");
    else
      printf("Нельзя\n");

    f = fopen("gr.gv", "w");

    if(!f)
    {
      printf("Ошибка открытия файла\n");
    }
    else
    {
      export_to_dot(f, "gr", graph);
      fclose(f);
    }
  }

	return 0;

}