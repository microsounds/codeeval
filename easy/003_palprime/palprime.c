#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPrime(int num)
{
	num = abs(num);
	if (num == 1) /* 1 can't be prime */
		return 0;
	int i;
	for (i = 2; i < num; i++)
	{
		if (num % i == 0 && i != num)
			return 0;
	}
	return 1;
}

char *strrev(char *str)
{
	int length = strlen(str) - 1; /* omit \0 */
	char *tmp = malloc(length);
	int a = length;
	int b = 0;
	while (a >= 0 && b <= length)
	{
		strncpy(tmp+b, str+a, sizeof(char));
		a--;
		b++;
	}
	return tmp;
}

int main(int argc, char **argv)
{
	int i = 1000 - 1;
	for (i; i > 0; --i)
	{
		if (isPrime(i))
		{
			char str_a[10], str_b[10];
			sprintf(str_a, "%d", i);
			sprintf(str_b, "%s", strrev(str_a));
			if (!strcmp(str_a, str_b))
			{
				printf("%d\n", i);
				return 0;
			}
		}
	}
	return 0;
}
