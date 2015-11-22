#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_newline(FILE *fp)
{
	/* cautiously insert '\n' at end of file */
	long current = ftell(fp);
	long seek = sizeof(char);
	fseek(fp, 0 - seek, SEEK_END);
	char c = fgetc(fp);
	if (c != '\n')
	{
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
	}
	rewind(fp); /* flush */
	fseek(fp, current, SEEK_SET);
}

unsigned count_tests(FILE *fp)
{
	/* get number of tests to loop through */
	long current = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char c;
	unsigned tests = 0;
	while ((c = fgetc(fp)) && !feof(fp))
	{
		if (c == '\n')
		{
			tests++;
		}
	}
	fseek(fp, current, SEEK_SET);
	return tests;
}

unsigned get_length(FILE *fp)
{
	/* gets length of current line */
	long current = ftell(fp);
	char c;
	unsigned len = 0;
	while (c != '\n')
	{
		c = fgetc(fp);
		len++;
	}
	fseek(fp, current, SEEK_SET);
	return len;
}

unsigned count_elements(char *buf, unsigned len)
{
	unsigned e_count = 0;
	unsigned trv = 0;
	char *current = (char *) malloc(sizeof(char) * len);
	while (sscanf(buf + trv, "%s", current) && trv < len)
	{
		trv += strlen(current) + 1; /* traverse current + space */
		e_count++;
	}
	free(current);
	return e_count;
}

void fill_array(char *buf, double *arr, unsigned e_count)
{
	unsigned i = 0;
	unsigned trv = 0;
	char *current = (char *) malloc(sizeof(char) * strlen(buf));
	while (i < e_count)
	{
		sscanf(buf + trv, "%s", current);
		sscanf(buf + trv, "%lf ", arr+i);
		trv += strlen(current) + 1; /* traverse current + space */
		i++;
	}
	free(current);
}

int compar(const void *a, const void *b)
{
    double x = *(double *)a;
    double y = *(double *)b;
    if (x < y)
        return -1;
    else if (x == y)
        return 0;
    else /* (x > y) */
        return 1;
}

void display_result(double *arr, unsigned e_count)
{
	unsigned i;
	for (i = 0; i < e_count; i++)
	{
		printf("%.3lf", *(arr+i));
		if (i == e_count - 1)
			printf("%c", '\n');
		else
			printf(" ");
	}
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
	unsigned i = 0;
	const unsigned total_tests = count_tests(file);
	while (i < total_tests)
	{
		const unsigned len = get_length(file);
		char *buf = (char *) malloc(sizeof(char) * len);
		fgets(buf, len + 1, file);
		const unsigned e_count = count_elements(buf, len);
		double *arr = (double *) malloc(sizeof(double) * e_count);
		fill_array(buf, arr, e_count);
		free(buf);
		qsort(arr, e_count, sizeof(double), compar);
		display_result(arr, e_count);
		free(arr);
		i++;
	}

	fclose(file);
	return 0;
}
