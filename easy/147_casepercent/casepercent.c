#include <stdio.h>

void insert_newline(FILE *fp)
{
	/* insert \n in test file if not present */
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
	int lcase = 0;
	int ucase = 0;
	char c;
	while ((c = fgetc(file)) && !feof(file))
	{
		if (c == '\n')
		{
			if (lcase + ucase)
			{
				printf("lowercase: %.2f uppercase: %.2f\n",
					   ((double) (lcase * 100) / (lcase + ucase)),
					   ((double) (ucase * 100) / (lcase + ucase)));
				lcase = 0;
				ucase = 0; /* reset counts */
			}
			else /* empty line or no A-Za-z chars */
			{
				printf("lowercase: %.2f uppercase: %.2f\n",
					   (double) lcase * 100, (double) ucase * 100);
			}
		}
		else if (c >= 'A' && c <= 'Z')
			ucase++;
		else if (c >= 'a' && c <= 'z')
			lcase++;
	}
	fclose(file);
	return 0;
}
