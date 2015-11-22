#include <stdio.h>

int decode(char c, int *lhit, int *hit)
{
	/* this probably could have been done better
       namely, returning the hit indicator... */
	if (c >= '0' && c <= '9')
	{
		*lhit = 1;
		*hit = 1;
		return c - '0';
	}
	else if (c >= 'a' && c <= 'j')
	{
		*lhit = 1;
		*hit = 1;
		return c - 'a';
	}
	else
		*hit = 0;
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
	char c;
	int lhit = 0; /* current line hit */
	int hit = 0; /* current char hit */
	while ((c = fgetc(file)) && !feof(file))
	{
		if (c == '\n')
		{
			if (!lhit) /* line contains no decode symbols */
			{
				printf("%s","NONE\n");
				lhit = 0;
			}
			else
			{
				printf("\n");
				lhit = 0;
			}
		}
		else /* decode() returns garbage if nothing is explicitly returned */
		{
			hit = 0;
			int c2 = decode(c, &lhit, &hit);
			if (hit)
				printf("%d", c2);
		}
	}
	fclose(file);
	return 0;
}
