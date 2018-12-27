#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float polynom( float x )
{
	float res;
	res = x -(x*exp(x)-exp(2))/13.8;
	return res;
}

int main(void)
{
	printf("\nf(x) = ln(x) - 2 + x\n\n");
	
	int i = 0;
	float x = 1;
	float xn;
	float acc = 0.001;
	float acc_buf;
	printf("x%d = %f\n", i, x);
	do{
		i++;
		xn = polynom(x);
		acc_buf = fabs(xn-x);
		printf("x%d = %f  accuracy: %f\n", i, xn, acc_buf);
		x = xn;
	}while(acc_buf > acc);
	printf("Result: f(x%d) = %f",i,(log(x)-2+x));
}
