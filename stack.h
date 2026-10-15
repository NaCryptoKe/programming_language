#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Node
{
  char *data;
  struct Node *next;
} Node;

bool isEmpty(Node *top);

void push(Node **top_ptr, char *data);
void pop(Node **top_ptr);
void peek(Node *top);
void freeStack(Node **top_ptr);

#endif // !STACH_H
