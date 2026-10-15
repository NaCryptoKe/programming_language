#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct Node
{
  char *data;
  struct Node *next;
} Node;

typedef struct Queue
{
  Node *front;
  Node *rear;
} Queue;

bool isEmpty(const Queue *queue);
void enqueue(Queue *queue, const char *data);
char *dequeue(Queue *queue);
void freeQueue(Queue *queue);

#endif
