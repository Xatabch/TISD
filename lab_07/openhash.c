#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "tick.h"//замер времени.

#define CMP_EQ(a, b) (a == b)

Hashmap* rehashUp(Hashmap **_map_, Entry* e);

//Создание хеш-таблицы с открытой адресацией
Hashmap* createHashmap(int limit)
{
  Hashmap* tmp = (Hashmap*)malloc(sizeof(Hashmap));
  tmp->arr_size = limit;
  tmp->size = 0;
  tmp->sravneniya = 0;
  tmp->data = (Node**) calloc(tmp->arr_size, sizeof(Node*));

  return tmp;
}

//Обход открытой хеш таблицы
void mapIterate(Hashmap *map, void(*f)(Entry*, void*), void* data) 
{
    size_t size, i;
    size = map->arr_size;

    for (i = 0; i < size; i++) {
        Node *anchor = map->data[i];
        printf("\t\t\t%ld: ",i);
        while (anchor) 
        {
            f(anchor->value, data);
            anchor = anchor->next;
        }
        printf("\n");
    }
}

//Печать элементов хеш-таблицы
void printEntry(Entry *e, void* data) 
{
    printf("%d ", e->value);
}

//Поиск элемента в открытой хеш-таблице
V get_open(Hashmap *map, V value, int *sravneniya) 
{
     size_t index = (value % map->arr_size);
     V retVal = -100000000;
     (*sravneniya) = 0;
     if (map->data[index] != NULL) 
     {
         if (CMP_EQ(map->data[index]->value->value, value)) 
         {  
            (*sravneniya) = (*sravneniya) + 1;
            return map->data[index]->value->value;
         }
         else 
         {
            Node *anchor = map->data[index]->next;
            (*sravneniya) = (*sravneniya) + 1;
            while (anchor) 
            {
              (*sravneniya) = (*sravneniya) + 1;
              if (CMP_EQ(anchor->value->value, value)) 
              {
                retVal = anchor->value->value;
                break;
              }
              anchor = anchor->next;
            }
         }
     }
     return retVal;
}

//Добавление элемента в хеш-тблаицу с открытой адресацией
void raw_put(Hashmap **_map_,Entry *e)
{
  Hashmap *map = *_map_;
  int sravneniya = 0;
  int max = -1;
  size_t index = ((unsigned long long)e->value % map->arr_size);
  e->key = index;

  if(map->sravneniya < 4)
  {
    if(map->data[index] == NULL)
    {
      Node *newNode = (Node*)malloc(sizeof(Node));
      newNode->next = NULL;
      newNode->value = e;
      map->data[index] = newNode;
    }
    else
    {
      Node *anchor = map->data[index];
      Node *newNode = NULL;
      while(anchor->next)
      {
        sravneniya++;
        if(CMP_EQ((anchor->value)->value, e->value))
          exit(-5);
        anchor = anchor->next;
      }
      newNode = (Node*)malloc(sizeof(Node));
      newNode->next = NULL;
      newNode->value = e;
      anchor->next = newNode;
      sravneniya = sravneniya + 2;
      if(sravneniya > max)
        max = sravneniya;
      map->sravneniya = max;
    }
  }
  else
  {
      printf("Реструктуризирую хеш-таблицу\n");
     *_map_ = rehashUp(_map_,e);
  }

  (*_map_)->size++;
}

//Реструктуризация хеш-таблицы с открытой адресацией
Hashmap* rehashUp(Hashmap **_map_, Entry* e) 
{
    Hashmap *newMap = createHashmap((size_t)(*_map_)->arr_size + 1);
 
    size_t i, size;
    Hashmap *map = (*_map_);
    Node *anchor = NULL;
    Node *target = NULL;
 
    size = (*_map_)->arr_size;
    for (i = 0; i < size; i++) {
        anchor = map->data[i];
        //Вставляем Entry, чтобы не пересоздавать их лишний раз
        while (anchor) {
            target = anchor;
            anchor = anchor->next;
            raw_put(&newMap, target->value);
            free(target);
        }
        free(anchor);
    }
    //Удаляем старую карту, чтобы не было утечек
    free(map->data);
    free(*_map_);
    *_map_ = newMap;
    if(e)
      raw_put(&newMap, e);

    return newMap;
}

//Добавление элемента в хеш-таблицу с открытой адресацией
void put(Hashmap **_map_, V value)
{
  Entry *e = (Entry*)malloc(sizeof(Entry));
  e->value = value;
  raw_put(_map_, e);
}

void open_hash_time(Hashmap *map, int *time, int *sravn) 
{
    size_t size, i;
    int sravneniya = 0;
    unsigned long long tb, te;
    size = map->arr_size;
    int num = 0;

    for (i = 0; i < size; i++) {
        Node *anchor = map->data[i];
        while (anchor) 
        {
          num = anchor->value->value;
          tb = tick();
          get_open(map, num, &sravneniya);
          te = tick();
          (*time) = (*time) + (int)(te-tb);
          (*sravn) = (*sravn) + sravneniya;
          sravneniya = 0;
          anchor = anchor->next;
        }
    }
}

//Создание и заполнения из файла хеш-талицы с открытой адресацией
Hashmap *get_open_hash(FILE *f,int *size,int *time, int *sravn)
{
  int num;
  (*time) = 0;
  (*sravn) = 0;

  if(fscanf(f,"%d",&num) == 1)
  {
    (*size) = (*size) + 1;
    while(fscanf(f,"%d",&num) == 1)
      (*size) = (*size) + 1;
  }

  fclose(f);
  Hashmap *map = createHashmap(*size);
  f = fopen("in.txt","r");
  if(!f)
    printf("Невозможно открыть файл\n");
  else
  {
    if(fscanf(f,"%d",&num) == 1)
    {
      put(&map,num);
      while(fscanf(f,"%d",&num) == 1)
        put(&map,num);
    }
    if(map->sravneniya >=4)
      map = rehashUp(&map,NULL);
  }

  open_hash_time(map, time, sravn);
  (*time) = (*time) / (*size);
  (*sravn) = (*sravn) / (*size);

  
  return map;
}