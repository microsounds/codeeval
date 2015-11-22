#include <stdio.h>

void slang(void)
{
	static int sel = 0;
	static const char *slang[] = {
		", yeah!",
		", this is crazy, I tell ya.",
		", can U believe this?",
		", eh?",
		", aw yea.",
		", yo.",
		"? No way!",
		". Awesome!"
	 };

	if (sel > 7) /* reset */
		sel = 0;
	printf("%s", slang[sel]);
	sel++;
}

void flip(int *s)
{
	*s = !(*s);
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
	char c;
	int state = 0;
	int *s = &state;
	while ((c = fgetc(file)) && !feof(file))
	{
		if (c == '.' || c == '!' || c == '?')
		{
			if (*s)
				slang();
			else
				putchar(c);
			flip(s);
		}
		else
			putchar(c);
	}
	fclose(file);
	return 0;
}
