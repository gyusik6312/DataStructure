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
	Q->capacity = size; // Queue ũ��
	Q->front = Q->rear = -1; //front, rear �ʱ갪����
	Q->array = malloc(Q->capacity * sizeof(int));
	if (!Q->array)
		return NULL;
	return Q;
}

// ���� ť�� rear�� ���Ҹ� �����ϴ� ����
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
			Q->front = Q->rear; // ù �������� ��� f=r=0 �̵Ǿ�� ��
	}
}

//���� ť�� front���� ���Ҹ� �����ϰ� ��ȯ�ϴ� ����
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

// ���� ť�� ���� �������� �˻��ϴ� ����
int isEmpty(QueueType* Q)
{
	return((Q->front) == -1);
}

// ���� ť�� ��ȭ �������� �˻��ϴ� ����
int isFull(QueueType* Q) 
{
	return ((Q->rear + 1) % Q->capacity == Q->front);
}

//ť ���� ����
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
	if (check(q) == 1) //�������϶�
	{
		printf("������\n");
		for (int i = 0; i < q->capacity; i++) //���ʴ�� ���
		{
			if (i < q->front || i > q->rear)
				printf("   | ");
			else
				printf("%d | ", q->array[i]);
		}
		printf("\n\n");
	}

	else if (check(q) == 0) //�������϶�
	{
		printf("������\n");
		for (int i = q->front; i < q->capacity; i++) //front���� ������ ���
		{
			printf("%d | ", q->array[i]);
		}
		for (int i = 0; i < q->front; i++) //0���� front�ձ��� ���
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

int check(QueueType* q) //���������� ���������� Ȯ��
{
	if (q->rear > q->front) //������
	{
		return 1;
	}
	else if (q->rear < q->front) //������
	{
		return 0;
	}
	else //������
	{
		return -1;
	}
}

void modify(QueueType* q)
{
	if (check(q) == 1) //�������϶� ---> ����X
	{
		printf("������ ---> ��������\n");
	}
	else if (check(q) == 0) //������ �϶� copy��� ������ �������� �ؼ� �Ҵ� �� �װ��� �ٽ� ������ q->array�� �Ҵ�
	{
		printf("������ ---> ����\n");
		int* copy = malloc(sizeof(int) * q->capacity);
		int j = 0; //copy�迭�� ����

		for (int i = q->front; i < q->capacity; i++) //front���� ������ ���� ����
		{
			copy[j] = q->array[i];
			j++;
		}

		for (int i = 0; i < q->front; i++) //0���� front�ձ��� ����
		{
			copy[j] = q->array[i];
			j++; 
		}
		for (int i = 0; i < q->capacity; i++) //q->array�� copy����
		{
			q->array[i] = copy[i];
		}
		q->rear = 4; //������ ������ front�� rear�� �ٲ��� ��
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
	printf("���°�: %d\n", result);
	queue_print(a);
	result = deQueue(a);
	printf("���°�: %d\n", result);
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
	printf("���°�: %d\n", result);
	queue_print(a);

	return 0;
}