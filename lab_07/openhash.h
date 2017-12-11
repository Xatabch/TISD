//openhash
#ifndef __OPENHASH_H__
#define __OPENHAS_H__
void mapIterate(Hashmap *map, void(*f)(Entry*, void*), void* data);
void printEntry(Entry *e, void* data);
V get_open(Hashmap *map, V value, int *sravneniya);
Hashmap *get_open_hash(FILE *f,int *size,int *time, int *sravn);
#endif