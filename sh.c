#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *x = malloc(5 * sizeof(char));

	x[0] = 'S';
	x[1] = 'h';
	x[2] = 'a';
	x[3] = 'u';
	x[4] = 'n';

	printf("%c\n", x[1, 3]);
}