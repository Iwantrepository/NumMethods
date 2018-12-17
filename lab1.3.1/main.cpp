#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

float func( float x )
{
	float res;
	res = 3*x-cos(x)-1;
	return res;
}

int main(void)
{
	printf("\nf(x) = 3x - cos(x) - 1\n\n");
	
	int i = 0;
	float x = 0;
	float xn;
	float acc = 0.001;
	float acc_buf;
	printf("x%d = %f\n", i, x);
	do{
		i++;
		xn = x-(x-1)*(func(x))/(func(x)-func(1));
		acc_buf = abs(xn-x);
		printf("x%d = %f  accuracy: %f\n", i, xn, acc_buf);
		x = xn;
	}while(acc_buf > acc);
	printf("Result: f(x%d) = %f",i,func(x));
}
