#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode
{
	int data;
	struct ListNode* link;
}ListNode;

ListNode* push(ListNode* s, int value)
{
	ListNode* p = malloc(sizeof(ListNode));
	p->data = value;
	p->link = s;
	s = p;

	return s;
}

ListNode* pop(ListNode* s)
{
	ListNode* remove = s;
	s = s->link;
	free(remove);

	return s;
}

ListNode* deep_copy(ListNode* top, ListNode* s)
{
	ListNode* i = s; //�ݺ������� ���
	ListNode* temp = NULL; //���� �ּ� �� ����

	while (i != NULL)
	{
		ListNode* p = malloc(sizeof(ListNode)); //p�� ���ο� �����޸� ���� �� �Ҵ�
		p->data = i->data; //p�� data�� ���� i�� data�� �Ҵ�

		if (top == NULL) //���� top == NULL�̸� top�� p�� �Ҵ��Ͽ� ó�� ���� ����Ʈ �ּҰ� �Ҵ� �� temp�� p�� ���� ����
		{
			top = p;
			temp = p;
			i = i->link;
		}
		else
		{
			temp->link = p; //temp�� �������� ����Ű�� ������ temp�� link�� p�� �Ҵ��� ���ο� �����޸� ����
			if (i->link == NULL) //���� i->link�� NULL�̸� �������� ����Ű�� �ִ°� �̱� ������ ���ο� �����޸��� link�� NULL�Ҵ��� �ݺ��� �����
			{
				p->link = NULL;
			}
			temp = p;
			i = i->link;
		}
	}
	return top;
}

void display(ListNode* top)
{
	ListNode* i = top;
	while (i != NULL)
	{
		printf("%d ", i->data);
		i = i->link;
	}
	printf("\n");
}

void check(ListNode* p, ListNode* q)
{
	ListNode* i = p;
	ListNode* j = q;

	while ((i != NULL) && (j != NULL))
	{
		if (i->data == j->data)
		{
			if (i != j)
			{
				printf("original�� ���� �ּҰ�:  %d %p / deepcopy: %d %p\n", i->data, i, j->data, j);
			}
		}
		i = i->link;
		j = j->link;
	}
	printf("�� data���� ������ ���ο� �޸𸮸� ���� �Ҵ���\n");
}

int main()
{
	ListNode* top = NULL;
	ListNode* deep_top = NULL;
	top = push(top, 10);
	top = push(top, 20);
	top = push(top, 30);
	top = push(top, 40);
	top = push(top, 50);
	printf("���� original����: ");
	display(top);

	deep_top = deep_copy(deep_top, top);
	printf("���ο� deeocopy����: ");
	display(deep_top);

	check(top, deep_top);
	return 0;
}