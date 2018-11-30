#include <stdio.h>
#include <iostream>
#include <math.h>


#include "MyFloat.h"

using namespace std;

float nums1[2] = {0.095,  4.69};	//{ 2/22 , sqrt(22)}
float nums2[2] = {24.5643, 0.1};	//{ number, accuracy in % }
float nums3 = 0.374;
float nums4[5] = {4.3, 17.21, 8.2, 12.417, 8.37};	//{ a,b,c,m,n }
// X=(( [0]+[1] )*[2] /( [3]-[4] ))*2

int main(void)
{
//----------1)----------
	cout << "Statements:\n1) 2/22=0.095\n2) sqrt(22)=4.69 \n";
	MyFloat a1, a2;
	a1.number = nums1[0];
	a2.number = nums1[1];
	a1.abs_inf = fabs( a1.number - ((float)2/22) );
	a2.abs_inf = fabs( a2.number - sqrt(22) );

	cout << "Accuracy: 1) " << a1.abs_inf << " 2) " << a2.abs_inf << '\n';
	cout << ((a1.abs_inf<a2.abs_inf)?"First":"Second") << " statement is more accurate.\n\n";
//----------2)----------
	cout << "Input data: number = 24.5643, relative infelicity = 0.1%\n";
	a1.wipe();
	a1.number = nums2[0];
	a1.fill_from_otn_inf(nums2[1]);
	cout << "Number in right digits: " << a1.number <<"\nAbsolute infelicity: "<< a1.abs_inf<<"\n\n";
//----------3)----------
	

	printf("\nEnd of program\n");
}
