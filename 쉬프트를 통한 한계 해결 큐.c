#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{ // 큐타입
	int front;
	int rear;
	int* data;
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

void enqueue(QueueType* q, int item)
{
	if (is_full(q)) 
	{
		error("큐가포화상태입니다.");
		return;
	}

	q->data[++(q->rear)] = item;
}

int dequeue(QueueType* q)
{
	if (is_empty(q)) 
	{
		error("큐가공백상태입니다.");
		return -1;
	}
	int item = q->data[++(q->front)];
	for (int i = 0; i < q->capacity; i++) //시프트
	{
		q->data[i] = q->data[i + 1];
	}
	q->rear--; //1개를 삭제하기 위하여 시프트를 했기 때문에 뒤에를 -1을 해주어야 정상적인 위치에 추가 가능
	q->front--;  //front를 앞에서 ++을 했기 때문에 --를 해야 정상적인 인덱스 값에 위치
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
	printf("크기 입력: ");
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