#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct ListNode // �����ǳ�带����ü������
{ 
	int data;
	struct ListNode* link;
} ListNode;

typedef struct Queue
{
	struct ListNode * front;
	struct ListNode* rear;
}Queue;

//ť����
Queue* createQueue() 
{
	Queue* Q;
	ListNode* temp;
	Q = malloc(sizeof(Queue));
	if (!Q)
		return NULL;
	temp = malloc(sizeof(ListNode));
	Q->front = Q->rear = NULL;
	return Q;
}

//�����̰����������Ȯ���ϴ¿���
int isEmptyQueue(Queue* Q)
{
	return(Q->front == NULL);
}

void enQueue(Queue* Q, int data) 
{
	ListNode* newNode;
	newNode = malloc(sizeof(ListNode));
	if (!newNode)
		return NULL;
	newNode->data = data;
	newNode->link = NULL;
	//����Ʈ���ƹ��͵����°��üũ�ؾ���
	if (Q->rear != NULL)
		Q->rear->link = newNode;
	Q->rear = newNode;
	//���ʳ����԰��front��ġ����
	if (Q->front == NULL)
		Q->front = Q->rear;
}

int deQueue(Queue* Q) 
{
	int data = 0;
	ListNode* temp;
	if (isEmptyQueue(Q)) {
		printf("[QueueisEmpty]");
		return 0;
	}
	else {
		temp = Q->front;
		data = Q->front->data;
		Q->front = Q->front->link;
		if (Q->front == NULL)
			Q->rear = NULL;
		free(temp);
	}
	return data;
}
void deleteQueue(Queue* Q)
{
	ListNode* temp;
	while (Q->front) {
		temp = Q->front;
		Q->front = Q->front->link;
		free(temp);
	}
	free(Q);
}

int map(int random) //0, 1, 2�� �ϳ� ��ȯ
{
	return random % 3;
}

int printQueue(Queue* q)
{
	ListNode* i = q->front;
	while (i != q->rear)
	{
		printf("%d ", i->data);
		i = i->link;
	}
	printf("\n");
}

int check(Queue* q, int number) //���� ť�� ��� �����Ͱ��̶� �Ű������� ���ؼ� ���� ������ 1�� ��ȯ
{
	ListNode* i = q->front;
	int result = 0;
	while (i != q->rear)
	{
		if (i->data == number)
		{
			result = 1;
			break;
		}
		i = i->link;
	}
	return result;
}

int counting(Queue* q) //���� ť�� ������ ���鼭 ������ üũ�� ������ ��ȯ
{
	int count = 0;
	ListNode* i = q->front;

	while (i != NULL)
	{
		count++;
		i = i->link;
	}
	return count;
}

void modify() //10�� ���� ť �����
{
	int r; //1~100������ �Ҵ�
	int random; //���ο� �̿�
	int count = 0; //���� q�� size�Ҵ�
	int result; //�ߺ� Ȯ��
	ListNode* i;
	Queue* q = createQueue();
	
	srand(time(NULL));
	while (count <= SIZE) //SIZE�� 10���� �س��� 10���� ũ�ų� ������ ����
	{
		r = rand() % 100 + 1;
		result = check(q, r);
		random = map(r);
		if (random % 2 == 0) //¦���̸� enQueue
		{
			if (result == 0) //check�� 1�� �ƴϸ� ����
			{
				enQueue(q, r);
				printQueue(q);
			}
			else //check���� 1�̸� ����
			{
				printf("random: %d�ߺ�\n", r);
			}
		}
		else //Ȧ���̸� deQueue
		{
			deQueue(q);
			printQueue(q);
		}
		count = counting(q); //���� ť�� ������ Ȯ��
	}
}

int main()
{
	int r;
	srand(time(NULL));
	r = rand() % 100 + 1;
	modify();

	return 0;
}