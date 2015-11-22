#include <stdio.h>

int main()
{
	int x, y;
	for (y = 1; y <= 12; y++)
	{
		for (x = 1; x <= 12; x++)
		{
			if (x == 1)
				printf("%d", x * y);
			else
				printf("%4d", x * y);
			if (x == 12)
				printf("\n");
		}
	}
	return 0;
}
