#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode
{
	int key;
	int data;
}HashNode;

typedef struct Hash
{
	HashNode** array;
	int bucket;
	struct Hash* next;
}Hash;

HashNode* createNode(int bucket_num, int value)
{
	HashNode* newNode = malloc(sizeof(HashNode));
	newNode->key = bucket_num;
	newNode->data = value;

	return newNode;
}

Hash* createHashTable(int b, int s)
{

	if (s == 0)
		return NULL;

	Hash* newHash = malloc(sizeof(Hash));
	newHash->array = malloc(sizeof(HashNode*) * b);
	newHash->bucket = b;

	for (int i = 0; i < b; i++)
		newHash->array[i] = NULL;

	newHash->next = createHashTable(b, s - 1);
	return newHash;
}

int divisionHash(int bucket, int data)
{
	return data % bucket;
}

int insert(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i = H;
	while (i != NULL)
	{
		if (i->array[input_index] == NULL)
		{
			i->array[input_index] = createNode(input_index, value);
			return i->array[input_index] -> data;
		}
		i = i->next;
	}
	return -1;
}

int delete(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i = H;
	while (i != NULL)
	{
		if ((i->array[input_index] != NULL) && (i->array[input_index] -> data == value))
		{
			free(i->array[input_index]);
			i->array[input_index] = NULL;
			return 0;
		}
		i = i->next;
	}
	return -1;
}

int search(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i = H;
	while (i != NULL)
	{
		if ((i->array[input_index] != NULL) && (i->array[input_index]->data == value))
		{
			return i->array[input_index]->data;
		}
		i = i->next;
	}
	return -1;
}

void print(Hash* H)
{
	Hash* move;
	for (int i = 0; i < H -> bucket; i++)
	{
		move = H;;
		printf("key가 %d일때: ", i);
		while (move != NULL)
		{
			if (move->array[i] != NULL)
			{
				printf("%5d", move->array[i]->data);
			}
			else if ((move->array[i] == NULL))
			{
				printf("%5s", "NULL");
			}
			if (move->next != NULL)
				printf(" -> ");
			move = move->next;
		}
		printf("\n");
	}
}

int main()
{
	FILE* fp = fopen("C:\\Users\\user\\Downloads\\hash input.txt", "r");
	int b, s, input_data;
	Hash* head;

	fscanf(fp, "%d", &b);
	fscanf(fp, "%d", &s);
	head = createHashTable(b, s);

	fscanf(fp, "%d", &input_data);
	while (input_data != -1)
	{
		if(insert(head, input_data) == -1)
		{
			printf("%d오버플로우\n", input_data);
		}
		else
		{
			printf("%d입력성공\n", input_data);
		}
		fscanf(fp, "%d", &input_data);
	}
	print(head);

	if (delete(head, 211) == 0)
		printf("성공\n");
	else
		printf("실패\n");

	if (search(head, 211) == -1)
		printf("실패\n");
	else
		printf("성공\n");

	if (search(head, 22706) == -1)
		printf("실패\n");
	else
		printf("성공\n");
	print(head);


	return 0;
}