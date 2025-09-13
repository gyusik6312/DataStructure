#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{ // ťŸ��
	int front;
	int rear;
	int* data;
	int capacity;
} QueueType;

// �����Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q)
{
	q->rear = -1;
	q->front = -1;
}

void enqueue(QueueType* q, int item)
{
	if (is_full(q)) 
	{
		error("ť����ȭ�����Դϴ�.");
		return;
	}

	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q)
{
	if (is_empty(q)) 
	{
		error("ť����������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	for (int i = 0; i < q->capacity; i++) //����Ʈ
	{
		q->data[i] = q->data[i + 1];
	}
	q->rear--; //1���� �����ϱ� ���Ͽ� ����Ʈ�� �߱� ������ �ڿ��� -1�� ���־�� �������� ��ġ�� �߰� ����
	q->front--;  //front�� �տ��� ++�� �߱� ������ --�� �ؾ� �������� �ε��� ���� ��ġ
	return item;
}

void queue_print(QueueType* q)
{
	for (int i = 0; i < q->capacity; i++)
	{
		if (i <= q->front || i > q->rear)
			printf("   | ");
		else
			printf("%d | ", q->data[i]);
	}
	printf("\n");
}
int is_full(QueueType* q)
{

	if ((q->rear == q->capacity - 1))
		return 1;

	else
		return 0;
}

int is_empty(QueueType* q)
{
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

int main()
{
	QueueType* a = malloc(sizeof(QueueType));
	printf("ũ�� �Է�: ");
	scanf("%d", &a->capacity);
	a->data = malloc(sizeof(int) * a->capacity);
	init_queue(a);

	enqueue(a, 10);
	enqueue(a, 20);
	enqueue(a, 30);
	enqueue(a, 40);
	enqueue(a, 50);
	queue_print(a);

	int result = dequeue(a);
	printf("%d\n", result);
	queue_print(a);
	enqueue(a, 90);
	queue_print(a);

	return 0;
}