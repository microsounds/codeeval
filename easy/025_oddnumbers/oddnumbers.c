#include <stdio.h>

int isEven(int n)
{
	return (n % 2) ? 0 : 1;
}

int main(void)
{
	int i;
	for (i = 1; i < 100; i++)
	{
		if (!isEven(i))
			printf("%d\n", i);
	}
	return 0;
}
