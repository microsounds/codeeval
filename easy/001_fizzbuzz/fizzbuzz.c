#include <stdio.h>

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
	else
	{
		int x, y, n;
		while (fscanf(file, "%d %d %d", &x, &y, &n) && !feof(file))
		{
			int i;
			for (i = 1; i <= n; i++)
			{
				if ((i % x == 0) && (i % y == 0))
					printf("%s", "FB");
				else if (i % x == 0)
					printf("%s", "F");
				else if (i % y == 0)
					printf("%s", "B");
				else
					printf("%d", i);

				if (i < n) /* formatting */
					printf(" ");
				if (i == n)
					printf("\n");
			}
		}
		fclose(file);
		return 0;
	}
}
