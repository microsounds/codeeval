#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void force_suffix(FILE *fp, char insert)
{
	/* forcibly insert char at end of file */
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

unsigned uintlen(unsigned n)
{
	unsigned len = 1;
	while (n /= 10)
	{
		len++;
	}
	return len;
}

char *strrev_p(char *arr)
{
	/* returns a pointer to a malloc'd
	   reversed string, free() when finished */
	unsigned len = strlen(arr);
	char *tmp = (char *) malloc(sizeof(char) * len);
	unsigned i = len - 1;
	unsigned j = 0;
	while (len > j)
	{
		*(tmp+j) = *(arr+i);
		j++;
		i--;
	}
	return (char *) tmp;
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
	unsigned n;
	while (fscanf(file, "%u", &n) && !feof(file))
	{
		unsigned iter = 0;
		unsigned len = uintlen(n);
		char *arr = (char *) malloc(sizeof(char) * len);
		sprintf(arr, "%u", n);
		char *arr_r = strrev_p(arr); /* arr_r is malloc'd elsewhere */
		while (strcmp(arr, arr_r) != 0)
		{
			/* loop endlessly until palindrome is found */
			n += atoi(arr_r);
			free(arr_r);
			len = uintlen(n);
			arr = (char *) realloc(arr, sizeof(char) * len); /* resize str */
			sprintf(arr, "%u", n);
			char *arr_r = strrev_p(arr);
			iter++;
		}

		printf("%u %s\n", iter, arr);

		free(arr_r);
		free(arr);
	}
	fclose(file);
	return 0;
}
