#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{ // 큐타입
 int front;
 int rear;
 int data;
 int capacity;
} QueueType;

// 오류함수
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

void enqueue(QueueType* q, intitem)
{
	if (is_full(q)) {
		error("큐가포화상태입니다.");
		return;
	}
	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("큐가공백상태입니다.");
		return -1;
	}
	intitem = q->data[++(q->front)];
	return item;
}

void queue_print(QueueType* q)
{
	for (inti = 0; i < MAX_QUEUE_SIZE; i++) 
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
	if (q->rear == MAX_QUEUE_SIZE - 1)
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
	QueueType* a;
	scanf("%d", &a->capacity);

	a->data = malloc(sizeof(int) * a->capacity);
	init_queue(a);
	printf("%d", a->front);

	return 0;
}