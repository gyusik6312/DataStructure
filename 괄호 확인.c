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
	int check = 1; //check는 마지막을 실행하냐 안하냐를 구별하기 위해 사용

	for (int i = 0; i < strlen(array); i++)
	{
		if ((array[i] == '(') || (array[i] == '{') || (array[i] == '[')) //만약 괄호가 열리면 스택에 push
		{
			p = push(p, array[i]);
		}

		else if ((p != NULL) && ((array[i] == ')') || (array[i] == '}') || (array[i] == ']'))) //만약 괄호가 닫히는 경우
		{
			if ((array[i] == ')') && (p->data == '(')) //만약 정상적으로 스택의 가장 나중에 들어온 괄호와 string의 닫히는 괄호가 대칭이면 pop
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
			else //만약 정상적으로 스택의 가장 나중에 들어온 괄호와 string의 닫히는 괄호가 대칭이 아니면 포함관계가 아님(예를 들어서 [와 }는 대칭이 아니며 포함관계 아님)
			{
				printf("오류: 포함관계가 아님\n");
				check = 0;
				break;//오류가 나왔으니 string을 끝까지 갈 필요없기 때문에 반복문 종료 후 함수 종류
			}
		}
		else if ((p == NULL) && ((array[i] == ')') || (array[i] == '}') || (array[i] == ']'))) //()}이런 경우 p는 스택은 정상적으로 NULL이지만 문자열은 닫는게 남으면 열지않았는데 닫음
		{
			printf("오류: 괄호를 열지도 않았는데 닫음\n");
			check = 0;
			break;
		}
	}

	if ((p == NULL) && (check == 1)) //만약 앞에 모든것이 잘 작동했고 p가 NULL이면 정상처리
	{
		printf("처리good\n");
	}
	else if ((check == 1) && (p != NULL)) //앞에 모든것이 잘 작동했지만 페어가 맞지 않음(()이런식으로 그러면 오류
	{
		printf("오류: 괄호의 페어가 맞지 않음\n");
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