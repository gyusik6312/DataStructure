#include <stdio.h>
#include <stdlib.h>

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

typedef struct queueNode
{
	TreeNode* Node_Data;
	struct queueNode* next;
}queueNode;

stackNode* createStack()
{
	return NULL;
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

int isEmptyStack(stackNode* stack)
{
	if (stack == NULL)
	{
		return 1;
	}
	else
		return 0;
}

int isEmptyQueue(queueNode* ｑｕｅｕｅ)
{
	if (ｑｕｅｕｅ == NULL)
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

TreeNode* insert(TreeNode* root, int data)
{
	if (root == NULL)
	{
		root = (TreeNode*)malloc(sizeof(TreeNode));
		if (root == NULL)
		{
			printf("Memory Error");
			return;
		}
		else
		{
			root->data = data;
			root->left = root->right = NULL;
		}
	}
	else
	{
		if (data < root->data)
			root->left = insert(root->left, data);
		else if (data > root->data)
			root->right = insert(root->right, data);

	}
	return root;
}

TreeNode* randomTree_BST(int count)
{
	int random;
	TreeNode* root = NULL;
	srand(time(NULL));
	printf("생성된 random값: ");
	for (int i = 0; i < 7; i++)
	{
		random = 1 + rand() % 100;
		printf("%d  ", random);
		root = insert(root, random);
	}
	printf("\n");
	return root;
}

void Inorder_iter(TreeNode* root)
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
	deleteStack(&top);
}

queueNode* enqueue(queueNode* top, TreeNode* root)
{
	queueNode* newNode = malloc(sizeof(queueNode));
	queueNode* i;

	newNode->Node_Data = root;
	newNode->next = NULL;

	if (top == NULL)
	{
		top = newNode;
	}
	else
	{
		i = top;
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = newNode;
	}
	return top;
}

TreeNode* dequeue(queueNode** top)
{
	TreeNode* store;
	queueNode* remove;
	if (top == NULL)
	{
		return NULL;
	}
	else
	{
		store = (*top) -> Node_Data;
		remove = *top;
		*top = (*top)->next;
		free(remove);

		return store;
	}
}

void level_print(TreeNode* root)
{
	if (root == NULL)
		return;

	queueNode* q = NULL;
	q = enqueue(q, root);

	while (!isEmptyQueue(q))
	{
		TreeNode* node = dequeue(&q);
		printf("%d ", node->data);

		if (node->left) 
			q = enqueue(q, node->left);
		if (node->right) 
			q = enqueue(q, node->right);
	}
}

TreeNode* new_insert(TreeNode* root, int data)
{
	if (root == NULL)
	{
		root = (TreeNode*)malloc(sizeof(TreeNode));
		if (root == NULL)
		{
			printf("Memory Error");
			return;
		}
		else
		{
			root->data = data;
			root->left = root->right = NULL;
		}
	}
	else
	{
		if (data < root->data)
		{
			printf("%d  ", root->data);
			root->left = new_insert(root->left, data);
		}
		else if (data > root->data)
		{
			printf("%d  ", root->data);
			root->right = new_insert(root->right, data);
		}
	}
	return root;
}

int main()
{
	int random;
	TreeNode* root;

	srand(time(NULL));
	random = 1 + rand() % 20;
	root = randomTree_BST(random);

	printf("중위 순회: ");
	Inorder_iter(root);
	printf("\n");
	printf("레벨 순회: ");
	level_print(root);
	printf("\n");

	random = 1 + rand() % 100;
	printf("삽입: %d\n", random);
	root = new_insert(root, random);
	printf("%d", random);

	return 0;
}