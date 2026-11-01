/*
 * FILE         : A2
 * PROJECT      : Data Structures - Assignment 2
 * PROGRAMMER   : Kiet Ngo
 * FIRST VERSION: 2026-10-28
 * DESCRIPTION  :
 */

#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define URL_SIZE 50

typedef struct StackNode {
    char url[URL_SIZE];
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

typedef struct QueueNode {
    char url[URL_SIZE];
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front; // head pointer
    QueueNode* rear; // tail pointer
} Queue;

// Function prototype for stack
Stack* InitializeStack(void);
void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peekStack(Stack* stack);
bool isStackEmpty(Stack* stack);

// Function prototype for queue
Queue* InititalizeQueue(void);
bool isQueueEmpty(Queue* queue);

// METHOD       : push()
// DESCRIPTION  : Adds a new URL to the top of the stack
// RETURNS      : returns 0 or nothing because void
void push(Stack* stack, char* newUrl)
{
    // allocating memory for node
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));

    // safe check, if allocation fails or is out of memory, display error and exit
    if (newNode == NULL) {
        printf("No Memory!\n");
        exit(EXIT_FAILURE);
    }

    // copy data and initializing fields
    strncpy(newNode->url, newUrl, URL_SIZE - 1);
    newNode->url[URL_SIZE - 1] = '\0'; // checks if string is NULL terminated
    newNode->next = stack->top;
    stack->top = newNode;
}

// METHOD       : isStackEmpty
// DESCRIPTION  : Checks if the stack is empty
// RETURNS      : returns true if stack is empty, otherwise return false
bool isStackEmpty(Stack* stack)
{
    //return stack->top == -1;
    return stack->top == NULL;
}

// METHOD       : pop()
// DESCRIPTION  : Removes and returns the URL from the top stack
// RETURNS      : char* string containing the popped URL or NULL if the stack is empty
char* pop(Stack* stack)
{
    // Calls isStackEmpty() method to check if stack is empty
    // If it is empty, return null to exit function
    if (isStackEmpty(stack)) 
    {
        return NULL;
    }

    StackNode* node = stack->top;
    // allocating memory for url
    char* poppedUrl = (char*)malloc(URL_SIZE * sizeof(char));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (poppedUrl == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(poppedUrl, node->url, URL_SIZE);
    stack->top = node->next;
    free(node); // free node for memory
    return poppedUrl;
}

// METHOD       : peekStack()
// DESCRIPTION  : Returns the URL from the top of the stack without removing it
// RETURNS      : char* pointer to the URL string at the top of the stack or NULL if the stack is empty
char* peekStack(Stack* stack)
{
    // Calls isStackEmpty() method to check if stack is empty
    // If it is empty, return null to exit function
    if (isStackEmpty(stack))
    {
        return NULL;
    }
    return stack->top->url;
}

// METHOD       : InitializeStack()
// DESCRIPTION  : Allocates memory for new empty stack, checks for memory allocation
//              : and sets stack top pointer to NULL
// RETURNS      : Pointer to newly initialized stack
Stack* InitializeStack(void) 
{
    // allocating memory for node
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// METHOD       : InitializeQueue()
// DESCRIPTION  : Allocates memory for new empty queue, checks for memory allocation
//              : and sets queue front and rear pointer to NULL
// RETURNS      : Pointer to newly initialized queue
Queue* InititalizeQueue(void) 
{
    // allocating memory for node
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (queue == NULL) {
        printf("No Memory");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// METHOD       : isQueueEmpty
// DESCRIPTION  : Checks if the queue is empty
// RETURNS      : returns true if queue is empty, otherwise return false
bool isQueueEmpty(Queue* queue)
{
    return queue->front == NULL;
}

int main(void)
{
    Stack* backStack = InitializeStack();
    Stack* forwardStack = InitializeStack();
}