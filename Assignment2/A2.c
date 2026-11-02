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
void clearStack(Stack* stack);

// Function prototype for queue
Queue* InitializeQueue(void);
bool isQueueEmpty(Queue* queue);
//QueueNode* CreateNewNode(char url);
void enqueue(Queue* queue, char* newUrl);
char* dequeue(Queue* queue);
char* peekQueue(Queue* queue);
void clearQueue(Queue* queue);

void DisplayMenu();
void ReadInputString(char* buffer, int size);
void visitNewWebPage(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl);
void navigateBack(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl);
void navigateForward(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl);
void displayCurrentPage(char* currentUrl);
void recordHistory(Queue* queue, char* url);
void displayHistoryLog(Queue* queue);

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
    // If it is empty, display error and return null
    if (isStackEmpty(stack)) 
    {
        printf("Stack is Empty");
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

// METHOD       : clearStack()
// DESCRIPTION  : Clears the stack by popping and freeing memory until the stack is empty
// RETURNS      : returns 0 or nothing because void
void clearStack(Stack* stack)
{
    // run until stack is empty
    while (!isStackEmpty(stack))
    {
        free(pop(stack));
    }
}

// METHOD       : InitializeQueue()
// DESCRIPTION  : Allocates memory for new empty queue, checks for memory allocation
//              : and sets queue front and rear pointer to NULL
// RETURNS      : Pointer to newly initialized queue
Queue* InitializeQueue(void) 
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

// From Week5_Queue example
/*QueueNode* CreateNewNode(char url)
{
    // allocating memory for node
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // copy data and initializing fields
    strncpy(newNode->url, url, URL_SIZE - 1);
    newNode->url[URL_SIZE - 1] = '\0'; // checks if string is NULL terminated
    newNode->next = NULL;
    return newNode;
}*/

// METHOD       : enqueue()
// DESCRIPTION  : Adds a new URL to the rear of the queue
// RETURNS      : returns 0 or nothing because void
void enqueue(Queue* queue, char* newUrl)
{
    // allocating memory for node
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));

    /* // From Week5_Queue example
    if (queue == NULL)
    {
        //queue = InitializeQueue();
    }
    
    QueueNode* toEnqueue = CreateNewNode(newUrl);
    */

    // safe check, if allocation fails or is out of memory, display error and exit
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // copy data and initializing fields
    strncpy(newNode->url, newUrl, URL_SIZE - 1);
    newNode->url[URL_SIZE - 1] = '\0'; // checks if string is NULL terminated
    // set pointer to the next node to NULL since this new node is being added to the rear/end of queue
    newNode->next = NULL; 
    
    // if queue is empty, the new node is both the first (front) and last (rear) items in the queue
    // and set both pointers to newNode
    if (isQueueEmpty(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        // connect the last rear node to the new node by updating next pointer
        queue->rear->next = newNode;
        // update the rear pointer so it points to the new node making it the end of the queue
        queue->rear = newNode;
    }
}

// METHOD       : dequeue()
// DESCRIPTION  : Removes and returns the URL from the front of the queue
// RETURNS      : char* string containing the dequeud URL or NULL if the queue is empty
char* dequeue(Queue* queue)
{
    // Calls isQueueEmpty() method to check if queue is empty
    // If it is empty, display error and return null
    if (isQueueEmpty(queue)) 
    {
        printf("Queue is Empty");
        return NULL;
    }

    // store a reference to the front node that is about to be removed
    QueueNode* nodeToDequeue = queue->front;

    // allocating memory for url
    char* dequeuedUrl = (char*)malloc(URL_SIZE * sizeof(char));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (dequeuedUrl == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(dequeuedUrl, nodeToDequeue->url, URL_SIZE);
    queue->front = nodeToDequeue->next;
    free(nodeToDequeue); // free node for memory
    return dequeuedUrl;
}

// METHOD       : peekQueue()
// DESCRIPTION  : Returns the URL from the front of the queue without removing it
// RETURNS      : char* pointer to the URL string at the front of the queue or NULL if the queue is empty
char* peekQueue(Queue* queue)
{
    // Calls isQueueEmpty() method to check if queue is empty
    // If it is empty, return null to exit function
    if (isQueueEmpty(queue))
    {
        return NULL;
    }
    return queue->front->url;
}

// METHOD       : clearQueue()
// DESCRIPTION  : Clears the stack by popping and freeing memory until the queue is empty
// RETURNS      : returns 0 or nothing because void
void clearQueue(Queue* queue) 
{
    while (!isQueueEmpty(queue)) 
    {
        free(dequeue(queue));
    }
    free(queue);
}

// METHOD       : visitNewWebpage()
// DESCRIPTION  : Asks user to enter a new URL
//              : Validates the new URL input from user to ensure its not empty or more than 50 chars long
//              : Saves current page to the back stack, clears forward stack and updates current active URL
// RETURNS      : returns 0 or nothing because void
void visitNewWebPage(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl)
{
    //char newUrl[URL_SIZE];
    
    // NOTE:
    // temporary substituting newUrl for a inputBuffer with a larger input Buffer to detect more than 50 chars
    // since fgets will not read more than the 49 chars + NULL terminator
    // so it will never display error for newUrl input from user that is more than 50 chars
    char inputBuffer[256];

    printf("\nEnter URL to visit (e.g., google.com): ");
    // safely read user input for new URL and makes sure that its not empty/NULL
    //ReadInputString(newUrl, URL_SIZE);
    ReadInputString(inputBuffer, sizeof(inputBuffer));
    // checks if newUrl input from user is empty
    //if (strlen(newUrl) == 0)
    if (strlen(inputBuffer) == 0)
    {
        printf("URL cannot be empty.\n");
        return;
    }
    // checks if newUrl input from user is too long (more than the allowable URL_SIZE: 50)
    //if (strlen(newUrl) >= URL_SIZE)
    if (strlen(inputBuffer) >= URL_SIZE)
    {
        printf("URL entered is too long. Max %d characters.\n", URL_SIZE - 1);
        return;
    }
    // if newUrl is valid length, copy it into newUrl
    char newUrl[URL_SIZE];
    strcpy(newUrl, inputBuffer);

    // if we are currently on a valid active url page, 
    // push it onto the top of the back stack before switching url pages so user can navigate back to it later
    if (strcmp(currentUrl, "") != 0)
    {
        push(backStack, currentUrl);
    }
    // clear the forwardStack so the user cannot navigate forward since they just visited a new page
    clearStack(forwardStack);
    // update the current page
    strncpy(currentUrl, newUrl, URL_SIZE);
    // update and record history
    recordHistory(historyQueue, currentUrl);

    printf("Currently Visiting: %s\n", currentUrl);
}

// METHOD       : navigateBack()
// DESCRIPTION  : Navigates back to previous web page url by popping the url from the back stack
//              : Pushes the current URL to the forward stack, and updates current URL
// RETURNS      : returns 0 or nothing because void
void navigateBack(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl)
{
    // checks if backStack is empty and displays error if it is empty
    if (isStackEmpty(backStack))
    {
        printf("No previous page to go back to.\n");
    }
    else
    {
        // push the current page to the forward stack since we are navigating back
        push(forwardStack, currentUrl);
        
        // Pop the previous page from the back stack
        char* prevUrl = pop(backStack);
        // update the current page
        strncpy(currentUrl, prevUrl, URL_SIZE);
        // free memory
        free(prevUrl);
        // update and record history queue order
        recordHistory(historyQueue, currentUrl);

        printf("\nNavigated back to: %s\n", currentUrl);
    }
}

// METHOD       : navigateForward()
// DESCRIPTION  : Navigates forward to next web page url by popping the url from the forward stack
//              : Pushes the current URL to the back stack, and updates current URL
// RETURNS      : returns 0 or nothing because void
void navigateForward(Stack* backStack, Stack* forwardStack, Queue* historyQueue, char* currentUrl)
{
    // checks if forwardStack is empty and displays error if it is empty
    if (isStackEmpty(forwardStack))
    {
        printf("No page to go forward to.\n");
    }
    else
    {
        // push the current page to the back stack since we are navigating forward
        push(backStack, currentUrl);

        // Pop the next page from the forward stack
        char* nextUrl = pop(forwardStack);
        // update the current page
        strncpy(currentUrl, nextUrl, URL_SIZE);
        // free memory
        free(nextUrl);
        // update and record history queue order
        recordHistory(historyQueue, currentUrl);

        printf("\nNavigated forward to: %s\n", currentUrl);
    }

}

// METHOD       : displayCurrentPage()
// DESCRIPTION  : Displays the currentUrl page (Will show None if there are no currentUrl pages)
// RETURNS      : returns 0 or nothing because void
void displayCurrentPage(char* currentUrl)
{
    printf("\nCurrent Web Page: %s\n", currentUrl);
}

// METHOD       : recordHistory()
// DESCRIPTION  : Records the url in the browsing history queue.
//              : If the url already exists in the queue, it is removed from its current position before being readded 
// RETURNS      : returns 0 or nothing because void
void recordHistory(Queue* queue, char* url)
{
    // set current to front node of the queue
    QueueNode* current = queue->front;
    QueueNode* prev = NULL;

    // will be used to track if url already exists in the queue/browsing history
    bool found = false; 

    // current is set to front so loop thru front to rear until the end is reached/NULL
    while (current != NULL) 
    {
        // checks if the current url matches a stored url node
        // if they match, return 0 and set found boolean to true
        if (strcmp(current->url, url) == 0) 
        {
            found = true; // found a matching url node
            break; // exit to if(found) below since a duplicate was found
        }
        prev = current;
        current = current->next;
    }
    // if a matching/duplicate url was found (true)
    if (found) 
    {
        // check if duplicate is at the front of the queue
        if (current == queue->front) 
        {
            // update queue front pointer to the next node removing the old
            queue->front = current->next;
            if (queue->front == NULL)
            {
                queue->rear = NULL;
            }
        }
        // else, the duplicate is found between the middle or rear of the queue
        else 
        {
            // bypass the current node by linking the previous node to the next current node
            prev->next = current->next;
            if (current == queue->rear) 
            {
                queue->rear = prev;
            }
        }
        free(current); // free memory
    }
    // Add the url at the back of the queue
    enqueue(queue, url);
}

// METHOD       : displayHistoryLog()
// DESCRIPTION  : Displays the browsing history stored in the queue
//              : If the queue is empty, will print that there is no browsing history message
// RETURNS      : returns 0 or nothing because void
void displayHistoryLog(Queue* queue)
{
    // set current to front node of the queue
    QueueNode* current = queue->front;

    // checks if queue is empty and displays error if it is empty
    if (isQueueEmpty(queue))
    {
        printf("\nNo browsing history.\n");
        return; // return to main menu
    }

    int i = 1; // counter for printed list of browsing history
    // loop thru each node in the queue until the end of the list is reached/NULL
    while (current != NULL) 
    {
        printf("%d. %s\n", i++, current->url);
        current = current->next;
    }
}

// METHOD       : ReadInputString()
// DESCRIPTION  : Reads user input and gets rid of trailing \n from fgets
//              : buffer will point to char array where text will be stored
//              : size is the maximum number of characters the buffer can hold
// RETURNS      : returns 0 or nothing because void
void ReadInputString(char* buffer, int size)
{
    // Note: basically the code from Assignment 1 copy pasted
    // read user input and ensures its valid or not empty
    if (fgets(buffer, size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }
    size_t length = strlen(buffer); // calculates the length of the string currently stored inside buffer and saves into length variable
    // checks if string is not empty and if the last character read is \n, if its true than replace the trailing \n with a \0
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
    else
    {
        // Clears out remaining characters inside stdin until it reachs a \n or end of file
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    // From GetString() example demo, gets rid of trailing \n from fgets
    //buffer[strcspn(buffer, "\n")] = '\0';

}

// METHOD       : DisplayMenu()
// DESCRIPTION  : Display Browser History Manager menu options to user
// RETURNS      : returns 0 or nothing because void
void DisplayMenu()
{
    printf("\n---- Browser History Manager ----\n");
    printf("1. Visit New Web Page\n");
    printf("2. Navigate Backward\n");
    printf("3. Navigate Forward\n");
    printf("4. Display Current Page\n");
    printf("5. Browsing History Log\n");
    printf("6. Exit\n");
    printf("Choice (1-6): ");
}

int main(void)
{
    Stack* backStack = InitializeStack();
    Stack* forwardStack = InitializeStack();
    Queue* historyQueue = InitializeQueue();

    int menuOption;
    char currentUrl[URL_SIZE] = "None";
    //char newUrl[URL_SIZE];

    // run while menuOption is not 6 (exit)
    do
    {
        DisplayMenu();
        scanf("%d", &menuOption); // get menu option input from user
        while (getchar() != '\n'); // clear input buffer

        switch (menuOption)
        {
        case 1:
            //printf("You have chosen to Visit a New Web Page\n");
            visitNewWebPage(backStack, forwardStack, historyQueue, currentUrl);
            break;
        case 2:
            //printf("You have chosen to Navigate Backwards\n");
            navigateBack(backStack, forwardStack, historyQueue, currentUrl);
            break;
        case 3:
            //printf("You have chosen to navigate Forward\n");
            navigateForward(backStack, forwardStack, historyQueue, currentUrl);
            break;
        case 4:
            //printf("You have chosen to Display Current Page\n");
            displayCurrentPage(currentUrl);
            break;
        case 5:
            //printf("You have chosen to Browse History Log\n");
            displayHistoryLog(historyQueue);
            break;
        case 6:
            printf("You have chosen to exit program\n");
            break;
        default:
            printf("Invalid choice! Please select an option between 1-6\n");
        }
    } while (menuOption != 6);

    return 0;
}