#include <stdio.h>

void modeSwitch(int *m)
{
	*m = (*m) ? 0 : 1;
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
	int mode = 1; /* 1 = ucase; 0 = lcase */
	char c;
	while ((c = fgetc(file)) && !feof(file))
	{
		if (c == '\n') /* reset case pattern on newline */
			mode = 1;

		if (mode)
		{
			if (c >= 'a' && c <= 'z')
			{
				printf("%c", c - 32);
				modeSwitch(&mode);
			}
			else if (c >= 'A' && c <= 'Z')
			{
				printf("%c", c);
				modeSwitch(&mode);
			}
			else
				printf("%c", c);
		}
		else
		{
			if (c >= 'A' && c <= 'Z')
			{
				printf("%c", c + 32);
				modeSwitch(&mode);
			}
			else if (c >= 'a' && c <= 'z')
			{
				printf("%c", c);
				modeSwitch(&mode);
			}
			else
				printf("%c", c);
		}
	}
	fclose(file);
	return 0;
}
