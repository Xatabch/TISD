//structs
#ifndef __MAIN_H__
#define __MAIN_H__
typedef struct tree_node tree;
struct tree_node
{
  int name;//(4 байт)

  unsigned char height;//высота данного поддерева(1 байт)
  //меньшие
  struct tree_node *left;//(4 байт)
  //большие
  struct tree_node *right;//(4 байт)
  //родитель
  struct tree_node *parent;//(4 байт)
  //17 байт занимает данная структура
};

typedef int V;
typedef int K;

typedef struct Entry
{
  V value;//4 байт
  K key;//4 байт
  // 8 байт
} Entry;

typedef struct Node//корзина
{
  Entry *value;//4 байт
  struct Node *next;//4 байт
  //8 байт
} Node;

typedef struct Hashmap 
{
  Node **data;        //массив корзин(16 байт)
  int size;        //количество элементов в карте (4 байт) 
  int arr_size;    //размер массива корзин(4 байт)
  int sravneniya; //максимальное количество сравнений в хеш-таблице(4 байт)
  //28 байт
} Hashmap;

typedef struct Hasharray
{
  int *arr;//Массив для хранения элементов

  int size;//количество элементов в массиве(4 байт)
  // 4 + размер массива по 4 байта
} Hasharray;
#endif