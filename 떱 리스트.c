#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* before; //���� ���� ����Ŵ
	struct node* after; //�ڿ� ���� ����Ŵ
}node;

node* insert_first(node* head, int value)
{
	node* p = malloc(sizeof(node));
	p->data = value;

	if (head == NULL) //ó������ �����Ͱ� �Ŀ� ���� ���� ������ �Ѵ� NULL�� �Ҵ���
	{
		p->before = NULL;
		p->after = NULL;
		head = p;
	}
	else
	{
		p->before = NULL;
		p->after = head;
		head->before = p;
		head = p;
	}

	return head;
}

node* insert_last(node* head, int value)
{
	node* p = malloc(sizeof(node));
	node* i;
	p->data = value;

	if (head == NULL) //ó������ �����Ͱ� �Ŀ� ���� ���� ������ �Ѵ� NULL�� �Ҵ���
	{
		p->before = NULL;
		p->after = NULL;
		head = p;
	}
	else
	{
		i = head;
		while (i->after != NULL)
		{
			i = i->after;
		}
		i->after = p;
		p->before = i;
		p->after = NULL;
	}

	return head;
}

node* delete_first(node* head)
{
	node* remove;

	if (head->after == NULL) //�ϳ� �������� �����ϴ� �Ϳ� ���� ���� ó��
	{
		remove = head;
		head = NULL;

		free(remove);
	}
	else
	{
		remove = head;
		head = head->after;
		head->before = NULL;

		free(remove);
	}
	return head;
}

node* delete_last(node* head)
{
	node* remove = NULL; //���� ���� ����
	node* temp = NULL; //�ڿ��� 2��°�� ����Ŵ ���� �ڿ����� �����ϰ� �� ���� ���� after�� NULL�� �Ҵ��ؾ��ϱ� ������
	node* i = NULL;

	if (head->after == NULL) //�ϳ� �������� �����ϴ� �Ϳ� ���� ���� ó��
	{
		remove = head;
		head = NULL;

		free(remove);
	}
	else
	{
		i = head;
		while (i->after != NULL)
		{
			temp = i;
			i = i->after;
		}
		remove = i;
		temp -> after = NULL;
		free(remove);
	}

	return head;
}

void print_forward(node* head)
{
	node* i;
	i = head;
	while (i != NULL)
	{
		printf("%d ", i->data);
		i = i->after;
	}
	printf("\n");
}

void print_backward(node* head)
{
	node* i;
	i = head;

	if (i != NULL)
	{
		while (i->after != NULL)
		{
			i = i->after;
		}
	}

	while (i != NULL)
	{
		printf("%d ", i->data);
		i = i->before;
	}
	printf("\n");
}

int main()
{
	node* head = NULL;
	head = insert_first(head, 10);
	head = insert_first(head, 20);
	head = insert_first(head, 30);
	head = insert_last(head, 40);
	head = insert_last(head, 50);
	head = insert_last(head, 60);

	head = delete_first(head);
	head = delete_last(head);
	head = delete_last(head);
	head = delete_last(head);
	head = delete_last(head);
	head = delete_last(head);

	print_forward(head);
	print_backward(head);

	return 0;
}