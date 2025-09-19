#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

typedef struct TreeNode 
{
	int index;
	int data;
	int llink, rlink;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct stackNode
{
	TreeNode* Node_Data;
	struct stackNode* next;
}stackNode;


TreeNode* CreateNode(TreeNode* array[], int data, int index, int left, int right)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode -> left = NULL;
	newNode -> right = NULL;
	newNode -> data = data;
	newNode -> index = index;
	newNode->llink = left;
	newNode->rlink = right;
	array[newNode->index] = newNode;
	return newNode;
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

TreeNode* Preorder_iter_makeTree(TreeNode* root, TreeNode* son) //순회를 이용한 트리 만들기
{
	stackNode* top;
	TreeNode* store = root;
	int nodeCount = 0;
	int leafNode = 0;
	top = createStack();
	int level = 0;


	while (1) {
		while (root)
		{
			push(&top, root);
			root = root->left;
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		if (root->llink == son->index)
		{
			root->left = son;
		}
		else if (root->rlink == son->index)
		{
			root->right = son;
		}
		root = root->right;
	}
	deleteStack(&top);

	return store;
}

TreeNode*  MakeBinaryTree(TreeNode* parent, TreeNode* array[], int node_index, int data, int left, int right)
{
	TreeNode* newNode = CreateNode(array, data, node_index, left, right);
	if (parent != NULL)
	{
		parent = Preorder_iter_makeTree(parent, newNode);
	}
	array[newNode->index] = newNode;
	return parent;
}

int Preorder_iter_search(TreeNode* root, int number) //전위순회 활용한 root라는 트리의 노드의 각 인덱스에 number과 일치하는지 확인 
{
	stackNode* top;
	top = createStack();
	while (1) {
		while (root) 
		{
			push(&top, root);
			root = root->left;
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		if (root->index == number)
		{
			return 1;
		}
		root = root->right;
	}
	deleteStack(&top);
	return 0;
}

void Preorder_iter_print(TreeNode* root) //전위순회 출력
{
	stackNode* top;
	top = createStack();
	while (1) {
		while (root) {
			printf("%d  ", root->index);
			push(&top, root);
			root = root->left;
		}
		if (isEmptyStack(top))
			break;
		root = pop(&top);
		root = root->right;
	}
	printf("\n");
	deleteStack(&top);
}

void postorder_print(TreeNode* root) 
{
	stackNode* top;
	top = createStack();
	TreeNode* lastVisited = NULL;

	while (1)
	{
		while (root)
		{
			push(&top, root);
			root = root->left;
		}

		if (isEmptyStack(top))
			break;

		TreeNode* peekNode = top->Node_Data; 
		if (peekNode->right && lastVisited != peekNode->right)
		{
			root = peekNode->right;
		}
		else
		{
			if (peekNode->left || peekNode->right)
			{
				int sum = 0;
				if (peekNode->left) sum += peekNode->left->data;
				if (peekNode->right) sum += peekNode->right->data;
				peekNode->data = sum;
			}
			printf("%d(%d)  ", peekNode->index, peekNode->data);
			lastVisited = pop(&top);
		}
	}

	printf("\n");
	deleteStack(&top);
}


int main()
{
	int node_count;
	char cateforty;
	int node_index;
	int data;
	int left, right;
	int index_count;
	TreeNode* root;
	TreeNode* node_store[1001];

	printf("노드 전체 갯수: ");
	scanf("%d", &node_count);

	scanf("%d %c %d %d", &node_index, &cateforty, &data, &left); //루트 노드
	if (left != 0)
	{
		scanf("%d", &right);
	}
	else
	{
		right = 0;
	}

	root = CreateNode(node_store, data, node_index, left, right); //나머지
;	for (int i = 2; i <= node_count; i++)
	{
		scanf("%d %c %d %d", &node_index, &cateforty, &data, &left);
		if (left != 0)
		{
			scanf("%d", &right);
		}
		else
		{
			right = 0;
		}
		root = MakeBinaryTree(root, node_store, node_index, data, left, right);
	}
	for (int i = 1; i <= node_count; i++) //빠진 노드 없는 지 확인하고 빠졌으면 추가
	{
		if (!Preorder_iter_search(root, i))
		{
			TreeNode* n = node_store[i];
			root = MakeBinaryTree(root, node_store, n->index, n->data, n->llink, n->rlink);
		}
	}

	printf("전위순회: ");
	Preorder_iter_print(root);

	printf("후위순회: ");
	postorder_print(root);

	return 0;
}