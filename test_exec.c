#include <stdlib.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	int x;
	x=atoi(argv[1]);
	x++;
	printf("%i\n",x);
	exit(EXIT_SUCCESS);
}