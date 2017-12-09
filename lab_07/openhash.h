//openhash
#ifndef __OPENHASH_H__
#define __OPENHAS_H__
void mapIterate(Hashmap *map, void(*f)(Entry*, void*), void* data);
void printEntry(Entry *e, void* data);
V get(Hashmap *map, V value);
Hashmap *get_open_hash(FILE *f);
#endif