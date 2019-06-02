#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;

int N = 7;

double X[9] = {0.593, 0.598, 0.605, 0.613, 0.619, 0.627, 0.632, 0.64, 0.65};
double Y[9] = {0.53205, 0.535625, 0.540598, 0.546235, 0.550431, 0.555983, 0.559428, 0.568738, 0.575298};

//double X[4] = {0, 2.5069, 5.0154, 7.5227};
//double Y[4] = {0.3989423, 0.3988169, 0.3984408, 0.3978138};

double razn (int f, int l)
{
	if( l-f == 1 )
	{	
		return (Y[l]-Y[f])/(X[l]-X[f]);
	}else
	{
		return (razn(f+1, l)-razn(f, l-1))/(X[l]-X[0]);
	}
}

double newton (double x)
{
	double res = Y[0];
	double buf;
	int num_of_parts = 8;
	for(int i = 1; i <= num_of_parts; i++)
	{
		buf = razn(0, i);
		for(int j = 0; j < i; j++)
		{
			buf *= x-X[j];
		}
		res += buf;
	}
	return res;
}

double lagrange (double x)
{
	double res = 0;
	double buf;
	int num_of_parts = 9;
	
	for(int i = 0; i < num_of_parts; i++)
	{
		buf = Y[i];
		for(int j = 0; j < num_of_parts; j++)
		{
			if(j != i)
			{
				buf *= x-X[j];
				buf /= X[i]-X[j];
			}
		}
		res += buf;
	}
	return res;
}

bool IT (double x, double y) // interval test
{
	if( (x < X[0]) || (x > X[8]) )
		return false;
	
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 1; i < 9; i++)
	{
		if(x < X[i])
		{
			if((y < Y[i])&&(y>Y[i-1]))
				return true;
			else
				return false;
			break;
		}
	}
}

int main()
{
	double x;
	printf("-----Newton-----\n");
	for(int i = 3; i < 2*N; i++)	//Newton
	{
		x = 0.608 + 0.005 * i;
		printf("%f -> %f %s\n", x, newton(x), (IT(x, newton(x)))?" ":"" );
	}
	
	printf("-----Lagrange-----\n");
	
	for(int i = N; i < 3*N; i++)	//Lagrange
	{
		x = 0.650 - 0.005 * i;
		printf("%f -> %f %s\n", x, lagrange(x), (IT(x, lagrange(x)))?" ":"");
	}
	
	/*
	for(int i = 0; i < 20; i++)
	{
		x = 0.6 + 0.0025 *i;
		printf("%f -> %f %s\n", x, newton(x), (IT(x, newton(x)))?"+":"--" );
		printf("%f -> %f %s\n", x, lagrange(x), (IT(x, lagrange(x)))?"+":"--");
	}
	*/
	return 0;
}