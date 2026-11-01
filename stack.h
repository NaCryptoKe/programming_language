#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the stack wrapper structure
typedef struct {
    Node* top;
} Stack;

// Initialize the stack
void initStack(Stack* s) {
    s->top = NULL;
}

// Check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == NULL;
}

// Push an element onto the stack
void push(Stack* s, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Stack Overflow (Out of memory)\n");
        return;
    }
    newNode->data = val;
    newNode->next = s->top; // Link the new node to the current top
    s->top = newNode;       // Move top to point to the new node
}

// Pop an element from the stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1; // Error value
    }
    Node* temp = s->top;
    int poppedValue = temp->data;
    s->top = s->top->next; // Move top to the next node
    free(temp);            // Free the memory of the old top node
    return poppedValue;
}

// Peek at the top element without removing it
int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

// Free all memory used by the stack when done
void freeStack(Stack* s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int evaluatePostfix(const char* postfix) {
    IntStack s;
    initIntStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            pushInt(&s, c - '0'); // Convert char digit to integer
        } 
        else {
            int op2 = popInt(&s);
            int op1 = popInt(&s);

            switch (c) {
                case '+': pushInt(&s, op1 + op2); break;
                case '-': pushInt(&s, op1 - op2); break;
                case '*': pushInt(&s, op1 * op2); break;
                case '/': pushInt(&s, op1 / op2); break;
            }
        }
    }
    return popInt(&s);
}
#endif // STACK_H
