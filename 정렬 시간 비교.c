#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void select(int a[], int size)
{
    int min;
    int temp;
    for (int i = 0; i < size; i++)
    {
        min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (a[min] > a[j])
                min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void buble(int a[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
}

void insert_sort(int a[], int size)
{
    int key, j;
    for (int i = 1; i < size; i++)
    {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(sizeof(int) * n1);
    int* R = (int*)malloc(sizeof(int) * n2);

    // 왼쪽 배열 복사
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];

    // 오른쪽 배열 복사
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // 병합
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    // 왼쪽에 남은 요소 복사
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    // 오른쪽에 남은 요소 복사
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int left, int right) {
    int mid = (left + right) / 2;   // 미들 피봇
    int pivot = arr[mid];

    // 피봇을 오른쪽으로 보내고 시작 (편한 구현)
    swap(&arr[mid], &arr[right]);

    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // 피봇을 제자리로
    swap(&arr[i + 1], &arr[right]);

    return i + 1;
}

void quickSort(int arr[], int left, int right)
{
    if (left < right) {
        int p = partition(arr, left, right);
        quickSort(arr, left, p - 1);
        quickSort(arr, p + 1, right);
    }
}


void print(int a[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d  ", a[i]);
    printf("\n");
}

typedef struct heap
{
    int* array;
    int capacity;
    int size;
    int type;
}heap;

heap* createHeap(int capacity, int heap_type)
{
    heap* h = malloc(sizeof(heap));
    h->capacity = capacity;
    h->type = heap_type;
    h->size = 0;
    h->array = malloc(sizeof(int) * capacity);

    return h;
}

int left_child(heap* h, int i)
{
    int l = i * 2 + 1;
    if (l >= h->size)
        return -1;
    else
        return l;
}

int right_child(heap* h, int i)
{
    int r = i * 2 + 2;
    if (r >= h->size)
        return -1;
    else
        return r;
}

void PercolateDown(heap* h, int i)
{
    int l, r, max, temp;
    l = left_child(h, i);
    r = right_child(h, i);

    if (l != -1 && h->array[l] > h->array[i])
        max = l;
    else
        max = i;
    if (r != -1 && h->array[max] < h->array[r])
        max = r;
    if (max != i)
    {
        temp = h->array[max];
        h->array[max] = h->array[i];
        h->array[i] = temp;
        PercolateDown(h, max);
    }
}

void BuildHeap(heap* h, int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        h->array[i] = A[i];
    }
    h->size = n;
    for (int i = (h->size - 2) / 2; i >= 0; i--)
    {
        PercolateDown(h, i);
    }
}

heap* HeapSort(int A[], int n)
{
    heap* h = createHeap(n, 1);
    BuildHeap(h, A, n);
    int temp, old_size;
    old_size = h->size;

    for (int i = n; i > 0; i--)
    {
        temp = h->array[0];
        h->array[0] = h->array[h->size - 1];
        h->array[h->size - 1] = temp;
        h->size--;
        PercolateDown(h, 0);
    }
    h->size = old_size;
    return h;
}

int main()
{
    srand(time(NULL));

    for (int n = 5000; n <= 60000; n += 5000)
    {
        printf("\n====================================\n");
        printf("               N = %d\n", n);
        printf("====================================\n");

        int* arr = (int*)malloc(sizeof(int) * n);
        int* temp = (int*)malloc(sizeof(int) * n);

        for (int type = 0; type < 3; type++)
        {
            // ----------------------
            // 입력 종류 결정
            // ----------------------
            if (type == 0) {
                printf("\n[랜덤 배열]\n");
                for (int i = 0; i < n; i++)
                    arr[i] = rand() * rand();
            }
            else if (type == 1) {
                printf("\n[오름차순 배열]\n");
                for (int i = 0; i < n; i++)
                    arr[i] = i;
            }
            else {
                printf("\n[내림차순 배열]\n");
                for (int i = 0; i < n; i++)
                    arr[i] = n - i;
            }

            clock_t start, end;

            // =========================
            // Selection Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            select(temp, n);
            end = clock();
            printf("Selection Sort : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            // =========================
            // Bubble Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            buble(temp, n);
            end = clock();
            printf("Bubble Sort    : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            // =========================
            // Insertion Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            insert_sort(temp, n);
            end = clock();
            printf("Insertion Sort : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            // =========================
            // Merge Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            merge_sort(temp, 0, n - 1);
            end = clock();
            printf("Merge Sort     : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            // =========================
            // Quick Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            quickSort(temp, 0, n - 1);
            end = clock();
            printf("Quick Sort     : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            // =========================
            // Heap Sort
            // =========================
            memcpy(temp, arr, sizeof(int) * n);
            start = clock();
            heap* h = HeapSort(temp, n);
            end = clock();
            printf("Heap Sort      : %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);

            free(h->array);
            free(h);
        }

        free(arr);
        free(temp);
    }

    return 0;
}