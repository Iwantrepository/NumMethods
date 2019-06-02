#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;

double A[13][13];
double X[13] = {0.101, 0.106, 0.111, 0.116, 0.121, 0.126, 0.131, 0.136, 0.141, 0.146, 0.151, 0.156, 0.161};
double Y[13] = {1.26183, 1.27644, 1.29122, 1.30617, 1.32130, 1.33660, 1.35207, 1.36773, 1.38357, 1.39959, 1.41579, 1.42683, 1.43356};

void init_A()
{
	for(int i = 0; i < 13; i++)
	{
		memset(A[i], 0, sizeof(double)*13);
	}
	memcpy(A[0], Y, sizeof(double)*13);
	
	for(int i = 1; i < 13; i++)
	{
		for(int j = 0; j < 13-i; j++)
		{
			A[i][j]=A[i-1][j+1]-A[i-1][j];
		}
	}
	
	for(int i = 1; i < 13; i++)
	{
		A[12][i] = A[12][0];
	}
	
	for(int i = 1; i < 13; i++)
	{
		for(int j = 1+i; j < 13; j++)
		{
			A[12-i][j]=A[12-i][j-1]+A[13-i][j-1];
		}
	}
}

void show_A()
{
	for(int i = 0; i < 13; i++)
	{
		printf("%.4f\t", X[i]);	//Эта строка выведет значения Х в таблице перед дельта У
		for(int j = 0; j < 13; j++)
		{
			printf("%.6f\t", A[j][i]);
		}
		printf("\n");
	}
}

double calculate_for(double x)
{
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 0; i < 13; i++)
	{
		if(fabs(x - X[i]) < mod_x)
		{
			mod_x = fabs(x - X[i]);
			nearest_idx = i;
		}
	}
	double h = X[1] - X[0];
	double q = (x - X[nearest_idx])/h;
	printf("%.4f\t", x);
	
	double result = Y[nearest_idx];
	double buf;
	for(int i = 1; i < 13; i++)
	{
		buf = q;
		for(int j = 1; j < i; j++)
		{
			buf *= (q-j);
		}
		for(int j = 1; j < i; j++)
		{
			buf /= i;
		}
		buf*=A[nearest_idx][i];
		
		result += buf;
	}
	printf("%.6f ", result);
	
	printf("\n");
}

int main()
{
	init_A();
	show_A();
	printf("\n   X\t  f(x)\n");
	for(int i = 1; i < 31; i++)
	{
		calculate_for(0.1026+0.002*i);
	}
	return 0;
}