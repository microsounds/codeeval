#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	char c, prev;
	while ((c = fgetc(file)) && !feof(file))
	{
		if (prev == c)
		{
			/* do nothing */
		}
		else
		{
			putchar(c);
		}
		prev = c;
	}
	fclose(file);
	return 0;
}
