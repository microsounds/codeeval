#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void force_suffix(FILE *fp, const char insert)
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

int count_ones(int num)
{
	/* whittle away at num
	   and count the number of 1's
	   until num becomes zero. */
	int ones = 0;
	while (num)
	{
    	if (num & 1)
        	ones++;
    	num >>= 1;
	}
	return ones;
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
	int num;
	while (fscanf(file, "%d", &num) && !feof(file))
	{
		printf("%d\n", count_ones(num));
	}

	fclose(file);
	return 0;
}
