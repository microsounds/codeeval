#include <stdio.h>

int mod(int n, int m)
{
	int tmp = n / m;
	tmp = tmp * m;
	tmp = n - tmp;
	return tmp;
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
	int n, m;
	while (fscanf(file, "%d,%d", &n, &m) && !feof(file))
	{
		printf("%d\n", mod(n, m));
	}
	fclose(file);
	return 0;
}
