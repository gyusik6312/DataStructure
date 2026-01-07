#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Hash
{
	int key;
	int data;
	struct Hash* next;
}Hash;

Hash* createNode(int bucket_num)
{
	Hash* new_node = malloc(sizeof(Hash));
	new_node->next = NULL;
	new_node->key = bucket_num;
	new_node->data = -1;

	return new_node;
}

Hash* createHashTable(int b, int s)
{
	if (s < 1)
	{
		return NULL;
	}
	Hash* array = malloc(sizeof(Hash) * b);
	for (int i = 0; i < b; i++)
	{
		array[i].key = i;
		array[i].next = NULL;
		array[i].data = -1;
	}

	for (int i = 0; i < s - 1; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (array[j].next == NULL)
			{
				array[j].next = createNode(j);
			}
			else
			{
				Hash* i = &array[j];
				while (i->next != NULL)
				{
					i = i->next;
				}
				i->next = createNode(j);
			}
		}
	}
	
	return array;
}

int divisionHash(int data, int bucket)
{
	return data % bucket;
}

int insert(Hash* H, int value)
{
	int index = divisionHash(value, 10);
	
	Hash* i = &H[index];
	while (i != NULL)
	{
		if (i->data == -1)
		{
			i->data = value;
			printf("%d 정상삽입: ", value);
			return i->key;
		}
		else
		{
			i = i->next;
		}
	}

	printf("%d오버플로우\n", value);
	return -1;
}

int delete(Hash* H, int value)
{
	int index = divisionHash(value, 10);
	Hash* i = &H[index];
	while (i != NULL)
	{
		if (i->data == value)
		{
			printf("%d삭제\n", value);
			i->data = -1;
			return -1;
		}
		else
		{
			i = i->next;
		}
	}
	return -1;
}

int search(Hash* H, int value)  //검색한 데이터값 출력, 검색실패시 -1 출력
{
	int index = divisionHash(value, 10);
	Hash* i = &H[index];
	while (i != NULL)
	{
		if (i->data == value)
		{
			return i->data;
		}
		else
		{
			i = i->next;
		}
	}
	return -1;
}

void print(Hash* H)
{
	Hash* move;
	for (int i = 0; i < 10; i++)
	{
		move = &H[i];
		printf("key가 %d일때: ", i);
		while (move != NULL)
		{
			printf("%d", move->data);
			if (move->next != NULL)
				printf(" -> ");
			move = move->next;
		}
		printf("\n");
	}
}


int main()
{
	int bucket, slot;
	int data;
	int check_insert;
	FILE* fp = fopen("C:\\Users\\user\\Downloads\\hash input.txt", "r");
	fscanf(fp, "%d", &bucket);
	fscanf(fp, "%d", &slot);
	Hash* head = createHashTable(bucket, slot);

	fscanf(fp, "%d", &data);
	while (data != -1)
	{
		check_insert = insert(head, data);
		if (check_insert != -1)
		{
			printf("위치: %d\n", check_insert);
		}
		fscanf(fp, "%d", &data);
	}
	printf("\n");

	printf("삭제확인: %d\n", delete(head, 22706));
	printf("서치확인: %d\n", search(head, 22706));
	printf("서치확인: %d\n", search(head, 48394));
	printf("\n프린트 시작\n");
	print(head);
	insert(head, 1);

	return 0;
}