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
	int fc = 1; /* first char case */
	char c, prev;
	while ((c = fgetc(file)) && !feof(file))
	{
		/* if first char and/or prev is \n or space */
		if (fc || prev == '\n' || prev == ' ')
		{
			if (c >= 'a' && c <= 'z')
				printf("%c", c - 32);
			else
				printf("%c", c);
		}
		else
			printf("%c", c);

		prev = c;
		if (fc)
			fc = !fc; /* deactivates first char case */
	}
	fclose(file);
	return 0;
}

