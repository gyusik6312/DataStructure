#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int top;
	int capacity;
	int* array;
}ArrayStack;

typedef struct
{
	int top;
	int capacity;
	int* array;
}ArrayStack;

ArrayStack* createStack()
{
	ArrayStack* s = malloc(sizeof(ArrayStack));

	if (!s)
	{
		return NULL;
	}
	else
	{
		printf("capacity: ");
		scanf("%d", &s->capacity);
		s->top = -1;
		s->array = malloc(sizeof(int) * s->capacity);
	}

	return s;
}

int is_empty(ArrayStack* s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

int is_full(ArrayStack* s)
{
	if (s->top == (s->capacity - 1))
		return 1;
	else
		return 0;
}


ArrayStack* push(ArrayStack* s, int value)
{
	if (is_full(s))
	{
		printf("스택포화에러\n");
		printf("capacity다시 입력하시오\n");

		return NULL; //만약 포화상태이면 NULL로 바꿈
	}
	else
	{
		s->array[++s->top] = value;
	}
	return s;
}

ArrayStack* pop(ArrayStack* s)
{
	if (s == NULL) //만약 s가 NULL이면 계속 NULL반환
	{
		return NULL;
	}

	if ((is_empty(s))) //만약 비었으면 NULL로 바꿈
	{
		printf("스택공백에러\n");
		return NULL;
	}
	else
	{
		printf("뺀값: %d\n", s->array[s->top--]); //뺀값
	}
	return s;
}

void print(ArrayStack* s)
{
	if (s == NULL)
	{
		printf("array는 현재 NULL이다\n");
	}
	else
	{
		for (int i = 0; i <= s->top; i++)
		{
			printf("%d ", s->array[i]);
		}
		printf("\n");
	}
}

int main()
{
	ArrayStack* head = NULL;
	ArrayStack* head2 = NULL;

	head = createStack();
	printf("3번실행\n");
	head = push(head, 10);
	head = push(head, 20);
	head = push(head, 30);
	print(head);
	head = push(head, 40);
	head = push(head, 50);
	head = push(head, 60);
	print(head);

	printf("4번실행\n");
	head2 = createStack();
	head2 = push(head2, 10);
	head2 = push(head2, 20);
	head2 = push(head2, 30);
	print(head2);
	head2 = pop(head2);
	head2 = pop(head2);
	head2 = pop(head2);
	head2 = pop(head2);
	head2 = pop(head2);
	head2 = pop(head2);
	print(head);

	return 0;
}