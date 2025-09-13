#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum(int array[][3], char number) //여기서 number이라는 변수는 main에서 scanf입력받은 input의 값을 불러오는 매개변수
{
	int sum = 0; //합을 구하는 변수
	int i; //반복문에서 사용하는 변수

	if ((number == '1') || (number == '2') || (number == '3')) //열의 합 구하기(1, 2, 3을 문자로 받았고 이것을 인덱스 값으로 바꾸기 위해서 아스키코드에서 1의 10진수인 49를 뺌)
	{
		for (i = 0; i < 3; i++)
		{
			sum += array[number - 49][i];
		}
	}
	else if ((number == 'a') || (number == 'b') || (number == 'c')) //행의 합 구하기(1, 2, 3을 문자로 받았고 이것을 인덱스 값으로 바꾸기 위해서 아스키코드에서 a의 10진수인 97를 뺌)
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
	int result; //결과 도출 변수
	char input;; //입력을 받는 변수

	scanf("%c", &input);
	result = sum(array, input);
	
	printf("%d\n", result);

	return 0;
}