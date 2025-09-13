#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodeList
{
	int data;
	struct nodeList* next;
}node;

node* insert_first(node* head, int data)
{
	node* p = (node*)malloc(sizeof(node));
	p->data = data;
	if (head == NULL)
	{
		head = p;
		p->next = p;
	}
	else 
	{
		p->next = head->next;
		head->next = p;
	}
	return head;
}

node* insert_last(node* head, int data)
{
	node* p = (node*)malloc(sizeof(node));
	p->data = data;
	if (head == NULL) { //����Ʈ�� ���Ұ� ���� ���
		head = p;
		p->next = head;
	}
	else {
		p->next = head->next;
		head->next = p;
		head = p;
	}
	return head;
}

node* delete_first(node* head)
{
	node* remove;
	if (head->next == head)
	{
		remove = head;
		free(remove);
		head = NULL;
		return head;
	}
	remove = head->next;
	head->next = remove->next;
	free(remove);

	return head;
}

node* delete_last(node* head)
{
	node* remove;
	node* i;

	i = head;

	if (head -> next == head)
	{
		remove = head;
		free(remove);
		head = NULL;
		return head;
	}

	else
	{
		while (i->next != head)
		{
			i = i->next;
		}

		i->next = head->next;
		remove = head;
		head = i;

		free(remove);
	}

	return head;
}

void print_list(node* head)
{
	node* i;

	if (head != NULL)
	{
		i = head->next;
		do
		{
			printf("%d ", i->data);
			i = i->next;
		} while (i != head->next);
		printf("\n");
	}

	else
	{
		printf("head�� NULL�Դϴ�.\n");
	}
	printf("\n");
}

void select_time(node* time_list, int n1, int n2)
{
	int k;
	node* i;

	i = time_list;
	for (k = 0; k < n1; k++)
	{
		i = i->next;
	}

	for (k = 0; k < n2; k++)
	{
		i = i->next;
	}
	printf("%d�� ����ð�,  %d�ô� ����ð����κ��� %d�ð� ���� �ð��̴�. ", n1, i->data, n2);
}

int main()
{
	node* head = NULL;
	node* time_list = NULL;
	int n1, n2;

	head = insert_first(head, 10);
	head = insert_first(head, 20);
	head = insert_first(head, 30);
	head = insert_last(head, 40);
	head = insert_last(head, 50);
	head = insert_last(head, 60);
	print_list(head);

	head = delete_first(head);
	head = delete_last(head);
	print_list(head);

	srand(time(NULL));
	n1 = rand() % 11 + 1;
	n2 = rand() % 49 + 1;
	for (int i = 1; i <= 12; i++)
	{
		time_list = insert_last(time_list, i);
	}
	printf("n1: %d n2: %d\n", n1, n2);
	select_time(time_list, n1, n2);

	return 0;
}