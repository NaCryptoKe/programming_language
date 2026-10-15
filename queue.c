#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isEmpty(const Queue *queue)
{
  return queue->front == NULL;
}

void enqueue(Queue *queue, const char *data)
{
  Node *node = malloc(sizeof(*node));
  if (node == NULL)
  {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    return;
  }

  node->data = malloc(strlen(data) + 1);
  if (node->data == NULL)
  {
    fprintf(stderr, "Error: Memory allocation failed.\n");
    free(node);
    return;
  }
  strcpy(node->data, data);
  node->next = NULL;

  if (queue->rear == NULL)
    queue->front = node;
  else
    queue->rear->next = node;
  queue->rear = node;
}

char *dequeue(Queue *queue)
{
  if (isEmpty(queue))
    return NULL;

  Node *node = queue->front;
  char *data = node->data;
  queue->front = node->next;
  if (queue->front == NULL)
    queue->rear = NULL;
  free(node);
  return data;
}

void freeQueue(Queue *queue)
{
  char *data;
  while ((data = dequeue(queue)) != NULL)
    free(data);
}
