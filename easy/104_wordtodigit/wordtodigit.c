#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void force_suffix(FILE *fp, char insert)
{
	/* force inserts trailing newline */
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
	/* returns number of loops */
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

void strreplace(char *arr, char target, char replace)
{
	/* overwrites target with replace */
	unsigned i = 0;
	unsigned len = strlen(arr);
	while (i <= len)
	{
		if (*(arr+i) == target)
			*(arr+i) = replace;
		i++;
	}
}

void to_digit(char *arr)
{
	static const char *key[10] = {
		"zero", "one", "two", "three", "four",
		"five", "six", "seven", "eight", "nine"
	};
	char current[5]; /* maximum word length */
	unsigned len = strlen(arr);
	unsigned trv = 0;
	while (sscanf(arr + trv, "%s", current) && trv < len)
	{
		trv += strlen(current) + 1; /* traverse current + space */
		unsigned i = 0;
		while (i <= 9)
		{
			/* match current string to answer key */
			if (strcmp(current, key[i]) == 0)
			{
				printf("%u", i);
				break;
			}
			i++;
		}
	}
	printf("%c", '\n');
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
	unsigned cases = get_cases(file, '\n');
	unsigned i = 0;
	while (i < cases)
	{
		/* 20 words + 20 spaces * max word length 5 */
		char *num = malloc(sizeof(char) * 120);
		fscanf(file, "%s", num);
		strreplace(num, ';', ' ');
		to_digit(num);
		free(num);
		i++;
	}
}
