#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct ArrayList
{
	int capacity; //리스트의 사이즈
	int number; //현재 데이터 갯수
	int* array;
};

void insert_first(int array[], int size)
{
	int i; //반복문 관련 배열
	int j; //반복문 관련 배열
	int input; //입력 관련 배열

	for (i = 0; i < 5; i++)
	{
		printf("입력값: ");
		scanf("%d", &input);


		for (j = i; j >= 1; j--)
		{
			array[j] = array[j - 1];
		}
		
		array[0] = input;
		for (int j = 0; j <= i; j++)
		{
			printf("%d ", array[j]);
		}
		printf("\n");
	}
}

void insert_last(int array[], int size)
{
	int i; //반복문 관련 배열
	int j; //반복문 관련 배열
	int input; //입력 관련 배열

	for (i = 0; i < 5; i++)
	{
		printf("입력값: ");
		scanf("%d", &input);

		array[size + i] = input;
		for (int j = 0; j < size + i + 1; j++)
		{
			printf("%d ", array[j]);
		}
		printf("\n");
	}
}

void insert(int array[], int size)
{
	int number; //저장값 입력 관련 배열
	int location; //저장 위치 관련 배열

	printf("저장값 지정: ");
	scanf("%d", &number);
	printf("저장위치 지정: ");
	scanf("%d", &location);

	for (int i = size; i >= location - 1; i--)
	{
		array[i + 1] = array[i];
	}
	array[location - 1] = number;
}

void delete_first(int array[], int size)
{

	for (int i = 0; i < size; i++)
	{
		array[i] = array[i + 1];
	}

	for (int i = 0; i < size - 1; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void delete_last(int* size)
{
	(*size)--;
}
void delete(int array[], int size)
{
	int location; //삭제 위치 관련 배열

	printf("삭제위치 지정: ");
	scanf("%d", &location);

	for (int i = location - 1; i < size; i++)
	{
		array[i] = array[i + 1];
	}

	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void print_array(int array[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void is_empty(int csize, int dsize)
{
	printf("배열이 남았습니다.\n");
	printf("남은 배열 수: %d\n", csize - dsize);
}

void is_full(int cSize, int dSize)
{
	if (cSize == dSize)
	{
		printf("배열이 다 찼습니다.\n");
	}
	else
	{
		is_empty(cSize, dSize);
	}
}

int main()
{
	struct ArrayList a; //배열
	int i; //반복문에서 사용
	int d_count; // delete횟수 관련 배열
	int i_count; // insert횟수 관련 배열

	printf("원소의 개수 입력: ");
	scanf("%d", &a.capacity);

	//배열 동적 할당 및 데이터 갯수 설정
	a.array = malloc(sizeof(int) * a.capacity);
	a.number = 5;
	printf("앞에서 입력\n");
	insert_first(a.array, a.number);

	printf("뒤에서 입력\n");
	insert_last(a.array, a.number);
	a.number += 5;

	//처음것 지움
	printf("처음것 지울 횟수 지정: ");
	scanf("%d", &d_count);
	for (i = 0; i < d_count; i++)
	{
		delete_first(a.array, a.number - i);
	}
	a.number -= d_count;

	//마지막 지움
	printf("마지막 지울 횟수 지정: ");
	scanf("%d", &d_count);
	for (i = 0; i < d_count; i++)
	{
		delete_last(&a.number);
	}
	printf("변경된 배열 값: ");
	print_array(a.array, a.number);

	//위치 지정 추가
	printf("추가 횟수: ");
	scanf("%d", &i_count);
	for(i = 0; i < i_count; i++)
	{
		insert(a.array, a.number);
		a.number++;
	}
	printf("변경된 배열 값: ");
	print_array(a.array, a.number);

	//위치 지정 삭제
	printf("삭제 횟수: ");
	scanf("%d", &i_count);
	for (i = 0; i < i_count; i++)
	{
		delete(a.array, a.number);
		a.number--;
	}
	printf("변경된 배열 값: ");
	print_array(a.array, a.number);

	//다 차있는지 안차여 있는지 관련 결과
	printf("\n");
	is_full(a.capacity, a.number);
	return 0;
}