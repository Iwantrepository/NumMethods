#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;

int N = 7; // Вариант
double A[15][15];
double X[15] = {1.50, 1.55, 1.60, 1.65, 1.70, 1.75, 1.80, 1.85, 1.90, 1.95, 2.00, 2.05, 2.10, 2.15, 2.20};
double Y[15] = {15.152, 17.422, 20.393, 23.994, 28.160, 32.814, 37.857, 43.189, 48.689, 54.225, 59.158, 64.817, 69.550, 74.782, 79.548};

unsigned factorial (unsigned n){
    if (1==n || 0==n)
        return 1;
    else
        return n*factorial(n-1);
}

void init_A()
{
	for(int i = 0; i < 15; i++)
	{
		memset(A[i], 0, sizeof(double)*15);
	}
	memcpy(A[0], Y, sizeof(double)*15);
	
	for(int i = 1; i < 15; i++)
	{
		for(int j = 0; j < 15-i; j++)
		{
			A[i][j]=A[i-1][j+1]-A[i-1][j];
		}
	}
	
	for(int i = 1; i < 15; i++)
	{
		A[14][i] = A[14][0];
	}
	
	for(int i = 1; i < 15; i++)
	{
		for(int j = 1+i; j < 15; j++)
		{
			A[14-i][j]=A[14-i][j-1]+A[15-i][j-1];
		}
	}
	
}

void show_A()
{
	for(int i = 0; i < 15; i++)
	{
		printf("%.4f\t", X[i]);	//Эта строка выведет значения Х в таблице перед дельта У
		for(int j = 0; j < 15; j++)
		{
			printf("%.3f\t", A[j][i]);
		}
		printf("\n");
	}
}

double calculate_gauss(double x)
{
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 0; i < 15; i++)
	{
		if(fabs(x - X[i]) < mod_x)
		{
			mod_x = fabs(x - X[i]);
			nearest_idx = i;
		}
	}
	double h = fabs(X[1] - X[0]);
	double q = (x - X[nearest_idx])/h;
	int n = (nearest_idx < 15-nearest_idx)? nearest_idx : 15-nearest_idx;
	
	double result = Y[nearest_idx];
	double buf;

	
	for(int i = 1; i <= n; i++)
	{		
		//1
		buf = q+i-1;
		for(int j = 1; j < 2*i-1; j++)
		{
			buf *= (q+i-1-j);
		}
		buf/=factorial(2*i-1);
		
		buf *= A[i*2-1][nearest_idx-(i-1)];
		result += buf;
		
		//2
		buf = q+i-1;
		for(int j = 1; j < 2*i; j++)
		{
			buf *= (q+i-1-j);
		}
		buf/=factorial(2*i);
		
		buf *= A[i*2][nearest_idx-i];
		result += buf;
	}

	return result;
}

double calculate_bessel(double x)
{
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 0; i < 15; i++)
	{
		if(fabs(x - X[i]) < mod_x)
		{
			mod_x = fabs(x - X[i]);
			nearest_idx = i;
		}
	}
	double h = fabs(X[1] - X[0]);
	double q = (x - X[nearest_idx])/h;
	int n = (nearest_idx < 15-nearest_idx)? nearest_idx : 15-nearest_idx;
	
	double result = (Y[nearest_idx]+Y[nearest_idx+1])/2;
	double buf;
	
	result += (q-0.5)*A[1][nearest_idx];
	
	for(int i = 1; i <= n; i++)
	{		
		//1
		buf = q-0.5;
		for(int j = 1; j < 2*i; j++)
		{
			buf *= (q+i-1-j);
		}
		buf/=factorial(2*i+1);
		
		buf *= A[i*2+1][nearest_idx-i];
		result += buf;
		
		//2
		buf = q+i-1;
		for(int j = 1; j < 2*i; j++)
		{
			buf *= (q+i-1-j);
		}
		buf/=factorial(2*i);
		
		buf *= (A[i*2][nearest_idx-i] + A[i*2][nearest_idx-i+1])/2;
		result += buf;
	}

	return result;
}

double q_S_search (double q, int n_counter) {  /// Поиск коэффициента (q+n-1)*...*(q-n) для формулы Стирлинга
    double res = q;
    for (int i=1; i<n_counter; i++){
        res = res*(pow(q, 2) - pow(i, 2));
    }
    return res;
}

double calculate_stirling (double sought_x) {
    /// Поиск ближайшего x
    double res = 0;
    int idx_closest_x = 0;
    for (int j=0; j<15; j++){
        if (fabs(X[j]-sought_x) < fabs(X[idx_closest_x]-sought_x)) {
            idx_closest_x = j;
        }
    }

    /// Вычисление q (шаг)
    double q = 1;
    q = (sought_x-X[idx_closest_x])/(X[1]-X[0]);

    for (int i = 0, j = 0; i < 2*idx_closest_x; i++){
        double coeff;
        switch (i){
        case 0:
            coeff = 1;
            break;
        case 1:
            coeff = q;
            break;
        case 2:
            coeff = pow(q, 2);
        default:
            coeff = q_S_search(q, j)/factorial(i);
            break;
        }
        double y = 0;

        if (i%2 == 1){
            j++;
            y = (A[i][idx_closest_x-j] + A[i][idx_closest_x-j+1])/2;
        } else {
            y = A[i][idx_closest_x-j];
        }
        res += coeff*y;
    }
    return res;
}

void show_closest(double x)
{
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 0; i < 15; i++)
	{
		if(x < X[i])
		{
			printf("\n%f < %+0.1f > %f\n", Y[i-1], (x-X[i-1])/(X[1]-X[0])*200-100, Y[i]);
			printf("          %f\n\n", (x-X[i-1])/(X[1]-X[0])*(Y[i]-Y[i-1])+Y[i-1]);
			break;
		}
	}
}

bool IT (double x, double y) // interval test
{
	int nearest_idx = 0;
	double mod_x = fabs(x - X[0]);
	for(int i = 0; i < 15; i++)
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
	init_A();
	show_A();
	double x;
	
	x = 1.618;
	//show_closest(x);
	
	
	x = 1.6+0.006*N;
	printf("Gauss:    f(%.4f) = %.4f %s\n", x, calculate_gauss(x), (IT(x, calculate_gauss(x)))?"+":"-");
	x = 1.725+0.002*N;
	printf("Stirling: f(%.4f) = %.4f %s\n", x, calculate_stirling(x), (IT(x, calculate_stirling(x)))?"+":"-");
	x=1.83+0.003 * N;
	printf("Bessel:   f(%.4f) = %.4f %s\n", x, calculate_bessel(x), (IT(x, calculate_bessel(x)))?"+":"-");
	
	return 0;
}