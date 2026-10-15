#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

bool isEmpty(Node *top)
{
  return top == NULL;
}

void push(Node **top_ptr, char *data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL)
  {
    printf("Error: Memory allocation failed. Stack Overflow!\n");
    return;
  }

  newNode->data = data;
  newNode -> next = *top_ptr;
  *top_ptr = newNode;
}

void pop(Node **top_ptr)
{
  if (isEmpty(*top_ptr))
  {
    printf("Error: Stack Underflow! The stack is empty.\n");
    return;
  }

  Node *temp = *top_ptr;

  *top_ptr = (*top_ptr)->next;
  free(temp);
}

void peek (Node *top)
{
  if (isEmpty(top))
  {
    printf("Stack is empty. Nothing to peek.\n");
    return;
  }
}

void freeStack(Node **top_ptr)
{
  while(!isEmpty(*top_ptr))
  {
    pop(top_ptr);
  }
}
