//structs
#ifndef __MAIN_H__
#define __MAIN_H__
struct colIndex {
  int Nk; //номера компонент с которых начинается описание столбца

  struct colIndex *next;
};

struct cscMatrix {
  int N;  //размер матрицы (N x N)
  int NZ; //количество ненулевых элементов

  //Массив значений (размер NZ)
  double *Value;
  //Массив номеров строк (Размер NZ)
  int *Row;
  //Массив индексов столбцов (размер N + 1)
  struct colIndex *colindex;
};
#endif