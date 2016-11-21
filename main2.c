#include <stdlib.h>
#include <unistd.h>
int main(int argc, char** argv)
{
	char** t;
	execv("cpprof", t);
	return(EXIT_SUCCESS);
}