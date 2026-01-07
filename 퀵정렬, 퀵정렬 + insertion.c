#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define standard 50

int input1[10000];
int input2[10000];
int input3[10000];

void QuickSort_medium(int array[], int left, int right)
{
	if (left >= right)
		return;

	int pivot_index;
	int medium = (left + right) / 2;;

	int temp = array[left];
	array[left] = array[medium];
	array[medium] = temp;

	int pivot = array[left];
	

	int i = left + 1;
	for (int j = left + 1; j <= right; j++)
	{
		if (array[j] < pivot)
		{
			int store = array[i];
			array[i] = array[j];
			array[j] = store;
			i++;
		}
	}

	pivot_index = i - 1;
	int store = array[left];
	array[left] = array[pivot_index];
	array[pivot_index] = store;

	QuickSort_medium(array, left, pivot_index - 1);
	QuickSort_medium(array, pivot_index + 1, right);
}

void QuickSort_left(int array[], int left, int right)
{
	if (left >= right)
		return;

	int pivot = array[left];

	int i = left + 1;
	for (int j = left + 1; j <= right; j++)
	{
		if (array[j] < pivot)
		{
			int store = array[i];
			array[i] = array[j];
			array[j] = store;
			i++;
		}
	}

	int pivot_index = i - 1;
	int store = array[left];
	array[left] = array[pivot_index];
	array[pivot_index] = store;

	QuickSort_left(array, left, pivot_index - 1);
	QuickSort_left(array, pivot_index + 1, right);
}

void InsertionSort(int array[], int left, int right) 
{
	for (int i = left + 1; i <= right; i++) 
	{
		int key = array[i];      
		int j = i - 1;

		while (j >= left && array[j] > key) 
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

void hybrid(int array[], int left, int right)
{
	if (left >= right)
		return;

	int pivot_index;
	int medium = (left + right) / 2;;

	int temp = array[left];
	array[left] = array[medium];
	array[medium] = temp;

	int pivot = array[left];


	int i = left + 1;
	for (int j = left + 1; j <= right; j++)
	{
		if (array[j] < pivot)
		{
			int store = array[i];
			array[i] = array[j];
			array[j] = store;
			i++;
		}
	}

	pivot_index = i - 1;
	int store = array[left];
	array[left] = array[pivot_index];
	array[pivot_index] = store;

	if (right - left + 1 > standard)
	{
		hybrid(array, left, pivot_index - 1);
		hybrid(array, pivot_index + 1, right);
	}
	else
	{
		InsertionSort(array, left, pivot_index - 1);
		InsertionSort(array, pivot_index + 1, right);
	}
}


int main()
{
	clock_t start, end;
	FILE* fp1 = fopen("C:\\Users\\user\\Downloads\\random_numbers.txt","r");
	for (int i = 0; i < 10000; i++)
		fscanf(fp1, "%d", &input1[i]);
	start = clock();
	QuickSort_medium(input1, 0, 9999);
	end = clock();
	printf("pivot이 medium일때 시간: %f\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);


	FILE* fp2 = fopen("C:\\Users\\user\\Downloads\\random_numbers.txt", "r");
	for (int i = 0; i < 10000; i++)
		fscanf(fp2, "%d", &input2[i]);
	start = clock();
	QuickSort_left(input2, 0, 9999);
	end = clock();
	printf("pivot이 left일때 시간: %f\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);

	FILE* fp3 = fopen("C:\\Users\\user\\Downloads\\random_numbers.txt", "r");
	for (int i = 0; i < 10000; i++)
		fscanf(fp3, "%d", &input3[i]);
	start = clock();
	hybrid(input3, 0, 9999);
	end = clock();
	printf("hybrid일때 시간: %f\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}