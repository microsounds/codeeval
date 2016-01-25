#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum _global { MAX_BUF = 1000 };

char *rewrite_str(char *str)
{
	unsigned len = strlen(str);
	char *out = (char *) malloc(sizeof(char) * len + 1);
	unsigned i;
	unsigned j = 0; /* output index */
	for (i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			out[j++] = str[i];
	}
	out[j] = '\0'; /* null terminate */
	return out;
}

int sum_of_digits(int n)
{
	int sum = 0;
	while (n > 0)
	{
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int to_digit(const char c)
{
	return (int) c - '0';
}

unsigned validate_str(char *str)
{
	/* Luhn algorithm */
	/* https://en.wikipedia.org/wiki/Luhn_algorithm
	 *
	 * Double every other digit from right to left excluding the check digit.
	 * If result is greater than 9, obtain sum of digits.
	 * Number is valid if sum of all resultant numbers + the check digit
	 * is divisible by 10.
	 */
	unsigned len = strlen(str);
	int sums[len];
	int i;
	for (i = len - 2; i >= 0; i -= 2)
	{
		int sum = to_digit(str[i]) * 2;
		if (sum > 9)
			sum = sum_of_digits(sum);
		sums[i] = sum;
		if (i != 0) /* ignore every other digit */
			sums[i-1] = to_digit(str[i-1]);
	}
	int sum_of_all = 0;
	for (i = 0; i < len; i++)
	{
		if (i == len - 1)
			sum_of_all += to_digit(str[len - 1]); /* check digit */
		else
			sum_of_all += sums[i];
	}
	if (sum_of_all % 10 == 0)
		return 1;
	else
		return 0;
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
	char *buf = (char *) calloc(MAX_BUF, sizeof(char));
	while (fscanf(file, "%[^\n]\n", buf))
	{
		char *str = rewrite_str(buf);
		printf("%c\n", (validate_str(str)) ? '1' : '0');
		free(str);
		if (feof(file))
			break;
	}
	free(buf);
	fclose(file);
	return 0;
}
