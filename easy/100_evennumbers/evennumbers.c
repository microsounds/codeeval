#include <stdio.h>

int isEven(int num)
{
	return !(num % 2);
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
	int num;
	while (fscanf(file, "%d", &num) && !feof(file))
		printf("%d\n", isEven(num));
	fclose(file);
	return 0;
}
