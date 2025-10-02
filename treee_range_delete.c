#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BSTN
{
	int data;
	struct BSTN* left, * right;
} BSTN;

typedef struct stackNode
{
	BSTN* data;
	struct stackNode* next;
}stackNode;

BSTN* insert(BSTN* root, int data)
{
	if (root == NULL)
	{
		root = (BSTN*)malloc(sizeof(BSTN));
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

BSTN* FindMax(BSTN* root)
{
	BSTN* i = root;
	while (i->right != NULL)
	{
		i = i->right;
	}
	return i;
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

void push(stackNode** stack, BSTN* root)
{
	stackNode* newNode = malloc(sizeof(stackNode));
	newNode->data = root;
	newNode->next = *stack;
	*stack = newNode;
}

BSTN* pop(stackNode** stack)
{
	stackNode* temp;
	BSTN* store;

	if (isEmptyStack(*stack))
	{
		return NULL;
	}
	else
	{
		temp = *stack;
		store = temp->data;
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

int check_Inorder_iter(BSTN* root, int check_data)
{
	stackNode* top;
	int check = 1;
	top = createStack();
	while (1) {
		while (root) {
			push(&top, root);
			root = root->left;
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		if (root->data == check_data)
		{
			check = 0;
		}
		root = root->right;
	}
	deleteStack(&top);
	return check;
}

BSTN* delete(BSTN* root, int data, int* check)
{
	BSTN* temp;
	//data의위치검색
	if (root == NULL)
		printf("Element not there in tree\n");
	else if (data < root->data)
		root->left = delete(root->left, data, check);
	else if (data > root->data)
		root->right = delete(root->right, data, check);
	//data를찾은경우
	else 
	{
		//자식이2개인경우왼쪽서브트리의최대값과교체한다.
		if (root->left && root->right) 
		{
			temp = FindMax(root->left);
			root->data = temp->data;
			root->left = delete(root->left, root->data, check);
		}
		else { //자식이하나또는없는경우
			temp = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			free(temp);
		}
		*check = 0;
	}
	return root;
}

void Inorder_iter(BSTN* root)
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

BSTN* deleteOutOfRange(BSTN* root, int minRange, int maxRange)
{
	if (root == NULL) return NULL;

	int dummyCheck = 1;
	root->left = deleteOutOfRange(root->left, minRange, maxRange);
	root->right = deleteOutOfRange(root->right, minRange, maxRange);

	if (root->data < minRange || root->data > maxRange)
	{
		root = delete(root, root->data, &dummyCheck);
	}

	return root;
}

int main()
{
	BSTN* root = NULL;
	int random_count;
	int insert_random;
	int delete_random1 = 1 + rand() % 100;
	int delete_random2 = 1 + rand() % 100;
	int max = delete_random1 > delete_random2 ? delete_random1 : delete_random2;
	int min = delete_random1 > delete_random2 ? delete_random2 : delete_random1;
	
	srand(time(NULL));
	random_count = 1 + rand() % 20;
	printf("노드의 갯수: %d\n", random_count);
	for (int i = 0; i < random_count; i++)
	{
		insert_random = 1 + rand() % 100;
		if (check_Inorder_iter(root, insert_random))
		{
			root = insert(root, insert_random);
		}
		else
		{
			printf("%d중복\n", insert_random);
			i--;
		}
	}
	printf("트리 삭제 전(전위 순회출력): ");
	Inorder_iter(root);

	printf("범위 값: %d, %d\n", min, max);
	printf("트리삭제 후(전위 순회출력): ");
	root = deleteOutOfRange(root, min, max);
	Inorder_iter(root);

	return 0;
}