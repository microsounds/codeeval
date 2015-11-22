#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("%s %s\n", argv[0], "filename");
		return 0;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Could not open file.\n");
		return 1;
	}
	char buffer[80];
	while(fscanf(file, "%s", buffer) && !feof(file))
	{
		int i;
		int total = 0;
		for (i = 0; buffer[i] != '\0'; i++)
		{
			/* '9' = 39, '0' = 30, therefore '9' - '0' = integer 9 */
			total += buffer[i] - '0';
		}
		printf("%d\n", total);
	}
	fclose(file);
	return 0;
}
