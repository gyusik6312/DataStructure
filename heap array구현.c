#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap
{
	int* array;
	int recent_count; // Èü ¾ÈÀÇ Ç×¸ñ °³¼ö
	int capacity; // ÈüÀÇ ¿ë·®
	int heap_type; //ÈüÀÇ Á¾·ù
	int count[3];
}Heap;

void deleteMin(Heap* data)
{
	int min = 101;
	int min_index = 0;
	if (data->heap_type == 0)
	{
		for (int i = 20; i < data->recent_count; i++)
		{
			if (min > data->array[i])
			{
				min = data -> array[i];
				min_index = i;
			}
		}

		if(min_index != data->recent_count - 1)
		{
			for (int i = min_index; i < data->recent_count; i++)
			{
				data->array[i] = data->array[i + 1];
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (min > data->array[i])
			{
				min = data->array[i];
				min_index = i;
			}
		}
		for (int i = min_index; i < data->recent_count; i++)
		{
			data->array[i] = data->array[i + 1];
		}
	}
	data->recent_count--;
	printf("%d»èÁ¦\n", min);
}

int main()
{
	Heap* data = malloc(sizeof(Heap));
	int random;
	data->capacity = 30;
	data->recent_count = 0;

	printf("ÈüÀÇ Á¾·ù(1 == min / 0 == max): ");
	scanf("%d", &data->heap_type);

	for (int i = 0; i < 3; i++)
	{
		data->count[i] = 0;
	}

	data->array = malloc(sizeof(int) * 30);

	srand(time(NULL));
	if (data->heap_type == 0)
	{
		for (int i = 0; i < 30; i++)
		{
			random = 1 + rand() % 99;
			data->recent_count++;
			if ((((61 <= random) && (random <= 100))) && (data->count[0] < 10))
			{
				data->array[0 + data->count[0]] = random;
				data->count[0]++;
			}
			else if (((31 <= random) && (random <= 60)) && (data->count[1] < 10))
			{
				data->array[10 + data->count[1]] = random;
				data->count[1]++;
			}
			else if((((0 <= random) && (random <= 30)) && (data->count[2] < 10)))
			{
				data->array[20 + data->count[2]] = random;
				data->count[2]++;
			}
			else
			{
				i--;
				data->recent_count--;
			}
		}
	}
	else
	{
		for (int i = 0; i < 30; i++)
		{
			random = 1 + rand() % 100;
			data->recent_count++;
			if (((0 <= random) && (random <= 30)) &&((data->count[0] < 10)))
			{
				data->array[0 + data->count[0]] = random;
				data->count[0]++;
			}
			else if (((31 <= random) && (random <= 60)) && (((data->count[1] < 10))))
			{
				data->array[10 + data->count[1]] = random;
				data->count[1]++;
			}
			else if ((((61 <= random) && (random <= 100)) && (data->count[2] < 10)))
			{
				data->array[20 + data->count[2]] = random;
				data->count[2]++;
			}
			else
			{
				i--;
				data->recent_count--;
			}
		}
	}

	for (int i = 0; i < 30; i++)
	{
		printf("%d  ", data->array[i]);
	}
	printf("\n");

	deleteMin(data);
	for (int i = 0; i < data->recent_count; i++)
	{
		printf("%d  ", data->array[i]);
	}

	return 0;
}