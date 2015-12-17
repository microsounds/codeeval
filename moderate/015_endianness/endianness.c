#include <stdio.h>

int main(void)
{
	/* copy the address of x to char y */
	/* little endian address will start with 0x01 */

	int x = 1;
	char *y = (char *) &x;
	if (*y == 1)
		printf("%s", "LittleEndian\n");
	else
		printf("%s", "BigEndian\n");
	return 0;
}
