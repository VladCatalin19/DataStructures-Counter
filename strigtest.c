#include <stdio.h>
#include <string.h>

int main ()
{
	printf ("%p\n", NULL);
	printf ("%d %d \n",strcmp ("c", "a"),strcmp ("c", "d") );
								// 1				-1
	return 0;
}