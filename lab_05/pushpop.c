#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct colIndex* add_end(struct colIndex *head, 
                                   struct colIndex *nk)
{
    struct colIndex *cur = head;

    if (!head)
        return nk;

    for ( ; cur->next; cur = cur->next)
        ;

    cur->next = nk;

    return head;
}

void push(struct colIndex **head, int data) {
  struct colIndex *tmp = malloc(sizeof(struct colIndex));
  tmp->Nk = data;
  tmp->next = (*head);
  (*head) = tmp;
}

int pop(struct colIndex **head) {
    struct colIndex* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->Nk;
    (*head) = (*head)->next;
    free(prev);
    return val;
}