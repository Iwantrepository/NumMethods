#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float func( float x )
{
	float res;
	res = x*x*x+0.2*x*x+0.5*x-1.2;
	return res;
}

float funcp( float x )
{
	float res;
	res = 3*x*x+0.4*x+0.5;
	return res;
}

int main(void)
{
	printf("\nf(x) = 3^3+0.2x^2+0.5x-1.2\n\n");
	
	int i = 0;
	float x = 0;
	float xn;
	float acc = 0.001;
	float acc_buf;
	printf("x%d = %f\n", i, x);
	do{
		i++;
		xn = x-(func(x))/(funcp(x));
		acc_buf = fabs(xn-x);
		printf("x%d = %f  accuracy: %f\n", i, xn, acc_buf);
		x = xn;
	}while(acc_buf > acc);
	printf("Result: f(x%d) = %f",i,func(x));
}
