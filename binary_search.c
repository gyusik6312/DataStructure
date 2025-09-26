#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

int array1[SIZE];
int array2[SIZE];
int array3[SIZE];

int main()
{
	int random;
	int low;
	int high;
	int mid;
	int index;
	double sum;
	clock_t start, end;

	srand(time(NULL));

	for (int i = 0; i < SIZE; i++)
		array1[i] = 1 + rand() % 40000;
	printf("SIZE가 %d일때", SIZE);
	sum = 0;
	for (int i = 0; i < 100; i++)
	{
		start = clock();
		random = 1 + rand() % 40000;

		for (int j = 0; j < 10000; j++)
		{
			if (random == array1[j])
				break;
		}
		end = clock();
		sum += (double)(end - start) / CLOCKS_PER_SEC;
	}
	printf("\n정렬되지 않은 배열 linear search의 평균시간: %lf\n", sum / (double)100);

	for (int i = 0; i < SIZE; i++)
		array2[i] = (i + 1) * 2;

	sum = 0;
	for (int i = 0; i < 100; i++)
	{
		start = clock();
		random = 1 + rand() % 40000;

		for (int j = 0; j < SIZE; j++)
		{
			if ((random == array2[j]) || (random < array2[j]))
				break;
		}
		end = clock();
		sum += (double)(end - start) / CLOCKS_PER_SEC;
	}
	printf("\n정렬 된 배열 linear search의 평균시간: %lf\n", sum / (double)100);

	for (int i = 0; i < SIZE; i++)
		array3[i] = (i + 1) * 2;

	sum = 0;
	for (int i = 0; i < 100; i++)
	{
		high = SIZE - 1;
		low = 0;
		start = clock();
		random = 1 + rand() % 40000;
		while(low <= high)
		{
			mid = low + (high - low) / 2;
			if (array3[mid] < random)
			{
				low = mid + 1;
			}
			else if (array3[mid] == random)
			{
				break;
			}
			else
			{
				high = mid - 1;
			}

		}
		end = clock();
		sum = (double)(end - start) / CLOCKS_PER_SEC;
	}
	printf("\n정렬 된 배열 binary search의 평균시간: %lf\n", sum / (double)100);
	return 0;
}