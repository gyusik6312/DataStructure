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
	ListNode* i = s; //반복문에서 사용
	ListNode* temp = NULL; //전에 주소 값 저장

	while (i != NULL)
	{
		ListNode* p = malloc(sizeof(ListNode)); //p에 새로운 동적메모리 생성 후 할당
		p->data = i->data; //p의 data에 현재 i의 data값 할당

		if (top == NULL) //만약 top == NULL이면 top에 p를 할당하여 처음 연결 리스트 주소값 할당 후 temp에 p의 값을 저장
		{
			top = p;
			temp = p;
			i = i->link;
		}
		else
		{
			temp->link = p; //temp가 전에것을 가르키고 있으니 temp의 link에 p에 할당한 새로운 동적메모리 저장
			if (i->link == NULL) //만약 i->link가 NULL이면 마지막을 가르키고 있는것 이기 때문에 새로운 동적메모리의 link에 NULL할당후 반복문 종료됨
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
				printf("original의 값과 주소값:  %d %p / deepcopy: %d %p\n", i->data, i, j->data, j);
			}
		}
		i = i->link;
		j = j->link;
	}
	printf("즉 data값은 같으나 새로운 메모리를 만들어서 할당함\n");
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
	printf("원래 original스택: ");
	display(top);

	deep_top = deep_copy(deep_top, top);
	printf("새로운 deeocopy스택: ");
	display(deep_top);

	check(top, deep_top);
	return 0;
}