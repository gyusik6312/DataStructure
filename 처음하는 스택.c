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
		printf("������ȭ����\n");
		printf("capacity�ٽ� �Է��Ͻÿ�\n");

		return NULL; //���� ��ȭ�����̸� NULL�� �ٲ�
	}
	else
	{
		s->array[++s->top] = value;
	}
	return s;
}

ArrayStack* pop(ArrayStack* s)
{
	if (s == NULL) //���� s�� NULL�̸� ��� NULL��ȯ
	{
		return NULL;
	}

	if ((is_empty(s))) //���� ������� NULL�� �ٲ�
	{
		printf("���ð��鿡��\n");
		return NULL;
	}
	else
	{
		printf("����: %d\n", s->array[s->top--]); //����
	}
	return s;
}

void print(ArrayStack* s)
{
	if (s == NULL)
	{
		printf("array�� ���� NULL�̴�\n");
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
	printf("3������\n");
	head = push(head, 10);
	head = push(head, 20);
	head = push(head, 30);
	print(head);
	head = push(head, 40);
	head = push(head, 50);
	head = push(head, 60);
	print(head);

	printf("4������\n");
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