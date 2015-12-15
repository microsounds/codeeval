#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h> /* POSIX regex library */

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
	char *str = (char *) malloc(sizeof(char) * 100);
	while (fscanf(file, "%[^\n]\n", str))
	{
		unsigned len = strlen(str);
		if (len == 0) /* if empty line */
			continue;
		else
		{
			int err;
			regex_t regex; /* regex context */
			char expr[] = "^[A-Za-z0-9.+!#$%&'*-/=?^_`{|}~]+\\@[A-Za-z0-9.]+$";
			err = regcomp(&regex, expr, REG_EXTENDED); /* compile regex */
			if (err)
			{
				printf("invalid regex\n");
				return 0;
			}
			err = regexec(&regex, str, 0, NULL, 0);
			char *override = strstr(str, ".@."); /* edge case */
			if (err == REG_NOMATCH && !override)
				printf("%s\n", "false");
			else
				printf("%s\n", "true");
			regfree(&regex);
		}
		if (feof(file))
			break;
	}
	free(str);
	fclose(file);
	return 0;
}

