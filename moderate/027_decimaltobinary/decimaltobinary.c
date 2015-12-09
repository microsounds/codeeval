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

void to_binary(unsigned num, char *buf)
{
	/* right shift unsigned int
	   until nothing is left */
	unsigned i = 0;
	while (num > 0)
	{
		if (num & 1)
			*(buf+i) = '1';
		else
			*(buf+i) = '0';
		num >>= 1;
		i++;
	}

	/* null terminate string */
	*(buf+i) = '\0';
}

void strrev(char *arr)
{
	/* reverses char array in place */
	unsigned len = strlen(arr);
	unsigned i = len - 1;
	unsigned j = 0;
	char c;
	while (i > j)
	{
		c = *(arr+i);
		*(arr+i) = *(arr+j);
		*(arr+j) = c;
		j++;
		i--;
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
	force_suffix(file, '\n');
	unsigned num;
	while (fscanf(file, "%u", &num) && !feof(file))
	{
		if (num < 1)
			printf("%d\n", 0);
		else
		{
			char *buf = (char *) malloc(sizeof(char) * 80);
			to_binary(num, buf);
			strrev(buf);
			printf("%s\n", buf);
			free(buf);
		}
	}
	fclose(file);
	return 0;
}
