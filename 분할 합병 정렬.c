#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int left, int mid, int right)
{
    int i = left;      
    int j = mid + 1;    
    int k = 0;          

    int temp[1000];     

    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= mid)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    for (int t = 0; t < k; t++)
        array[left + t] = temp[t];

}

void merge_sorting(int array[], int left, int right)
{
	if (left >= right)
		return;
	int mid = (right + left) / 2;

    merge_sorting(array, left, mid);
    merge_sorting(array, mid + 1, right);

    merge(array, left, mid, right);
}

int main()
{
	FILE* fp;
	fp = fopen("C:\\Users\\user\\Downloads\\input.txt", "r");
    int count;
    int* array;

    fscanf(fp, " %d", &count);
    array = malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++)
    {
        fscanf(fp, "%d", &array[i]);
    }
    for (int i = 0; i < count; i++)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
    merge_sorting(array, 0, count - 1);

    for (int i = 0; i < count; i++)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");

    fclose(fp);
    return 0;
}