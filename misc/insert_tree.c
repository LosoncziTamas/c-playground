#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Node 
{    
    int data;
    struct Node *left;
    struct Node *right; 
} Node;

void PreOrder(Node *root) 
{
	if (root == NULL)
    {
      return;
    }
	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

Node* CreateNode(int data)
{
    Node* result = malloc(sizeof(Node));
    result->data = data;
    result->left = NULL;
    result->right = NULL;

    return result;
}

struct Node* Insert(Node* root, int data) 
{
    if (!root)
    {
        return CreateNode(data);
    }

	if (data < root->data)
    {
        Node* left = Insert(root->left, data);
        root->left = left;
    }
    else 
    {
        Node* right = Insert(root->right, data);
        root->right = right;
    }
    return root;
}

int main() {
  
    Node* root = NULL;

    root = Insert(root, 4);
    root = Insert(root, 3);
    root = Insert(root, 2);
    root = Insert(root, 1);
    
	PreOrder(root);

    return 0;
}
