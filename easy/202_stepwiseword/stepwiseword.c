#include <stdio.h>
#include <string.h>

void insert_newline(FILE *fp)
{
	/* insert \n at end of file if not present */
	long current = ftell(fp);
	long seek = sizeof(char);
	fseek(fp, 0 - seek, SEEK_END);
	char c = fgetc(fp);
	if (c != '\n')
	{
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
	}
	rewind(fp);
	fseek(fp, current, SEEK_SET);
}

void stepwise_print(char *buf, unsigned len)
{
	unsigned i, j;
	for (i = 0; i <= len-1; i++)
	{
		for (j = 0; j < i; j++)
		{
			printf("%c", '*');
		}
		printf("%c", *(buf+i));
		if (i == len-1)
			printf("%c", '\n');
		else
			printf(" ");
	}
}

void longest_word(char *buf)
{
	unsigned trv = 0;
	char current[200] = "", candidate[200] = "";
	while (sscanf(buf + trv, "%s", current) && trv < strlen(buf))
	{
		/* gets the first longest word in the buffer */
		trv += strlen(current);
		if (strlen(current) > strlen(candidate))
		{
			strncpy(candidate, current, strlen(current));
		}
	}
	stepwise_print(candidate, strlen(candidate));
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
		longest_word(line);
	}
	fclose(file);
	return 0;
}
