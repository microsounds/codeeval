#include <stdio.h>

int fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	else
	{
		int n;
		while (fscanf(file, "%d", &n) && !feof(file))
			printf("%d\n", fib(n));
		fclose(file);
		return 0;
	}
}
