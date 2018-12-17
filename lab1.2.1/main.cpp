#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

float polynom( float x )
{
	float res;
	res = x - (x*x*x - 0.2*x*x +0.4*x -1.4)/7.3;
	return res;
}

int main(void)
{
	printf("\nf(x) = x^3 - 0.2x^2 + 0.4x -1.4\n\n");
	
	int i = 0;
	float x = 1;
	float xn;
	float acc = 0.001;
	float acc_buf;
	printf("x%d = %f\n", i, x);
	do{
		i++;
		xn = polynom(x);
		acc_buf = abs(xn-x);
		printf("x%d = %f  accuracy: %f\n", i, xn, acc_buf);
		x = xn;
	}while(acc_buf > acc);
	printf("Result: f(x%d) = %f",i,(x*x*x - 0.2*x*x +0.4*x -1.4));
}