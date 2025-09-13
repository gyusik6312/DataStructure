#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* CreateNode(int data)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

TreeNode* make_tree(TreeNode* parent)
{
	int node_count = 2;
	int count;
	int array[100];
	int j = 0;

	TreeNode* newNode;
	TreeNode* i;

	for (j = 0; j < 100; j++)
		array[j] = 2;

	srand(time(NULL));
	while (node_count < 32)
	{
		newNode = CreateNode(1 + rand() % 100);
		count = node_count;
		i = parent;
		j = 0;

			while (count / 2 != 0)
			{
				array[j++] = count % 2;
				count /= 2;
			}

			for (int o = j - 1; o >= 1; o--)
			{
				if (array[o] == 0)
				{
					i = i->left;
				}
				else if (array[o] == 1)
				{
					i = i->right;
				}
				else
				{
					break;
				}
			}

			if (array[0] == 0)
			{
				i->left = newNode;
			}
			else if (array[0] == 1)
			{
				i->right = newNode;
			}
		node_count++;
	}
	return parent;
}

void print(TreeNode* parent)
{
	int node_count = 1;
	int count;
	int array[100];
	int j = 0;
	TreeNode* i;
	int tree_count = 0;

	for (j = 0; j < 100; j++)
		array[j] = 2;

	for (int node_count = 1; node_count <= 31; node_count++)
	{
		TreeNode* i = parent;
		int count = node_count;
		int j = 0;

		while (count / 2 != 0)
		{
			array[j++] = count % 2;
			count /= 2;
		}

		for (int o = j - 1; o >= 0; o--)
		{
			if (array[o] == 0) i = i->left;
			else i = i->right;
		}

		printf("노드 번호: %d / 데이터: %d\n", node_count, i->data);
	}
}



int main()
{
	TreeNode* root = CreateNode(1 + rand() % 100);
	root = make_tree(root);
	print(root);
	printf("노드5번 data: %d\n", root->left->right->data);
	return 0;
}