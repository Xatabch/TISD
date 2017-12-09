#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define HASH(num,m) (num % m)

void put_close_hash(int *arr,int num,int *size);
int *check_restruct(int *arr,int *size);

int *rehash(int *arr,int *size)
{ 
  int oldsize = *size;
  *size = *size + 2;
  int *newArr = calloc((*size),sizeof(int*));

  for(int i = 0; i < oldsize; i++)
  {
    if(arr[i] != 0)
    {
      put_close_hash(newArr,arr[i],size);
    }
  }

  return newArr;
}

void put_close_hash(int *arr,int num,int *size)
{
  int i = 0;
  int index = HASH(num,(*size));
  if(index < (*size))
  {
    if(arr[index] == 0)
      arr[index] = num;
    else
    {
      i = index;
      while(arr[i] != 0)
      {
        i++;
        if(i == (*size))
          i = 0;
        if(i == index)
          break;
      }
      if(i != index)
        arr[i] = num;

      if(i == index)
      {
        printf("Реструктурирую хеш-таблицу\n");
        arr = rehash(arr,size);
      }
    }
  }
  else
  {
    printf("Реструктурирую хеш-таблицу\n");
    arr = rehash(arr,size);
  }

}

int get_close(int *arr,int num, int *size,int *sravneniya)
{
  int find = -10000000;
  int i;
  int index = HASH(num,(*size));
  *sravneniya = 0;
  if(arr[index] == num)
  {
    (*sravneniya) = (*sravneniya) + 1;
    find = arr[index];
  }
  else
  {
    i = index;
    while(arr[i] != num)
    {
      (*sravneniya) = (*sravneniya) + 1;
      i++;
      if(i == (*size))
        i = 0;
      if(i == index)
        break;
    }

    if(i != index)
      find = num;

  }

  return find;
}

int *get_close_hash(int *arr,FILE *f,int *size)
{
  int num;

  if(fscanf(f,"%d",&num) == 1)
  {
    (*size) = (*size) + 1;
    while(fscanf(f,"%d",&num) == 1)
      (*size) = (*size) + 1;
  }
  fclose(f);
  (*size) = ((*size) * 1.2) + 1;

  arr = calloc((*size) , sizeof(int*));
  f = fopen("in.txt","r");
  if(!f)
    printf("Невозможно открыть файл\n");
  else
  {
    if(fscanf(f,"%d",&num) == 1)
    {
      put_close_hash(arr,num,size);
      while(fscanf(f,"%d",&num) == 1)
      {
        put_close_hash(arr,num,size);
      }
    }
  }

  printf("\nПроверка на необходимость реструктуризации хеш-таблицы с закрытой адресацией...\n");
  arr = check_restruct(arr,size);

  return arr;
}

int *check_restruct(int *arr,int *size)
{ 
  float sred = 0;
  float count = 0;
  int sravneniya = 0;
  for(int i = 0;i < (*size); i++)
  {
    if(arr[i] != 0)
    {
      count++;
      get_close(arr,arr[i],size,&sravneniya);
      sred += sravneniya;
    }
  }

  sred /= count;

  if(sred >= 4)
  {
    printf("Реструктурирую хеш-таблицу...\n");
    arr = rehash(arr,size);
  }
  else
    printf("Реструризация не требуется...\n");

  return arr;
}