#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void force_suffix(FILE *fp, const char insert)
{
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

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int determine_duplicate(char *str)
{
	/* determine duplicate assuming it only occurs twice */
	char *token = strtok(str, ";,");
	unsigned size = atoi(token);

	int *array = (int *) malloc(sizeof(int) * size);
	unsigned i = 0;
	while (token != NULL && i < size)
	{
		token = strtok(NULL, ";,");
		array[i] = atoi(token);
		i++;
	}
	qsort(array, size, sizeof(int), compare);
	int duplicate = 0;
	for (i = 1; i < size; i++)
	{
		if (array[i - 1] == array[i])
		{
			duplicate = array[i - 1];
			break; /* early out */
		}
	}
	free(array);
	return duplicate;
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
	char *str = (char *) malloc(sizeof(char) * 200);
	while (fscanf(file, "%[^\n]\n", str))
	{
		int dupl = determine_duplicate(str);
		printf("%d\n", dupl);

		if (feof(file))
			break;
	}
	free(str);
	fclose(file);
	return 0;
}
