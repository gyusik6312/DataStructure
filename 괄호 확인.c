#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct ListNode
{
	char data;
	struct ListNode* link;
}ListNode;

ListNode* push(ListNode* s, char value)
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

void test(char* array)
{
	ListNode* p = NULL;
	int check = 1; //check�� �������� �����ϳ� ���ϳĸ� �����ϱ� ���� ���

	for (int i = 0; i < strlen(array); i++)
	{
		if ((array[i] == '(') || (array[i] == '{') || (array[i] == '[')) //���� ��ȣ�� ������ ���ÿ� push
		{
			p = push(p, array[i]);
		}

		else if ((p != NULL) && ((array[i] == ')') || (array[i] == '}') || (array[i] == ']'))) //���� ��ȣ�� ������ ���
		{
			if ((array[i] == ')') && (p->data == '(')) //���� ���������� ������ ���� ���߿� ���� ��ȣ�� string�� ������ ��ȣ�� ��Ī�̸� pop
			{
				p = pop(p);
			}
			else if ((array[i] == '}') && (p->data == '{'))
			{
				p = pop(p);
			}
			else if ((array[i] == ']') && (p->data == '['))
			{
				p = pop(p);
			}
			else //���� ���������� ������ ���� ���߿� ���� ��ȣ�� string�� ������ ��ȣ�� ��Ī�� �ƴϸ� ���԰��谡 �ƴ�(���� �� [�� }�� ��Ī�� �ƴϸ� ���԰��� �ƴ�)
			{
				printf("����: ���԰��谡 �ƴ�\n");
				check = 0;
				break;//������ �������� string�� ������ �� �ʿ���� ������ �ݺ��� ���� �� �Լ� ����
			}
		}
		else if ((p == NULL) && ((array[i] == ')') || (array[i] == '}') || (array[i] == ']'))) //()}�̷� ��� p�� ������ ���������� NULL������ ���ڿ��� �ݴ°� ������ �����ʾҴµ� ����
		{
			printf("����: ��ȣ�� ������ �ʾҴµ� ����\n");
			check = 0;
			break;
		}
	}

	if ((p == NULL) && (check == 1)) //���� �տ� ������ �� �۵��߰� p�� NULL�̸� ����ó��
	{
		printf("ó��good\n");
	}
	else if ((check == 1) && (p != NULL)) //�տ� ������ �� �۵������� �� ���� ����(()�̷������� �׷��� ����
	{
		printf("����: ��ȣ�� �� ���� ����\n");
	}
}

int main()
{
	char* array1 = "(a(b)";
	test(array1);
	char* array2 = "({a)}";
	test(array2);
	char* array3 = "a(b)c)";
	test(array3);
	char* array4 = "(a(b))";
	test(array4);

	return 0;
}