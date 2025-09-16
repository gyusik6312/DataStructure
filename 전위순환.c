#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

typedef struct TreeNode 
{
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct stackNode
{
	TreeNode* Node_Data;
	struct stackNode* next;
}stackNode;


TreeNode* CreateNode(int data)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

void MakeBinaryTree_left(TreeNode* parent, TreeNode* lson)
{
	parent->left = lson;
}

void MakeBinaryTree_right(TreeNode* parent, TreeNode* rson)
{
	parent->right = rson;
}

void MakeBinaryTree(TreeNode* parent, TreeNode* lson, TreeNode* rson)
{
	parent->left = lson;
	parent->right = rson;
}

stackNode* createStack()
{
	return NULL;
}

int isEmptyStack(stackNode* stack)
{
	if (stack == NULL)
	{
		return 1;
	}
	else
		return 0;
}

void push(stackNode** stack, TreeNode* root)
{
	stackNode* newNode = malloc(sizeof(stackNode));
	newNode->Node_Data = root;
	newNode->next = *stack;
	*stack = newNode;
}

TreeNode* pop(stackNode** stack)
{
	stackNode* temp;
	TreeNode* store;

	if (isEmptyStack(*stack))
	{
		return NULL;
	}
	else
	{
		temp = *stack;
		store = temp->Node_Data;
		*stack = (*stack)->next;
		free(temp);

		return store;
	}
}


void deleteStack(stackNode** temp)
{
    while (*temp != NULL)
    {
        stackNode* remove = *temp;
        *temp = (*temp)->next;
        free(remove);
    }
}

void Preorder_iter(TreeNode* root)
{
	stackNode* top;
	int nodeCount = 0;
	int leafNode = 0;
	top = createStack();
	int level = 0;

	while (1) {
		while (root) {
			printf("%d  ", root->data);
			push(&top, root);
			nodeCount++;
			root = root->left;
			if (root == NULL)
			{
				leafNode++;
			}
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		root = root->right;
	}
	printf("\n");
	deleteStack(&top);

	do
	{
		level++;
	} while (nodeCount > pow(2, level) - 1);

	printf("레벨: %d\n", level);
	printf("리프노드의 수: %d\n", leafNode);
}

int main()
{
	TreeNode* root = CreateNode(11);
	TreeNode* lson5 = CreateNode(5);
	TreeNode* rson10 = CreateNode(10);
	TreeNode* lson3 = CreateNode(3);
	TreeNode* rson4 = CreateNode(4);
	TreeNode* lson6 = CreateNode(6);
	TreeNode* rson9 = CreateNode(9);
	TreeNode* lson1 = CreateNode(1);
	TreeNode* rson2 = CreateNode(2);
	TreeNode* lson7 = CreateNode(7);
	TreeNode* rson8 = CreateNode(8);

	MakeBinaryTree(root, lson5, rson10);
	MakeBinaryTree(lson5, lson3, rson4);
	MakeBinaryTree(rson10, lson6, rson9);
	MakeBinaryTree(lson3, lson1, rson2);
	MakeBinaryTree(rson9, lson7, rson8);
	Preorder_iter(root);

	return 0;
}