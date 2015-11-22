#include <stdio.h>
#include <math.h>

void insert_newline(FILE *fp)
{
	/* adds newline char to end of file if it doesn't exist */
	int seek = sizeof(char);
	fseek(fp, 0 - seek, SEEK_END);
	char c = fgetc(fp);
	if (c != '\n')
	{
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
	}
	rewind(fp);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r+");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}

	insert_newline(file);
	static const unsigned MAX_N = 100; /* maximum NxN size is 10x10 */
	char matrix[MAX_N];
	unsigned ncount = 0;
	char c;
	while ((c = fgetc(file)) && !feof(file))
	{
		if (c == '\n')
		{
			unsigned n = sqrt(ncount); /* row/column length */
			char rotate[MAX_N];

			unsigned iter, k; /* offset */
			for (iter = 0, k = 0; iter < n; iter++)
			{
				unsigned place, l; /* rotation */
				for (l = 0, place = ncount + iter; l < n; l++)
				{
					place -= n;
					rotate[k++] = matrix[place];
				}
			}

			unsigned j; /* output */
			for (j = 0; j <= ncount - 1; j++)
			{
				printf("%c", rotate[j]);
				if (j != ncount - 1)
					printf(" ");
				else
					printf("\n");
			}

			unsigned i; /* wiping persistent data for next run */
			for (i = 0; i <= ncount; i++)
			{
				matrix[i] = '\0';
			}
			ncount = 0;
		}
		else
		{
			if (c != ' ')
			{
				matrix[ncount] = c;
				ncount++;
			}
		}
	}
	fclose(file);
	return 0;
}
