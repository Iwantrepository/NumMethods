#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int m = 5;
int i, j, n;

float matrix[4][5] = {
	{ 4, 2, -1, 0.5, -9},
	{ 1, -5, 2, 1, -10},
	{ 2, 1, -4, -1.5, -1},
	{ 1, -0.4, 0.8, -3, -4.2}
};

void cat_mat()
{
	for (i=0; i<n; i++)
	{
		for (j=0; j<m; j++)
			printf("%s%.1f\t", (j==4)?"| ":"", matrix[i][j]);
		cout << endl;
	}
	cout << endl;
}

int main()
{
	n = m-1;
	cat_mat();

//	forward move

	float  tmp, res[m];
	int k;
	for (i=0; i<n; i++)
	{
		tmp=matrix[i][i];
		for (j=n;j>=i;j--)
			matrix[i][j]/=tmp;
			for (j=i+1;j<n;j++)
			{
				tmp=matrix[j][i];
				for (k=n;k>=i;k--)
					matrix[j][k]-=tmp*matrix[i][k];
			}
	}
	
//	reverse move

	res[n-1] = matrix[n-1][n];
	for (i=n-2; i>=0; i--)
	{
		res[i] = matrix[i][n];
		for (j=i+1;j<n;j++) 
			res[i]-=matrix[i][j]*res[j];
	}

//	result out

	for (i=0; i<n; i++)
		printf("x%d = %.1f\n",i+1, res[i]);

	return 0;
}
