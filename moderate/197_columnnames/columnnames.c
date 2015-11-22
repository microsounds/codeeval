#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void force_suffix(FILE *fp, char insert)
{
	/* forcibly inserts char if not present */
	long pos = ftell(fp);
	fseek(fp, 0 - sizeof(char), SEEK_END);
	if (fgetc(fp) != insert)
	{
		fseek(fp, 0, SEEK_END);
		fputc(insert, fp);
		fflush(fp);
	}
	fseek(fp, pos, SEEK_SET);
}

unsigned get_cases(FILE *fp, char delimiter)
{
	/* fetch # of loops to traverse */
	long pos = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	unsigned cases = 0;
	while (!feof(fp))
	{
		if (fgetc(fp) == delimiter)
			cases++;
	}
	fseek(fp, pos, SEEK_SET);
	return cases;
}

unsigned uintlen(unsigned *uint)
{
	unsigned len = 1;
	unsigned n = *uint;
	while (n /= 10)
	{
		len++;
	}
	return len;
}
void strrev(char *str)
{
	int j = strlen(str) - 1;
	int k = 0;
	char c;
	while (j > k)
	{
		c = *(str+j);
		*(str+j) = *(str+k);
		*(str+k) = c;
		j--;
		k++;
	}
}

void excel_header(unsigned *col, char *arr)
{
	unsigned i = *col;
	unsigned place = 0;
	while (i > 0)
	{
		unsigned mod = (i - 1) % 26;
		i = (i - mod) / 26;
		*(arr+place) = mod + 'A';
		place++;
	}
	strrev(arr);
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
	force_suffix(file, '\n');
	unsigned i = 0, cases = get_cases(file, '\n');
	while (cases > i++)
	{
		/* this program supports up to 4,294,967,295 columns */
		unsigned *col = (unsigned *) malloc(sizeof(unsigned));
		fscanf(file, "%u", col);
		unsigned len = uintlen(col);
		char *arr = (char *) malloc(sizeof(char) * len);
		excel_header(col, arr);
		printf("%s\n", arr);
		free(col);
		free(arr);
	}

	fclose(file);
	return 0;
}
