#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int array[][3], char number) //���⼭ number�̶�� ������ main���� scanf�Է¹��� input�� ���� �ҷ����� �Ű�����
{
	int sum = 0; //���� ���ϴ� ����
	int i; //�ݺ������� ����ϴ� ����

	if ((number == '1') || (number == '2') || (number == '3')) //���� �� ���ϱ�(1, 2, 3�� ���ڷ� �޾Ұ� �̰��� �ε��� ������ �ٲٱ� ���ؼ� �ƽ�Ű�ڵ忡�� 1�� 10������ 49�� ��)
	{
		for (i = 0; i < 3; i++)
		{
			sum += array[number - 49][i];
		}
	}
	else if ((number == 'a') || (number == 'b') || (number == 'c')) //���� �� ���ϱ�(1, 2, 3�� ���ڷ� �޾Ұ� �̰��� �ε��� ������ �ٲٱ� ���ؼ� �ƽ�Ű�ڵ忡�� a�� 10������ 97�� ��)
	{
		for (i = 0; i < 3; i++)
		{
			sum += array[i][number - 97];
		}
	}
	return sum;
}

int main()
{
	int array[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	int result; //��� ���� ����
	char input;; //�Է��� �޴� ����

	scanf("%c", &input);
	result = sum(array, input);
	
	printf("%d\n", result);

	return 0;
}