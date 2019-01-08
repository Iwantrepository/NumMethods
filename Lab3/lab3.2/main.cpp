#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

float res[2] = {0.5, 0.5};
float resn[2];
float m = 0;
float eps = 0.001;


float f1(float x, float y)
{
	float res;
	res = tan(x*y)-x*x;
	return res;
}

float f2(float x, float y)
{
	float res;
	res = 0.8*x*x+2*y*y-1;;
	return res;
}

float f1dx(float x, float y)
{
	float res;
	res = y/(cos(x*y)*cos(x*y)) - 2*x;
	return res;
}

float f1dy(float x, float y)
{
	float res;
	res = x/(cos(x*y)*cos(x*y));
	return res;
}

float f2dx(float x, float y)
{
	float res;
	res = 1.6*x;
	return res;
}

float f2dy(float x, float y)
{
	float res;
	res = 4*y;
	return res;
}

void count_m(float x, float y)
{
	float wf1;
	float wf2;
	
	wf1 = (f1dx(x,y)*f1dx(x,y)+f1dy(x,y)*f1dy(x,y))*f1(x,y)+
	(f1dx(x,y)*f2dx(x,y)+f1dy(x,y)*f2dy(x,y))*f2(x,y);
	
	wf2 = (f1dx(x,y)*f2dx(x,y)+f1dy(x,y)*f2dy(x,y))*f1(x,y) + 
	(f2dx(x,y)*f2dx(x,y)+f2dy(x,y)*f2dy(x,y))*f2(x,y);
	
	m = (f1(x,y)*wf1+f2(x,y)*wf2)/(wf1*wf1+wf2*wf2);
}

int main()
{
	for(int i=0;;i++)
	{
		count_m(res[0], res[1]);
		
		resn[0] = res[0]-m*(f1dx(res[0],res[1])*f1(res[0],res[1])+f2dx(res[0],res[1])*f2(res[0],res[1]));
		resn[1] = res[1]-m*(f1dy(res[0],res[1])*f1(res[0],res[1])+f2dy(res[0],res[1])*f2(res[0],res[1]));
		
		float max_eps = (fabs(res[0]-resn[0])>fabs(res[1]-resn[1]))?fabs(res[0]-resn[0]):fabs(res[1]-resn[1]);
		
		res[0]=resn[0];
		res[1]=resn[1];
		
		printf("x%d = %f\ty%d = %f\t Acc: %f\n", i, res[0], i, res[1], max_eps);
		
		if(max_eps<eps)
			break;
	}
	
	printf("Result: \nf1(x,y) = %f\nf2(x,y) = %f\n\n", f1(res[0],res[1]), f2(res[0],res[1]));
	return 0;
}



