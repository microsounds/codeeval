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

char *strip_characters(const char *string, const char *remove)
{
	unsigned r_len = strlen(remove);
	unsigned len = strlen(string);
	char *out = (char *) malloc(sizeof(char) * len);
	unsigned i, j;
	unsigned k = 0; /* output index */
	for (i = 0; i < len; i++)
	{
		unsigned found = 0;
		for (j = 0; j < r_len; j++)
		{
			if (remove[j] == string[i])
				found = 1;
		}
		if (!found)
		{
			*(out+k) = string[i];
			k++;
		}
	}
	*(out+k) = '\0'; /* null terminate */
	return out;
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
	char *str = (char *) malloc(sizeof(char) * 100);
	while (fscanf(file, "%[^\n]\n", str))
	{
		char string[100], remove[100];
		char *token = strtok(str, ",");
		strcpy(string, token);
		token = strtok(NULL, " ");
		strcpy(remove, token);
		char *result = strip_characters(string, remove);
		printf("%s\n", result);
		free(result);

		if (feof(file))
			break;
	}
	free(str);
	fclose(file);
	return 0;
}
