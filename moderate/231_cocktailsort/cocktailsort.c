#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum _globals { MAX_BUF = 200 };

int compare(int a, int b)
{
	return (int) a - b;
}

void swap(int *a, int *b)
{
	register int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void printstate(int *arr, unsigned size)
{
	unsigned i;
	for (i = 0; i < size; i++)
	{
		printf("%d", arr[i]);
		if (i != size - 1)
			printf(" ");
	}
	printf("%c", '\n');
}

void cocktailsort(int *arr, unsigned size, unsigned iters)
{
	unsigned i;
	for (i = 0; i < iters; i++)
	{
		unsigned j; /* --> */
		for (j = 0; j < size - 1; j++)
		{
			int state = compare(arr[j], arr[j+1]);
			if (state > 0)
				swap(arr+j, arr+j+1);
			else
				continue;
		}
		unsigned k; /* <-- */
		for (k = size - 1; k > 0; k--)
		{
			int state = compare(arr[k-1], arr[k]);
			if (state > 0)
				swap(arr+k-1, arr+k);
			else
				continue;
		}
	}
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
	char buf[MAX_BUF] = { 0 };
	while (fscanf(file, "%[^\n]\n", buf))
	{
		unsigned size = 0;
		unsigned iters = 0;
		int *arr = (int *) calloc(MAX_BUF, sizeof(int));
		char *tok = strtok(buf, " ");
		while (tok != NULL)
		{
			if (*tok == '|')
			{
				tok = strtok(NULL, " ");
				iters = atoi(tok);
				break;
			}
			else
			{
				arr[size++] = atoi(tok);
				tok = strtok(NULL, " ");
			}

		}
		arr = (int *) realloc(arr, sizeof(int) * size);

		cocktailsort(arr, size, iters);
		printstate(arr, size);
		free(arr);
		if (feof(file))
			break;
	}
	fclose(file);
	return 0;
}
