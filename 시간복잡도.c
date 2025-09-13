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
	struct node* remove = NULL; //삭제에 활용
	struct node* i = NULL; //반복문에서 사용(마지막 삭제의 경우 삭제에도 기여)
	struct node* temp = NULL; //마지막을 삭제할경우 마지막 노드 전의 노드를 가르킴

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
	time_t start, end; //시간 관련 연산 수행
	double result_array; // 시간 결과(array)
	double result_list; //시간 결과(list)
	int random_index; // 임의의 인덱스 
	int result; //get을 받는 변수
	double sum_array = 0; //array의 합을 받는 변수
	double sum_list = 0; //list의 합을 받는 변수
	int i; //반복문 사용

	test.capacity = 10000;
	test.array = malloc(sizeof(int) * test.capacity);
	test.count = 10000;
	 
	printf("Insert_last의 수행 시간\n");
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

	printf("arrayList시간: %lf\nLinkedList시간: %lf\n\n", result_array, result_list);
	
	printf("get으로 불러와서 데이터 더하는 수행 시간\n");
	srand(time(NULL));

	//array(get으로 받아서 sum에 더하기)
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

	//list(get으로 받아서 sum에 더하기)
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
	printf("arrayList시간: %lf\nLinkedList시간: %lf\n\n", result_array, result_list);

	printf("데이터 삭제 수행 시간\n");
	//array(삭제 수행 시간)
	start = clock();
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % test.count;
		delete_array(test, random_index);
	}
	end = clock();
	result_array = (double)end - start;

	//list(삭제 수행 시간)
	start = clock();
	for (i = 0; i < 1000; i++)
	{
		random_index = rand() % (10000 - i);
		delete_position(head, random_index);
	}
	end = clock();
	result_list = (double)end - start;
	printf("arrayList시간: %lf\nLinkedList시간: %lf\n\n", result_array, result_list);

	return 0;
}