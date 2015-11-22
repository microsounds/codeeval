#include <stdio.h>

int isPrime(int num)
{
    num = abs(num);
    if (num == 1) /* 1 can't be prime */
        return 0;
    int i;
    for (i = 2; i < num; i++)
    {
        if (num % i == 0 && i != num)
            return 0;
    }
    return 1;
}

int main()
{
	int i;
	int primecount = 0;
	int sumofprimes = 0;
	for (i = 1; primecount < 1000; i++)
	{
		if (isPrime(i))
		{
			sumofprimes += i;
			primecount++;
		}
	}
	printf("%d\n", sumofprimes);
	return 0;
}
