//pushpop
#ifndef __PUSHPOP_H__
#define __PUSHPOP_H__
struct colIndex* add_end(struct colIndex *head, struct colIndex *nk);
void push(struct colIndex **head, int data);
int pop(struct colIndex **head);
#endif