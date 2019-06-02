#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>

using namespace std;

double f1(double x)
{
    return 1/(3*x*x-1);
}

double fTrap()
{
    double a = 1.4;
    double b = 2.1;
    int n = 66;
    double h = (b-a)/n;
    double result = 0;

    for (int i = 0; i < n; i++)
    {
        result += h*(f1(a + i*h) + f1(a + (i+1)*h))/2;
    }
    return result;
}

double f2(double x)
{
    return (log10(x*x+1))/x;
}

double fSimp(int k)
{
    double a = 0.8;
    double b = 1.6;
    int n = k;
    double h = (b-a)/n;
    double result = 0;

    for (int i = 1; i < n; i++)
    {
        switch (i%2)
        {
            case 0:
                result += 2*f2(a + i*h);
            break;
            case 1:
                result += 4*f2(a + i*h);
            break;
        }
    }
    result += f2(a) + f2(b);
    result *= h/3;
    return result;
}

double f3(double x)
{
    return sqrt(x*x+1)/(x+2);
}

double fGaussa4()
{
    double x[4];
    x[0] = -0.861136; x[1] = -0.339981;
    x[2] = 0.339981;  x[3] = 0.861136;
    double a = 0.2;
    double b = 2.4;
    double result = 0;

    for (int i = 0; i < 4; i++)
    {
        x[i] = (a+b)/2 + (b-a)/2*x[i];
    }

    return (0.34785*(f3(x[0]) + f3(x[3])) + 0.65215*(f3(x[1]) + f3(x[2])));
}

double fGaussa5()
{
    double x[5];
    x[0] = -0.90618; x[1] = -0.53847; x[2] = 0;
    x[3] = 0.53847;  x[4] = 0.90618;
    double a = 0.2;
    double b = 2.4;
    double result = 0;

    for (int i = 0; i < 5; i++)
    {
        x[i] = (a+b)/2 + (b-a)/2*x[i];
    }

    return (0.236927*(f3(x[0]) + f3(x[4])) + 0.478629*(f3(x[1]) + f3(x[3])) + 0.568889*f3(x[2]));
}

int main()
{
    cout << endl;
    cout << "dx/(3x^2-1) from 1.4 to 2.1 [trapezium]" << endl;
    cout << fTrap() << endl;

    cout << endl;

    cout << "lg(x^2+1)dx/x from 0.8 to 1.6 [Simpson]" << endl;
    cout << fSimp(8) << endl;
    cout << "R = ";
    cout << (fSimp(8) - fSimp(4))/15 << endl;

    cout << endl;

    cout << "sqrt(x^2+1)dx/(x+2)  from 0.2 to 2.4 [Gauss]" << endl;
    cout << "n = 4" << endl;
    printf("%.6f\n", fGaussa4());
    cout << "n = 5" << endl;
    printf("%.6f\n", fGaussa5());

    return 0;
}


