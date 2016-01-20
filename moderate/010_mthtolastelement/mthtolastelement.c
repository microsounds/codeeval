#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum _globals { MAX_BUF = 500 };

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
		unsigned m = 0;
		char *arr = (char *) calloc(MAX_BUF, sizeof(char));
		char *tok = strtok(buf, " ");
		while (tok != NULL)
		{
			if (tok[0] >= '0' && tok[0] <= '9')
			{
				m = atoi(tok);
				break;
			}
			else
			{
				arr[size++] = tok[0];
				tok = strtok(NULL, " ");
			}
		}
		arr = realloc(arr, sizeof(char) * size);
		if (m > size)
			goto abort;
		else
			printf("%c\n", arr[size - m]);

		abort: free(arr);
		if (feof(file))
			break;
	}
	fclose(file);
	return 0;
}
