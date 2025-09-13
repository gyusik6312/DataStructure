#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

long long fac(int n)
{
	if (n == 1)
		return 1;
	else
	{
		printf("순환 진행중: %d\n", n);
		return n * fac(n - 1);
	}
}

long long factorial(int n, double *result)
{
	int i;
	long long sum = 1;
	time_t start, end;
	start = clock();
	for (i = 2; i <= n; i++)
	{
		sum *= i;
		printf("for 진행중: %d\n", i);
	}
	end = clock();
	*result = (double)(end - start);

	return sum;
}

int main()
{
	int size;
	long long result1; //순환 활용
	long long result2; //for활용
	double result3, result4; //시간 측정

	printf("사이즈 입력: ");
	scanf("%d", &size);

	time_t start, end;

	result2 = factorial(size, &result4);
	printf("값\n");
	printf("%lld\n", result2);
	printf("시간\n");
	printf("%lf\n", result4);

	start = clock();
	result1 = fac(size);
	end = clock();
	result3 = (double)(end - start);
	printf("값\n");
	printf("%lld\n", result1);
	printf("시간\n");
	printf("%lf\n\n\n", result3);

	return 0;
}