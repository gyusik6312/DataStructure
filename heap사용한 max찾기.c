#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int* array;
	int count; // 힙 안의 항목 개수
	int capacity; // 힙의 용량
	int heap_type; //힙의 종류
}Heap;

Heap* CreateHeap(int capacity, int heap_type)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	if (h == NULL)
	{
		printf("Memory Error");
		return;
	}
	h->heap_type = heap_type;
	h->count = 0;
	h->capacity = capacity;
	h->array = (int*)malloc(sizeof(int) * h->capacity);
	if (h->array == NULL)
	{
		printf("Memory Error");
		return;
	}
	return h;
}
	
int Parent(Heap * h, int i)
{
	if (i <= 0 || i >= h->count)
		return-1;
	return (i - 1) / 2;
}

int LeftChild(Heap* h, int i) {
	int left = 2 * i + 1;
	if (left >= h->count)
		return-1;
	return left;
}

int RightChild(Heap* h, int i) {
	int right = 2 * i + 2;
	if (right >= h->count)
		return-1;
	return right;
}

void PercolateUp(struct Heap* h, int i)
{
	int parents, max, temp;
	parents = Parent(h, i);
	if (parents != -1 && h->array[parents] < h->array[i])
		max = parents;
	else 
		max = i;

	if (max != i) 
	{
		temp = h->array[i];
		h->array[i] = h->array[max];
		h->array[max] = temp;
		PercolateUp(h, max);
	}
}

void PercolateDown(struct Heap* h, int i)
{
	int l, r, max, temp;
	l = LeftChild(h, i);
	r = RightChild(h, i);
	if (l != -1 && h->array[l] > h->array[i])
		max = l;
	else
		max = i;
	if (r != -1 && h->array[r] > h->array[max])
		max = r;
	if (max != i)
	{
		temp = h->array[i];
		h->array[i] = h->array[max];
		h->array[max] = temp;
		PercolateDown(h, max);
	}
}

void PercolateUpMin(struct Heap* h, int i)
{
	int parents, min, temp;
	parents = Parent(h, i);
	if (parents != -1 && h->array[parents] > h->array[i])
		min = parents;
	else
		min = i;

	if (min != i)
	{
		temp = h->array[i];
		h->array[i] = h->array[min];
		h->array[min] = temp;
		PercolateUpMin(h, min);
	}
}

void PercolateDownMin(struct Heap* h, int i)
{
	int l, r, min, temp;
	l = LeftChild(h, i);
	r = RightChild(h, i);
	if (l != -1 && h->array[l] < h->array[i])
		min = l;
	else
		min = i;
	if (r != -1 && h->array[r] < h->array[min])
		min = r;
	if (min != i)
	{
		temp = h->array[i];
		h->array[i] = h->array[min];
		h->array[min] = temp;
		PercolateDownMin(h, min);
	}
}

Heap* insert(Heap* root, int data)
{
	root->array[root->count] = data;
	root->count++;

	if (root->heap_type == 0)
	{
		PercolateUp(root, root->count - 1);
	}
	else
	{
		PercolateUpMin(root, root->count - 1);
	}
	return root;
}

int DeleteMax(Heap* h)
{
	int data;
	if (h->count == 0)
		return-1;
	data = h->array[0];
	h->array[0] = h->array[h->count - 1];
	h->count--;
	PercolateDown(h, 0);
	return data;
}

int compare(const void* a, const void* b)
{
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)
		return -1;
	else if (num1 > num2)
		return 1;
	else
		return 0;
}

void find(Heap* root, int k)
{
	if (root->count < k)
	{
		printf("none  ");
	}
	else
	{
		int* array = malloc(sizeof(int)*root->count);
		for (int i = 0; i < root->count; i++)
		{
			array[i] = root->array[i];
		}
		qsort(array, root->count, sizeof(int), compare);
		printf("%d  ", array[k-1]);

		free(array);
	}
}

int main()
{
	Heap* tree = NULL;
	int random;
	int k;
	int type;

	printf("몇번째 작은수를 구하시나요?: ");
	scanf("%d", &k);
	printf("타입이 무엇인가요?: ");
	scanf("%d", &type);

	tree = CreateHeap(10, type);

	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		random = 1 + rand() % 100;
		tree = insert(tree, random);
		for (int i = 0; i < tree->count; i++)
			printf("%d  ", tree->array[i]);
		printf("\n작은값: ");
		find(tree, k);
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < tree->count; i++)
		printf("%d  ", tree->array[i]);
	printf("\n");

	return 0;
}