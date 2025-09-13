#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int front, rear;
	int capacity;
	int* array;
} QueueType;

QueueType* Queue(int size) 
{
	QueueType* Q;
	Q = (QueueType*)malloc(sizeof(QueueType));
	if (!Q)
		return NULL;
	Q->capacity = size; // Queue 크기
	Q->front = Q->rear = -1; //front, rear 초깃값설정
	Q->array = malloc(Q->capacity * sizeof(int));
	if (!Q->array)
		return NULL;
	return Q;
}

// 원형 큐의 rear에 원소를 삽입하는 연산
void enQueue(QueueType* Q, int item) 
{
	if (isFull(Q)) 
	{
		printf(" Queue Overflow\n");
		exit(1);
	}
	else 
	{
		Q->rear = (Q->rear + 1) % Q->capacity;
		Q->array[Q->rear] = item;
		if (Q->front == -1)
			Q->front = Q->rear; // 첫 데이터의 경우 f=r=0 이되어야 함
	}
}

//원형 큐의 front에서 원소를 삭제하고 반환하는 연산
int deQueue(QueueType* Q) 
{
	int data = 0;
	if (isEmpty(Q)) 
	{
		printf(" Queue is empty\n");
		exit(1);
	}
	else 
	{
		data = Q->array[Q->front];
		if (Q->front == Q->rear)
			Q->front = Q->rear = -1;
		else
			Q->front = (Q->front + 1) % Q->capacity;
	}
	return data;
}

// 원형 큐가 공백 상태인지 검사하는 연산
int isEmpty(QueueType* Q)
{
	return((Q->front) == -1);
}

// 원형 큐가 포화 상태인지 검사하는 연산
int isFull(QueueType* Q) 
{
	return ((Q->rear + 1) % Q->capacity == Q->front);
}

//큐 삭제 연산
void deleteQueue(QueueType* Q) 
{
	if (Q)
	{
		if (Q->array)
			free(Q->array);
	}
	free(Q);
}

void queue_print(QueueType* q)
{
	if (check(q) == 1) //정방향일때
	{
		printf("정방향\n");
		for (int i = 0; i < q->capacity; i++) //차례대로 출력
		{
			if (i < q->front || i > q->rear)
				printf("   | ");
			else
				printf("%d | ", q->array[i]);
		}
		printf("\n\n");
	}

	else if (check(q) == 0) //역방향일때
	{
		printf("역방향\n");
		for (int i = q->front; i < q->capacity; i++) //front부터 끝까지 출력
		{
			printf("%d | ", q->array[i]);
		}
		for (int i = 0; i < q->front; i++) //0부터 front앞까지 출력
		{
			if (i <= q->rear)
			{
				printf("%d | ", q->array[i]);
			}
			else
			{
				printf("   | ");
			}
		}
		printf("\n\n");
	}
}

int check(QueueType* q) //정방향인지 역방향인지 확인
{
	if (q->rear > q->front) //정방향
	{
		return 1;
	}
	else if (q->rear < q->front) //역방향
	{
		return 0;
	}
	else //나머지
	{
		return -1;
	}
}

void modify(QueueType* q)
{
	if (check(q) == 1) //정방향일때 ---> 수정X
	{
		printf("정방향 ---> 수정없음\n");
	}
	else if (check(q) == 0) //역방향 일때 copy라는 변수에 재정렬을 해서 할당 후 그값을 다시 원래의 q->array에 할당
	{
		printf("역방향 ---> 수정\n");
		int* copy = malloc(sizeof(int) * q->capacity);
		int j = 0; //copy배열에 접근

		for (int i = q->front; i < q->capacity; i++) //front부터 끝까지 먼저 저장
		{
			copy[j] = q->array[i];
			j++;
		}

		for (int i = 0; i < q->front; i++) //0부터 front앞까지 저장
		{
			copy[j] = q->array[i];
			j++; 
		}
		for (int i = 0; i < q->capacity; i++) //q->array에 copy저장
		{
			q->array[i] = copy[i];
		}
		q->rear = 4; //재정렬 했으니 front와 rear값 바뀌어야 함
		q->front = 0;
	}
}

int main()
{
	QueueType* a = Queue(5);
	int result;

	enQueue(a, 10);
	enQueue(a, 20);
	enQueue(a, 30);
	queue_print(a);

	result = deQueue(a);
	printf("나온값: %d\n", result);
	queue_print(a);
	result = deQueue(a);
	printf("나온값: %d\n", result);
	queue_print(a);

	enQueue(a, 40);
	queue_print(a);
	enQueue(a, 50);
	queue_print(a);
	enQueue(a, 60);
	queue_print(a);
	enQueue(a, 70);
	queue_print(a);

	modify(a);
	queue_print(a);

	result = deQueue(a);
	printf("나온값: %d\n", result);
	queue_print(a);

	return 0;
}