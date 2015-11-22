#include <stdio.h>
#include <ctype.h>

/* this version is too codegolf-y for my taste */

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
		if (iscntrl(c)) /* reset case pattern on newline */
			mode = 1;
		printf("%c", ((mode) ? toupper(c) : tolower(c)));
		if (isalpha(c))
			modeSwitch(&mode);
	}
	fclose(file);
	return 0;
}
