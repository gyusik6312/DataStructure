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

AVLN* SingleRotateLeft(AVLN* X, int* count)
{
	if (X == NULL || X->left == NULL)
		return X;

	AVLN* W = X->left;
	X->left = W->right;
	W->right = X;
	X->height = select_max(Height(X->left), Height(X->right)) + 1;
	W->height = select_max(Height(W->left), Height(W->right)) + 1;

	//W->height = max(Height(W->left), X->height) + 1;
	printf("LL실행\n");
	(*count)++;
	return W; // new root node
}

AVLN* SingleRotateRight(AVLN* W, int* count)
{
	if (W == NULL || W->right == NULL)
		return W;

	AVLN* X = W->right;
	W->right = X->left;
	X->left = W;
	W->height = select_max(Height(W->left), Height(W->right)) + 1;
	X->height = select_max(Height(X->left), Height(X->right)) + 1;

	//X->height = max(Height(X->right), W->height) + 1;
	printf("RR실행\n");
	(*count)++;
	return X; // new root node;
}
AVLN* DoubleRotateLeftRight(AVLN* Z, int* count)
{
	printf("LR실행\n");
	Z->left = SingleRotateLeft(Z->left, count);
	return SingleRotateRight(Z, count);
}

AVLN* DoubleRotateRightLeft(AVLN* X, int* count)
{
	printf("RL실행\n");
	X->right = SingleRotateLeft(X->right, count);
	return SingleRotateRight(X, count);
}


AVLN* insert(AVLN* root, int data, int* count)
{
	if (!root)
	{
		root = (AVLN*)malloc(sizeof(AVLN));
		if (!root)
		{
			printf("Memory Error");
			return;
		}
		else
		{
			root->data = data;
			root->height = 0;
			root->left = root->right = NULL;
		}
	}
	else if (data < root->data)
	{
		root->left = insert(root->left, data, count);

		if (Height(root->left) - Height(root->right) == 2)
		{
			if (data < root->left->data)
				root = SingleRotateLeft(root, count);
			else
				root = DoubleRotateLeftRight(root, count);
		}
	}
	else if (data > root->data)
	{
		root->right = insert(root->right, data, count);
		if (Height(root->right) - Height(root->left) == 2)
		{
			if (data > root->right->data)
				root = SingleRotateRight(root, count);
			else
				root = DoubleRotateRightLeft(root, count);
		}
	}
	root->height = select_max(Height(root->left), Height(root->right)) + 1;
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
	srand(time(NULL));
	int count = 10 + rand() % 11;
	int input;
	int result = 0;
	AVLN* root = NULL;

	for (int i = 0; i < count; i++)
	{
		input = 1 + rand() % 100;
		root = insert(root, input, &result);
	}
	printf("전위 순회 출력: ");
	Inorder_iter(root);
	printf("회전 횟수: %d\n", result);

	return 0;
}