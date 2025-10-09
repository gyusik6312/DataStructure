#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct AVLTreeNode
{
	int data;
	struct AVLTreeNode* left;
	struct AVLTreeNode* right;
	int height;
} AVLN;

typedef struct stackNode
{
	AVLN* Node_Data;
	struct stackNode* next;
}stackNode;

int Height(AVLN* root)
{
	if (!root) return -1;
	else return root->height;
}

int select_max(int num1, int num2)
{
	if (num1 >= num2)
		return num1;
	else
		return num2;
}

AVLN* SingleRotateLeft(AVLN* X)
{
	int balance = Height(X->left) - Height(X->right);
	AVLN* W = X->left;
	X->left = W->right;
	W->right = X;
	X->height = select_max(Height(X->left), Height(X->right)) + 1;
	W->height = select_max(Height(W->left), Height(W->right)) + 1;

	//W->height = max(Height(W->left), X->height) + 1;
	printf("balanced가 깨지는 부분: %d, 차이: %d(LL)\n", X->data, balance);
	return W; // new root node
}

AVLN* SingleRotateRight(AVLN* W)
{
	int balance = Height(W->left) - Height(W->right);
	AVLN* X = W->right;
	W->right = X->left;
	X->left = W;
	W->height = select_max(Height(W->left), Height(W->right)) + 1;
	X->height = select_max(Height(X->left), Height(X->right)) + 1;

	//X->height = max(Height(X->right), W->height) + 1;
	printf("balanced가 깨지는 부분: %d, 차이: %d(LL)\n", W->data, balance);
	return X; // new root node;
}

AVLN* insert(AVLN* root, int data)
{
	if (root == NULL)
	{
		root = (AVLN*)malloc(sizeof(AVLN));
		if (root == NULL)
		{
			printf("Memory Error");
			return NULL;
		}
		else
		{
			root->data = data;
			root->left = root->right = NULL;
			root->height = 0;  // height 추가
		}
	}
	else
	{
		if (data < root->data)
			root->left = insert(root->left, data);
		else if (data > root->data)
			root->right = insert(root->right, data);
	}
	// 삽입 후 height 갱신
	root->height = select_max(Height(root->left), Height(root->right)) + 1;

	int balance = Height(root->left) - Height(root->right);

	// LL
	if (balance > 1 && data < root->left->data)
	{
		return SingleRotateLeft(root);
	}
	// RR
	if (balance < -1 && data > root->right->data)
	{
		return SingleRotateRight(root);
	}

	return root;
}

void push(stackNode** stack, AVLN* root)
{
	stackNode* newNode = malloc(sizeof(stackNode));
	newNode->Node_Data = root;
	newNode->next = *stack;
	*stack = newNode;
}

AVLN* pop(stackNode** stack)
{
	stackNode* temp;
	AVLN* store;

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

int isEmptyStack(stackNode* stack)
{
	if (stack == NULL)
	{
		return 1;
	}
	else
		return 0;
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

stackNode* createStack()
{
	return NULL;
}

void Inorder_iter(AVLN* root)
{
	stackNode* top;
	top = createStack();
	while (1) {
		while (root) {
			push(&top, root);
			root = root->left;
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		printf("%d  ", root->data);
		root = root->right;
	}
	printf("\n");
	deleteStack(&top);
}

int main()
{
	AVLN* root = NULL;

	root = insert(root, 7);
	root = insert(root, 5);
	root = insert(root, 3);
	root = insert(root, 9);
	root = insert(root, 11);
	root = insert(root, 15);

	Inorder_iter(root);

	return 0;
}