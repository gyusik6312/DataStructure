#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct ListNode // 스택의노드를구조체로정의
{ 
	int data;
	struct ListNode* link;
} ListNode;

typedef struct Queue
{
	struct ListNode * front;
	struct ListNode* rear;
}Queue;

//큐생성
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

//스택이공백상태인지확인하는연산
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
	//리스트에아무것도없는경우체크해야함
	if (Q->rear != NULL)
		Q->rear->link = newNode;
	Q->rear = newNode;
	//최초노드삽입경우front위치조절
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

int map(int random) //0, 1, 2중 하나 반환
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

int check(Queue* q, int number) //지금 큐의 모든 데이터값이랑 매개변수랑 비교해서 만약 있으면 1로 반환
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

int counting(Queue* q) //현재 큐의 끝까지 돌면서 사이즈 체크후 사이즈 반환
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

void modify() //10개 이하 큐 만들기
{
	int r; //1~100랜덤값 할당
	int random; //맵핑에 이용
	int count = 0; //현재 q의 size할당
	int result; //중복 확인
	ListNode* i;
	Queue* q = createQueue();
	
	srand(time(NULL));
	while (count <= SIZE) //SIZE를 10으로 해놓고 10보다 크거나 같으면 실행
	{
		r = rand() % 100 + 1;
		result = check(q, r);
		random = map(r);
		if (random % 2 == 0) //짝수이면 enQueue
		{
			if (result == 0) //check가 1이 아니면 실행
			{
				enQueue(q, r);
				printQueue(q);
			}
			else //check에서 1이면 실행
			{
				printf("random: %d중복\n", r);
			}
		}
		else //홀수이면 deQueue
		{
			deQueue(q);
			printQueue(q);
		}
		count = counting(q); //현재 큐의 사이즈 확인
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