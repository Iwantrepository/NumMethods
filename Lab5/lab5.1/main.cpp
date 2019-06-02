#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;

double X[] = {2.4, 2.6, 2.8, 3, 3.2, 3.4, 3.6, 3.8, 4, 4.2, 4.4, 4.6};
double Y[] = {3.526 ,3.782, 3.945, 4.043, 4.104, 4.155, 4.222, 4.331, 4.507 ,4.775, 5.159, 5.683};

unsigned factorial (unsigned n){
    if (1==n || 0==n)
        return 1;
    else
        return n*factorial(n-1);
}

double C_nk(int n, int k)
{
    return factorial(n)/(factorial(k)*(factorial(n-k)));
}

double F_r(int i, int n, double *mas)
{
    double result = 0;
    for (int j = 0; j <= n; j++){
        result += pow(-1,j)*C_nk(n,j)*mas[i+n-j];
    }
    return result;
}

double q_d1(double q, int n)
{
    double buf1 = 0;
    double buf2 = 1;

    for (int i = 0; i <= n; i++)
    {
        buf2 = 1;
        for (int j = 0; j <= n; j++)
            if (i != j)
                buf2 *= (q-j);
        buf1 += buf2;
    }
    return buf1;
}

double Newton_d1(double x, double n, double *mas)
{
    double h = X[1] - X[0];
    double q = (x - X[0])/h;
    double result = 0;

    for (int i = 0; i < n; i++){
        double cur;
        cur = q_d1(q,i) * F_r(0, i+1, mas)/factorial(i+1);
        result += cur;
    }
    result /= h;
    return result;
}

double q_d2(double q, int n)
{
    double buf1 = 0;
    double buf2 = 1;

    int val = factorial(n)/(2*factorial(n-2));
    for (int i = 0; i < val; i++)
    {
        buf2 = 1;
        int m = i/n + 1;
        for (int j = 0; j < n-2; j++){
                buf2 *= (q-(m*j + i)%n);
        }
        buf1 += buf2;
    }
    return buf1;
}

double Newton_d2(double x, int n, double *mas)
{
    double h = X[1] - X[0];
    double q = (x - X[0])/h;
    double result = 0;

    for (int i = 2; i <= n; i++){
        double cur;
        cur = 2*q_d2(q,i) * F_r(0, i, mas)/factorial(i);
        result += cur;
    }
    result /= pow(h,2);
    return result;
}


double new_f_q(int j, double q, int k)
{
    double cur = 1;
    for (int i = j; i < k; i++)
        cur *= (pow(q, 2) - pow(i ,2));
    return cur;
}

double Stirling(double x, int n, double* mas)
{
    n = (n-1)/2;
    double q = (x - X[n])/(X[1] - X[0]);
    double y = 0;
    for (int k = 0; k <= n; k++)
    {
        y += new_f_q(0, q,k) * F_r(n-k, 2*k, mas) / factorial(2*k);
        if (k != n)
            y += q * new_f_q(1, q, k+1) * (F_r(n-k-1, 2*k+1, mas) + F_r(n-k, 2*k+1, mas))/(2* factorial(2*k+1));
    }
    return y;
}

double Stirling_d1(int k, int n, double* mas, double h)
{
    double result = 0;
    n = (n-1)/2;
    for (int i = 0; i < n; i++){
        result += new_f_q(1,0,i+1)*(F_r(k-i-1,2*i+1,mas) + F_r(k-i, 2*i+1, mas))/(2*factorial(2*i+1));
    }
    result /= h;
    return result;
}


double Stirling_d2(int k, int n, double* mas, double h)
{
    double result = 0;
    n = (n-1)/2;
    for (int i = 1; i <= n; i++){
        result += 2*new_f_q(1,0,i)*F_r(k-i,2*i,mas)/factorial(2*i);
    }
    result /= pow(h,2);
    return result;
}


double Lagrange_d1(double x, int n, double *masx, double *masy)
{
    double result = 0;
    double buf1, buf2;
    for (int i = 0; i < n; i++)
    {
        buf1 = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                buf2 = 1;
                for (int k = 0; k < n; k++)
                {
                    if (k != i && k!= j)
                        buf2 *= (x-masx[k])/(masx[i]-masx[k]);
                }
                buf1 += buf2/(masx[i] - masx[j]);
            }
        }
        result += masy[i]*buf1;
    }
    return result;
}

double Lagrange_d2(double x, int n, double *masx, double *masy)
{
    double result = 0;
    double buf1, buf2, buf3;
    for (int i = 0; i < n; i++)
    {
        buf1 = 0;
        for (int j = 0; j < n; j++)
        {

            if (i != j)
            {
                buf2 = 0;
                for (int l = 0; l < n; l++)
                {
                    if (i != l && l != j)
                    {
                        buf3 = 1;
                        for (int k = 0; k < n; k++)
                        {
                            if (k != i && k != j && k != l)
                                buf3 *= (x-masx[k])/(masx[i]-masx[k]);
                        }
                        buf2 += buf3/(masx[i] - masx[l]);
                    }
                }
                buf1 += buf2/(masx[i] - masx[j]);
            }
        }
        result += masy[i]*buf1;
    }
    return result;
}

int main()
{
    cout << "Newton" << endl;
    int n = sizeof(X)/sizeof(double);
    for (int i = 1; i <= 12; i+=2)
    {
        double x = 3.32 + 0.02*i;
        printf("f'(%.2f) = %f\n",x , Newton_d1(x,n,Y));
    }

    cout << "---" << endl;
    for (int i = 1; i <=12; i+=2)
    {
        double x = 3.32 + 0.02*i;
        printf("f''(%.2f) = %f\n",x , Newton_d2(x,n,Y));
    }

    cout << "\nStirling"  << endl;
	n = sizeof(X)/sizeof(double);
    double Stirling_dx[21];
    double Stirling_dy[21];
    for (int i = 1; i <= 11; i++)
    {
        Stirling_dx[i] = 3.82 + 0.02*i;
        Stirling_dy[i] = Stirling(Stirling_dx[i], n, Y);
    }
    double h = Stirling_dx[1] - Stirling_dx[0];
    for (int i = 1; i <= 11; i+=2)
    {
        printf("f'(%.2f) = %f\n", Stirling_dx[i], Stirling_d1(i, n, Stirling_dy, h));
    }

    cout << "---" << endl;
    for (int i = 1; i <= 11; i+=2)
    {
        printf("f''(%.2f) = %f\n", Stirling_dx[i], Stirling_d2(i, n, Stirling_dy, h));
    }

    cout << "\nLagrange" << endl;
    n = sizeof(X)/sizeof(double);
    for (int i = 1; i <= 11; i+=2)
    {
        double x = 4.32 + 0.02*i;
        printf("f'(%.2f) = %f\n", x, Lagrange_d1(x,n, X, Y));
    }

    cout << "---" << endl;
    for (int i = 1; i<=11; i+=2)
    {
        double x = 4.32 + 0.02*i;
        printf("f''(%.2f) = %f\n", x, Lagrange_d2(x,n, X, Y));
    }

    return 0;
}


