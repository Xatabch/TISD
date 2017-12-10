//structs
#ifndef __MAIN_H__
#define __MAIN_H__
typedef struct tree_node tree;
struct tree_node
{
  int name;

  unsigned char height;//высота данного поддерева
  //меньшие
  struct tree_node *left;
  //большие
  struct tree_node *right;
  //родитель
  struct tree_node *parent;
};

typedef int V;
typedef int K;

typedef struct Entry
{
  V value;
  K key;
} Entry;

typedef struct Node//корзина
{
  Entry *value;
  struct Node *next;
} Node;

typedef struct Hashmap 
{
  Node **data;        //массив корзин
  size_t size;        //количество элементов в карте  
  size_t arr_size;    //размер массива корзин
  float loadFactor;   //процентное заполнение карты, при котором
                        //происходит пересборка карты
  int sravneniya; //максимальное количество сравнений в хеш-таблице
} Hashmap;

typedef struct Hasharray
{
  int *arr;//Массив для хранения элементов

  size_t size;//количество элементов в массиве
} Hasharray;
#endif