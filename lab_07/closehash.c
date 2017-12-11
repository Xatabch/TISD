#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "tick.h"//замер времени.

#define HASH(num,m) (num % m)

void put_close_hash(Hasharray **array,int num);
Hasharray *check_restruct(Hasharray *array,int *sravn,int *time);

Hasharray *rehash(Hasharray *array)
{ 
  Hasharray *newArr = malloc(sizeof(Hasharray));
  int oldsize = array->size;
  newArr->size = array->size + 2;
  newArr->arr = calloc(newArr->size,sizeof(int*));

  for(int i = 0; i < oldsize; i++)
  {
    if(array->arr[i] != 0)
      put_close_hash(&newArr,array->arr[i]);
  }

  return newArr;
}

void put_close_hash(Hasharray **array,int num)
{
  int i = 0;
  int index = HASH(num,(*array)->size);

  if(index < (*array)->size)
  {
    if((*array)->arr[index] == 0)
      (*array)->arr[index] = num;
    else
    {
      i = index;
      while((*array)->arr[i] != 0)
      {
        i++;
        if(i == (*array)->size)
          i = 0;
        if(i == index)
          break;
      }
      if(i != index)
        (*array)->arr[i] = num;

      if(i == index)
        (*array) = rehash((*array));
    }
  }
  else
    (*array) = rehash((*array));

}

int get_close(Hasharray *array,int num,int *sravneniya)
{
  int find = -10000000;
  int i;
  int index = HASH(num,array->size);
  *sravneniya = 0;

  if(array->arr[index] == num)
  {
    (*sravneniya) = (*sravneniya) + 1;
    find = array->arr[index];
  }
  else
  {
    i = index;
    while(array->arr[i] != num)
    {
      (*sravneniya) = (*sravneniya) + 1;
      i++;
      if(i == array->size)
        i = 0;
      if(i == index)
        break;
    }

    if(i != index)
      find = num;

  }

  return find;
}

Hasharray *get_close_hash(Hasharray *array,FILE *f, int *time, int *sravn)
{
  int num;
  array = malloc(sizeof(Hasharray));
  array->size = 0;

  if(fscanf(f,"%d",&num) == 1)
  {
    array->size++;
    while(fscanf(f,"%d",&num) == 1)
      array->size++;
  }
  fclose(f);
  array->size = (array->size * 1.2) + 1;

  array->arr = calloc(array->size , sizeof(int*));
  f = fopen("in.txt","r");
  if(!f)
    printf("Невозможно открыть файл\n");
  else
  {
    if(fscanf(f,"%d",&num) == 1)
    {
      put_close_hash(&array,num);
      while(fscanf(f,"%d",&num) == 1)
      {
        put_close_hash(&array,num);
      }
    }
  }

  (*time) = 0;
  (*sravn) = 0;

  array = check_restruct(array,sravn,time);
  (*time) = (*time) / array->size;
  (*sravn) = (*sravn) / array->size;

  return array;
}

Hasharray *check_restruct(Hasharray *array,int *sravn,int *time)
{ 
  float sred = 0;
  float count = 0;
  int sravneniya = 0;
  unsigned long long tb, te;

  for(int i = 0;i < array->size; i++)
  {
    if(array->arr[i] != 0)
    {
      count++;
      tb = tick();
      get_close(array,array->arr[i],&sravneniya);
      te = tick();
      (*time) = (*time) + (int)(te-tb);
      (*sravn) = (*sravn) + sravneniya;
      sred += sravneniya;
      sravneniya = 0;
    }
  }

  sred /= count;

  if(sred >= 4)
    array = rehash(array);
  
  return array;
}