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
	int x, n;
	while (fscanf(file, "%d,%d", &x, &n) && !feof(file))
	{
		int tmp = 0;
		while (!(tmp >= x))
		{
			tmp += n;
		}
		printf("%d\n", tmp);
	}
	fclose(file);
	return 0;
}
