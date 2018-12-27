#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

using namespace std;

double First(double x1, double x2)
{
	return sin(x1-1)-1.3+x2;
}

double Second(double x1, double x2)
{
	return x1-sin(x2+1)-0.8;
}


double derX1First(double x1, double x2)
{
	return cos(1-x1);
}

double derX2First(double x1, double x2)
{
	return 1;
}

double derX1Second(double x1)
{
	return 1;
}

double derX2Second(double x2)
{
	return -cos(x2+1);
}

int main()
{
	cout << "\nf(x1) = sin(x-1)-1.3+y\nf(x2) = x-sin(y+1)-0.8" << endl << endl;

	const int SIZE = 2;

	long double vec[SIZE];
	vec[0] = 2;
	vec[1] = 0.5;

	double matrix[SIZE][SIZE];

	cout.setf(ios::fixed);
	cout.precision(5);

	matrix[0][0] = derX1First(vec[0], vec[1]);
	matrix[0][1] = derX2First(vec[0], vec[1]);
	matrix[1][0] = derX1Second(vec[0]);
	matrix[1][1] = derX2Second(vec[1]);

	cout << "W(x0)" << endl;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << setw(7) << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;

	double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	cout << "DetW(x0): " << det << endl;

	double temp1 = matrix[0][0];
	matrix[0][0] = matrix[1][1];
	matrix[1][1] = temp1;

	matrix[0][1] = -matrix[0][1];
	matrix[1][0] = -matrix[1][0];

	for (int i = 0; i < SIZE; ++i)
	for (int j = 0; j < SIZE; ++j)
	{
		matrix[i][j] = (1 / det)*matrix[i][j];
	}

	cout << endl;

	cout << "(W(x0))^-1" << endl;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cout << setw(7) << matrix[i][j] << " ";
		}
		cout << endl;
	}

	double F[2];

	F[0] = First(vec[0], vec[1]);
	F[1] = Second(vec[0], vec[1]);

	cout << endl << endl;

	double iterArr[100][SIZE];

	for (int i = 0; i < 100; ++i)
	for (int j = 0; j < SIZE; ++j)
	{
		iterArr[i][j] = 0;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		iterArr[0][i] = vec[i];
	}

	cout << "N " << "X1\t  " << "X2\t  " << "Acc" << endl;
	cout << "0 " << iterArr[0][0] << " " << iterArr[0][1] << endl;

	int n = 0;
	double max = 0;
	for (int c = 1;; c++)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				iterArr[c][i] += matrix[i][j] * F[j];
			}
			iterArr[c][i] = iterArr[c - 1][i] - iterArr[c][i];

			vec[i] = iterArr[c][i];

			double k = fabs(iterArr[c][i] - iterArr[c - 1][i]);
			if (k > max) max = k;
			if (i == 0) cout << c << " ";
			cout << setw(6) << iterArr[c][i] << " ";
		}

		F[n] = First(vec[0], vec[1]);
		F[++n] = Second(vec[0], vec[1]);
		n = 0;

		cout << setw(6) << max;
		if (max < 0.001)
		{
			cout << "\n\nResult: " << endl;
			cout << "f(x1) = " << First(vec[0], vec[1]) << endl;
			cout << "f(x2) = " << Second(vec[0], vec[1]) << endl;
			break;
		}
		else max = 0;
		cout << endl;
	}
	return 0;
}



