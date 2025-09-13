#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct inf
{
	char name[10];
	int age;
	double score;
};

void print(const struct inf* a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%s %d %lf\n", a[i].name, a[i].age, a[i].score);
	}
}

double operate(const struct inf* a, int size)
{
	double average = 0;
	for (int i = 0; i < size; i++)
	{
		average += a[i].score;
	}
	average /= size;

	return average;
}

int main()
{
	int size;
	printf("입력 학생수: ");
	scanf("%d", &size);
	struct inf *array = (struct inf*)malloc(sizeof(struct inf) * size);
	int i;
	double result;

	for (i = 0; i < size; i++)
	{
		printf("이름: ");
		scanf("%s", array[i].name);
		printf("나이: ");
		scanf("%d", &array[i].age);
		printf("성적: ");
		scanf("%lf", &array[i].score);
		printf("\n");
	}

	result = operate(array, size);
	print(array, size);
	printf("%lf", result);

	free(array);

	return 0;
}