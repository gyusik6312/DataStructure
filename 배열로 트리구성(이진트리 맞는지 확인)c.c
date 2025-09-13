#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int create_level()
{
	int number;
	printf("level�� �Է��Ͻÿ�: ");
	scanf("%d", &number);

	return number;
}

int* create_tree(int size)
{
	int* array;
	array = malloc(size * sizeof(int));

	array[0] = 1; //�ε��� 0�� ��Ʈ���ν� ������ ä�������ϱ� �����̴�. 
	for (int i = 1; i < size; i++)
	{
		array[i] = 0;
	}

	return array;
}

void check_tree(int* array, int size)
{
	int count; //���� �ε��� ���� ��
	int index; //�ε���
	int check; //0�̸� Ʈ��, 1�̸� Ʈ�� �ƴ�
	int min = size - 1;

	srand(time(NULL));
	while (1)
	{
		check = 0;
		count = rand() % (size - 1);

		for (int i = 0; i < count; i++)
		{
			index = 1 + rand() % (size - 1);
			array[index] = 1 + rand() % size;

		}
		for (int i = 1; i < size; i++)
		{
			if ((array[i] != 0) && (i % 2 != 0) && (array[i / 2] == 0))
			{
				check = 1;
				printf("Ʈ�� �ƴմϴ�. \n");
				for (int j = 0; j < size; j++)
				{
					printf("%d ", array[j]);
				}
				printf("\n");

				for (i = 1; i < size; i++)
				{
					array[i] = 0;
				}
				break;
			}
			else if ((array[i] != 0) && (i % 2 == 0) && (array[(i / 2) - 1] == 0))
			{
				check = 1;
				printf("Ʈ�� �ƴմϴ�. \n");
				for (int j = 0; j < size; j++)
				{
					printf("%d ", array[j]);
				}
				printf("\n");

				for (i = 1; i < size; i++)
				{
					array[i] = 0;
				}
				break;
			}

		}
		if (check == 0)
		{
			printf("Ʈ���¾ƿ�\n");
			for (int j = 0; j < size; j++)
			{
				printf("%d ", array[j]);
			}
			break;
		}
	}
}

int main()
{
	int level = create_level();
	int size = pow(2, level) - 1;
	int* tree = create_tree(size);

	check_tree(tree, size);

	return 0;
}