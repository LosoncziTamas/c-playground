#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define STACK_SIZE 100

typedef struct Stack 
{
    int data[STACK_SIZE];
    int top;
} Stack;

typedef struct Node 
{
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

Stack* CreateStack()
{
    Stack* stack = malloc(sizeof(Stack));
    stack->top = 0;

    return stack;
}

void PrintListBackward(Node* root)
{
    while(root)
    {
        printf("%d ", root->value);
        root = root->prev;
    }
    printf("\n");
}

Node* CreateListFromArray(int a[], int size)
{
    Node* head = NULL;
    Node* prev = NULL;

    for (int i = 0; i < size; ++i)
    {
        Node* node = malloc(sizeof(Node));
        node->value = a[i];
        node->next = NULL;
        node->prev = prev;
        if (prev)
        {
            prev->next = node;
        }
        else
        {
            head = node;
        }
        prev = node;
    }

    return head;
}

void PrintList(Node* root)
{
    while(root)
    {
        printf("%d ", root->value);
        root = root->next;
    }
    printf("\n");
}

void Push(Stack* stack, int value)
{
    if (stack->top < STACK_SIZE)
    {
        stack->data[stack->top++] = value;
    }
}

int Pop(Stack* stack)
{
    if (stack->top > 0)
    {
        return stack->data[--stack->top];
    }
    return -1;
}

bool IsEmpty(Stack* stack)
{
    return stack->top == 0;
}

Node* ReverseList(Node* root)
{
    if (!root) return NULL;

    Stack* stack = CreateStack();
    Push(stack, root->value);
    while(root->next)
    {
        root = root->next;
        Push(stack, root->value);
    }

    Node* head = root;
    Node* prev = NULL;
    while (!IsEmpty(stack))
    {
        root->value = Pop(stack);
        root->next = root->prev;
        root->prev = prev;

        root = root->next;
        prev = root;
    }

    return head;
}

int main() 
{
    int a1[] = {0, 1, 2, 3, 4, 5};
    int size = sizeof(a1) / sizeof(a1[0]);
    Node* list = CreateListFromArray(a1, size);
    PrintList(list);

    Stack* s = CreateStack();
    assert(IsEmpty(s));
    Push(s, 1);
    Push(s, 2);
    Push(s, 3);
    assert(Pop(s) == 3);
    assert(Pop(s) == 2);
    assert(Pop(s) == 1);
    assert(IsEmpty(s));

    list = ReverseList(list);
    PrintList(list);
}