#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Node 
{    
    int data;
    struct Node *left;
    struct Node *right; 
};

void preOrder(struct Node *root) 
{
	if (root == NULL)
    {
      return;
    }
	printf("%d ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

struct Node* createNode(int data)
{
    struct Node* result = malloc(sizeof(struct Node));
    result->data = data;
    return result;
}

struct Node* insert(struct Node* root, int data) 
{
    if (!root)
    {
        root = createNode(data);
        return root;
    }

	if (data < root->data)
    {
        insert(root->left, data);
    }
    else 
    {
        insert(root->right, data);
    }
    return root;
}

int main() {
  
    struct Node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) 
    {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	preOrder(root);
    return 0;
}
