#include <stdio.h>

int main ()
{
	/* an array with 5 elements */
	double balance[5] = {1000.0, 2.0, 3.4, 17.0, 50.0};
	double *p;
	int i;

	p = balance;

	size_t ds = sizeof(double);                                 
	size_t dps = sizeof(double*);

	printf("double size = %lu bytes\n", ds);
	printf("double pointer size = %lu bytes\n", dps);
	printf("int pointer size =%lu bytes\n", sizeof(int*));
	
	for(i = 0; i < 5; i++)
	{
		printf("p + %d address = %lld\n", i, p + i);
	}

	/* output each array element's value */
	printf( "Array values using pointer\n");
	for ( i = 0; i < 5; i++ )
	{
		printf("*(p + %d) : %f\n",  i, *(p + i) );
	}

	printf( "Array values using balance as address\n");
	for ( i = 0; i < 5; i++ )
	{
		printf("*(balance + %d) : %f\n",  i, *(balance + i) );
	}

	return 0;
}
