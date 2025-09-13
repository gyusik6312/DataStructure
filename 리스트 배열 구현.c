#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct ArrayList
{
	int capacity; //����Ʈ�� ������
	int number; //���� ������ ����
	int* array;
};

void insert_first(int array[], int size)
{
	int i; //�ݺ��� ���� �迭
	int j; //�ݺ��� ���� �迭
	int input; //�Է� ���� �迭

	for (i = 0; i < 5; i++)
	{
		printf("�Է°�: ");
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
	int i; //�ݺ��� ���� �迭
	int j; //�ݺ��� ���� �迭
	int input; //�Է� ���� �迭

	for (i = 0; i < 5; i++)
	{
		printf("�Է°�: ");
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
	int number; //���尪 �Է� ���� �迭
	int location; //���� ��ġ ���� �迭

	printf("���尪 ����: ");
	scanf("%d", &number);
	printf("������ġ ����: ");
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
	int location; //���� ��ġ ���� �迭

	printf("������ġ ����: ");
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
	printf("�迭�� ���ҽ��ϴ�.\n");
	printf("���� �迭 ��: %d\n", csize - dsize);
}

void is_full(int cSize, int dSize)
{
	if (cSize == dSize)
	{
		printf("�迭�� �� á���ϴ�.\n");
	}
	else
	{
		is_empty(cSize, dSize);
	}
}

int main()
{
	struct ArrayList a; //�迭
	int i; //�ݺ������� ���
	int d_count; // deleteȽ�� ���� �迭
	int i_count; // insertȽ�� ���� �迭

	printf("������ ���� �Է�: ");
	scanf("%d", &a.capacity);

	//�迭 ���� �Ҵ� �� ������ ���� ����
	a.array = malloc(sizeof(int) * a.capacity);
	a.number = 5;
	printf("�տ��� �Է�\n");
	insert_first(a.array, a.number);

	printf("�ڿ��� �Է�\n");
	insert_last(a.array, a.number);
	a.number += 5;

	//ó���� ����
	printf("ó���� ���� Ƚ�� ����: ");
	scanf("%d", &d_count);
	for (i = 0; i < d_count; i++)
	{
		delete_first(a.array, a.number - i);
	}
	a.number -= d_count;

	//������ ����
	printf("������ ���� Ƚ�� ����: ");
	scanf("%d", &d_count);
	for (i = 0; i < d_count; i++)
	{
		delete_last(&a.number);
	}
	printf("����� �迭 ��: ");
	print_array(a.array, a.number);

	//��ġ ���� �߰�
	printf("�߰� Ƚ��: ");
	scanf("%d", &i_count);
	for(i = 0; i < i_count; i++)
	{
		insert(a.array, a.number);
		a.number++;
	}
	printf("����� �迭 ��: ");
	print_array(a.array, a.number);

	//��ġ ���� ����
	printf("���� Ƚ��: ");
	scanf("%d", &i_count);
	for (i = 0; i < i_count; i++)
	{
		delete(a.array, a.number);
		a.number--;
	}
	printf("����� �迭 ��: ");
	print_array(a.array, a.number);

	//�� ���ִ��� ������ �ִ��� ���� ���
	printf("\n");
	is_full(a.capacity, a.number);
	return 0;
}