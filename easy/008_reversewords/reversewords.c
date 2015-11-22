#include <stdio.h>
#include <string.h>

void insert_newline(FILE *fp)
{
	/* insert newline if none exists */
	long current = ftell(fp);
	long seek = sizeof(char);
	fseek(fp, 0 - seek, SEEK_END);
	char c = fgetc(fp);
	if (c != '\n')
	{
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
	}
	rewind(fp); /* flush buffer */
	fseek(fp, current, SEEK_SET);
}

void reverse_line(char *buf, unsigned len)
{
	char array[200][200];
	unsigned i = 0;
	unsigned trv = 0; /* traverse distance */
	while (sscanf(buf + trv, "%s", array[i]) && trv < len)
	{
		strncpy(array[i], array[i], strlen(array[i])); /* strip newlines */
		trv += strlen(array[i]) + 1; /* traverse to next word + space */
		i++;
	}
	while (0 < i--)
	{
		printf("%s", array[i]);
		if (i == 0)
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
	char line[200] = "";
	while (fgets(line, 200, file) && !feof(file))
	{
		reverse_line(line, strlen(line));
	}
	fclose(file);
	return 0;
}
