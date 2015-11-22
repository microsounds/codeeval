#include <stdio.h>
#include <ctype.h>
#include <math.h>

int toDecimal(char c)
{
	if (isupper(c))
		tolower(c);
	if (c >= 'a' && c <= 'f')
	{
		/* 'a' thru 'f' - 87 renders it's dec value */
		return (int)c - 87;
	}
	else
		return -1;
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
	char buffer[80];
	const int base = 16;
	while (fscanf(file, "%s", buffer) && !feof(file))
	{
		int len = 0;
		int dec = 0;

		int i;
		for (i = 0; buffer[i] != '\0'; i++)
		{
			len++;
		}
		int j;
		int k = len - 1;
		for (j = 0; j <= len - 1; j++, k--)
		{
			if (isdigit(buffer[j]))
			{
				int digit = buffer[j] - '0';
				dec += digit * pow(base, k);
			}
			else
			{
				int digit = toDecimal(buffer[j]);
				dec += digit * pow(base, k);
			}
		}
		printf("%d\n", dec);
	}
	fclose(file);
	return 0;
}
