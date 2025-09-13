#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct arrayList
{
	int capacity;
	int size;
	int* array;
}arrayList;

void create(arrayList* head)
{
	printf("capacity�Է�: ");
	scanf("%d", &head->capacity);
	head->size = head -> capacity - 1;
	head->array = malloc(sizeof(int) * head->capacity);
}

void insert_last_2(arrayList* L, int index, int value, int* count)
{
	if (L->size >= L->capacity)
	{
		L->capacity *= 2;
		L->array = realloc(L->array, L->capacity * sizeof(int));
		(*count)++;
	}
	L->array[index] = value;
	L->size += 1;
}

void insert_last_1(arrayList* L, int index, int value, int* count)
{
	if (L->size >= L->capacity)
	{
		L->capacity += 1;
		L->array = realloc(L->array, L->capacity * sizeof(int));
		(*count)++;
	}
	L->array[index] = value;
	L->size += 1;
}

void print(arrayList* L)
{
	printf("capacity: %d\n", L->capacity);
	printf("size: %d\n", L->size);
	printf("\n\n");
}


int main()
{
	arrayList* head = malloc(sizeof(arrayList));
	arrayList* head2 = malloc(sizeof(arrayList));
	time_t start, end;
	int count = 0;
	int count2 = 0;
	double time_complex;
	double time_complex2;

	create(head);
	print(head);

	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		insert_last_2(head, i, i + 1, &count);
	}
	end = clock();
	time_complex = (double)(end - start) / CLOCKS_PER_SEC;
	print(head);
	printf("�ð�: %lf\n", time_complex);
	printf("Ȯ��Ƚ��: %d\n", count);
	printf("\n\n");

	printf("capacity�ϳ��� ����\n");
	create(head2);
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		insert_last_1(head2, i, i + 1, &count2);
	}
	end = clock();
	time_complex2 = (double)(end - start) / CLOCKS_PER_SEC;
	print(head2);
	printf("�ð�: %lf\n", time_complex2);
	printf("Ȯ��Ƚ��: %d\n", count2);

	return 0;
}