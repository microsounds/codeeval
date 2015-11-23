#include <stdio.h>
#include <math.h>

void force_suffix(FILE *fp, char insert)
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

int is_prime(unsigned num)
{
	/* if num >= 2 && num is not divisible by
	   any number other than itself up to
	   a ceiling of sqrt(num) */

    num = abs(num);
    unsigned sq = sqrt(num);

    if (num < 2)
        return 0;
    unsigned i;
    for (i = 2; i <= sq; i++)
    {
        if (num % i == 0 && i != num)
            return 0;
    }
    return 1;
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
	unsigned n;
	while (fscanf(file, "%u", &n) && !feof(file))
	{
		/* find first prime and print
		   every subsequent prime will be preceded with ',' */

		unsigned i;
		int nf = 0; /* "not first" flag */
		for (i = 0; i < n; i++)
		{
			if (is_prime(i))
			{
				if (nf)
				{
	 				printf("%c%u", ',', i);
	 			}
	 			else
	 			{
					nf = !nf; /* blow nf bolt */
					printf("%u", i);
	 			}
			}
		}
		printf("%c", '\n');
	}
	fclose(file);
	return 0;
}
