#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int data;
	struct node* next;
}node;

typedef struct arrayList
{
	int capacity;
	int count;
	int* array;
}arrayList;

node* insert_last_list(node* head, int value)
{
	node* p = malloc(sizeof(node));
	node* i;
	p->data = value;

	if (head == NULL)
	{
		p->next = NULL;
		head = p;

		return head;
	}

	i = head;
	while (i->next != NULL)
	{
		i = i->next;
	}
	p->next = NULL;
	i->next = p;

	return head;
}

void* insert_last_array(arrayList a, int index, int value)
{
	a.array[index] = value;
}

int get_array(arrayList a, int index)
{
	return a.array[index];
}

int get_list(node* head, int index)
{
	int k = 0;
	node* i;

	i = head;
	while (i != NULL)
	{
		if (k == index)
		{
			return i->data;
		}
		i = i->next;
		k++;
	}
}

void delete_array(arrayList test, int index)
{
	int i;

	for (i = index; i < test.count; i++)
	{
		test.array[i] = test.array[i + 1];
	}
	test.count -= 1;

}

void delete_position(struct node* head, int index)
{
	int k = 1;
	struct node* remove = NULL; //������ Ȱ��
	struct node* i = NULL; //�ݺ������� ���(������ ������ ��� �������� �⿩)
	struct node* temp = NULL; //�������� �����Ұ�� ������ ��� ���� ��带 ����Ŵ

	if (index == 1)
	{
		remove = head;
		head = head->next;
		free(remove);
		return head;
	}

	i = head;
	while (i != NULL)
	{
		if (k == index)
		{
			remove = i->next;
			i->next = remove->next;
			free(remove);
			break;
		}
		else if (i->next == NULL)
		{
			temp->next = NULL;
			free(i);
			break;
		}
		k++;
		temp = i;
		i = i->next;
	}
}



int main()
{
	arrayList test; //array
	node* head = NULL; //linked list
	time_t start, end; //�ð� ���� ���� ����
	double result_array; // �ð� ���(array)
	double result_list; //�ð� ���(list)
	int random_index; // ������ �ε��� 
	int result; //get�� �޴� ����
	double sum_array = 0; //array�� ���� �޴� ����
	double sum_list = 0; //list�� ���� �޴� ����
	int i; //�ݺ��� ���

	test.capacity = 10000;
	test.array = malloc(sizeof(int) * test.capacity);
	test.count = 10000;
	 
	printf("Insert_last�� ���� �ð�\n");
	//insert_last_array
	start = clock();
	for (i = 0; i < 10000; i++)
	{
		insert_last_array(test, i, i);
	}
	end = clock();
	result_array = (double)end - start;

	//insert_last_list
	start = clock();
	for (i = 0; i < 10000; i++)
	{
		head = insert_last_list(head, i);
	}
	end = clock();
	result_list = (double)end - start;

	printf("arrayList�ð�: %lf\nLinkedList�ð�: %lf\n\n", result_array, result_list);
	
	printf("get���� �ҷ��ͼ� ������ ���ϴ� ���� �ð�\n");
	srand(time(NULL));

	//array(get���� �޾Ƽ� sum�� ���ϱ�)
	start = clock(); 
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % 10000;
		result = get_array(test, random_index);
		sum_array += (double)result;
	}
	end = clock();
	result_array = (double)end - start;
	printf("array: %lf\n", sum_array);

	//list(get���� �޾Ƽ� sum�� ���ϱ�)
	start = clock();
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % 10000;
		result = get_list(head, random_index);
		sum_list += (double)result;
	}
	end = clock();
	result_list = (double)end - start;
	printf("list: %lf\n", sum_list);
	printf("arrayList�ð�: %lf\nLinkedList�ð�: %lf\n\n", result_array, result_list);

	printf("������ ���� ���� �ð�\n");
	//array(���� ���� �ð�)
	start = clock();
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % test.count;
		delete_array(test, random_index);
	}
	end = clock();
	result_array = (double)end - start;

	//list(���� ���� �ð�)
	start = clock();
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % (10000 - i);
		delete_position(head, random_index);
	}
	end = clock();
	result_list = (double)end - start;
	printf("arrayList�ð�: %lf\nLinkedList�ð�: %lf\n\n", result_array, result_list);

	return 0;
}