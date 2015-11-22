#include <stdio.h>

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
	int total = 0;
	while (fscanf(file, "%d", &num) && !feof(file))
	{
		total += num;
	}
	printf("%d\n", total);
	fclose(file);
	return 0;
}
