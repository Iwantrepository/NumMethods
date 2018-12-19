#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float func( float x )
{
	float res;
	res = 2*x*x*x+9*x*x-21;
	return res;
}

float funcp( float x )
{
	float res;
	res = 6*x*x+18*x;
	return res;
}

int main(void)
{
	printf("\nf(x) = 2x^3 + 9x^2 - 21\n\n");
	
	int i = 0;
	float a = 1, b = 2;
	float an, bn;
	float acc = 0.001;
	float acc_buf;
	printf("a%d = %f\n", i, a);
	do{
		i++;
		an = a - (func(a))*(b-a)/(func(b)-func(a));
		bn = b - (func(b))/(funcp(b));
		acc_buf = fabs(an-bn);
		printf("a%d = %f b%d = %f  accuracy: %f\n", i, an, i, bn, acc_buf);
		a = an;
		b = bn;
	}while(acc_buf > acc);
	printf("Result: f(a%d) = %f",i,func(a));
}
