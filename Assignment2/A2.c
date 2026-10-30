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


// Function prototype
void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peekStack(Stack* stack);
bool isStackEmpty(Stack* stack);

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

int main(void)
{

}