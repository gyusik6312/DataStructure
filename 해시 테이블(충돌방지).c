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

typedef struct HashChainNode
{
	int key;
	int data;
	struct HashChainNode* next;
}HashChainNode;

typedef struct HashChain
{
	HashChainNode** array;
	int bucket;
}HashChain;

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

int insert_linear(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i;

	int count = input_index;
	do 
	{
		i = H;
		while (i != NULL)
		{
			if (i->array[count] == NULL)
			{
				i->array[count] = createNode(count, value);
				return i->array[count]->data;
			}
			i = i->next;
		}
		count++;
		if (count == H->bucket)
			count = 0;
	} while (count != input_index);

	return -1;
}

int delete_linear(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i;

	int count = input_index;
	do
	{
		i = H;
		while (i != NULL)
		{
			if ((i->array[count] != NULL) && (i->array[count]->data == value))
			{
				free(i->array[count]);
				i->array[count] = NULL;
				return 0;
			}
			i = i->next;
		}
		count++;
		if (count == H->bucket)
			count = 0;
	} while (count != input_index);

	return -1;
}

int search_linear(Hash* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	Hash* i;

	int count = input_index;
	do
	{
		i = H;
		while (i != NULL)
		{
			if ((i->array[count] != NULL) && (i->array[count]->data == value))
			{
				return i->array[count]->data;
			}
			i = i->next;
		}
		count++;
		if (count == H->bucket)
			count = 0;
	} while (count != input_index);

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

HashChain* createHashChain(int b)
{
	HashChain* newHash = malloc(sizeof(HashChain));
	newHash->array = malloc(sizeof(HashChainNode*) * b);
	newHash->bucket = b;
	for (int i = 0; i < b; i++)
		newHash->array[i] = NULL;

	return newHash;
}

HashChainNode* createChainNode(int bucket_num, int value)
{
	HashChainNode* newNode = malloc(sizeof(HashChainNode));
	newNode->key = bucket_num;
	newNode->data = value;
	newNode->next = NULL;

	return newNode;
}

int insert_chain(HashChain* H, int value)
{
	int input_index = divisionHash(H->bucket, value);


	if (H->array[input_index] == NULL)
	{
		H->array[input_index] = createChainNode(input_index, value);
		return H->array[input_index]->data;
	}
	else
	{
		HashChainNode* i = H->array[input_index];
		while (i->next != NULL)
		{
			i = i->next;
		}
		i->next = createChainNode(input_index, value);
		return i -> next ->data;
	}
}

int delete_chain(HashChain* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	HashChainNode* before = H->array[input_index];
	if (before == NULL)
	{
		return -1; // 삭제할 노드 없음
	}

	// 헤드 노드가 삭제 대상일 때
	if (before->data == value)
	{
		HashChainNode* remove = before;
		H->array[input_index] = before->next; // 헤드 이동
		free(remove);
		return 0;
	}

	HashChainNode* current = before->next;
	HashChainNode* after;

	while (current != NULL)
	{
		after = current->next;

		if (current->data == value)
		{
			before->next = after;
			free(current);
			return 0;
		}

		before = current;
		current = after;
	}
	return -1; // 값이 없을 때
}

int search_chain(HashChain* H, int value)
{
	int input_index = divisionHash(H->bucket, value);
	if (H->array[input_index] == NULL)
	{
		return -1;
	}
	else
	{
		HashChainNode* i = H->array[input_index];
		while (i != NULL)
		{
			if (i->data == value)
				return i->data;
			i = i->next;
		}
	}
	return -1;
}

void print_chain(HashChain* H)
{
	for (int i = 0; i < H->bucket; i++)
	{
		printf("key가 %d일때: ", i);
		HashChainNode* move = H->array[i];

		if (move == NULL)
		{
			printf("NULL\n");
			continue;
		}

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
	FILE* fp1 = fopen("C:\\Users\\user\\Downloads\\hash_input.txt", "r");
	FILE* fp2 = fopen("C:\\Users\\user\\Downloads\\hash_input.txt", "r");
	int b, s, input_data;
	int bC, sC;
	Hash* head;
	HashChain* headChain;

	fscanf(fp1, "%d", &b);
	fscanf(fp1, "%d", &s);
	head = createHashTable(b, s);

	fscanf(fp1, "%d", &input_data);
	while (input_data != -1)
	{
		if(insert_linear(head, input_data) == -1)
		{
			printf("%d오버플로우\n", input_data);
		}
		else
		{
			printf("%d입력성공\n", input_data);
		}
		fscanf(fp1, "%d", &input_data);
	}
	print(head);
	if (delete_linear(head, 10) == 0)
		printf("성공\n");
	else
		printf("실패\n");

	if (search_linear(head, 10) == -1)
		printf("실패\n");
	else
		printf("성공\n");

	if (search_linear(head, 17) == -1)
		printf("실패\n");
	else
		printf("성공\n");
	print(head);
	if (insert_linear(head, 1000) == -1)
	{
		printf("%d오버플로우\n", 1000);
	}
	else
	{
		printf("%d입력성공\n", 1000);
	}
	print(head);

	fscanf(fp2, "%d", &bC);
	fscanf(fp2, "%d", &sC);
	headChain = createHashChain(bC);
	fscanf(fp2, "%d", &input_data);
	while (input_data != -1)
	{
		printf("%d입력성공\n", insert_chain(headChain, input_data));
		fscanf(fp2, "%d", &input_data);
	}
	print_chain(headChain);
	if (delete_chain(headChain, 10) == 0)
		printf("성공\n");
	else
		printf("실패\n");
	if (search_chain(headChain, 10) == -1)
		printf("실패\n");
	else
		printf("성공\n");

	if (search_chain(headChain, 17) == -1)
		printf("실패\n");
	else
		printf("성공\n");
	printf("%d입력성공\n", insert_chain(headChain, 1000));
	print_chain(headChain);

	return 0;
}