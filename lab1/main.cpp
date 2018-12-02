#include <stdio.h>
#include <iostream>
#include <math.h>


#include "MyFloat.h"

using namespace std;

float nums1[2] = {0.095,  4.69};	//{ 2/22 , sqrt(22)}
float nums2[2] = {24.5643, 0.1};	//{ number, accuracy in % }
float nums3 = 0.374;
float nums4[5] = {4.3, 17.21, 8.2, 12.417, 8.37};	//{ a,b,c,m,n }
// X=(( [0]+[1] )*[2] /( [3]-[4] ))^2

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
	a1.fill_from_otn_inf(nums2[0], nums2[1]);
	cout << "Number in right digits: " << a1.number <<"\nAbsolute infelicity: "<< a1.abs_inf<<"\n\n";
//----------3)----------
	cout << "Number = 0.378 (in right digits)\n";
	a1.wipe();
	a1.fill_from_r_d_num(nums3);
	cout << "Utmost relative infelicity: " << a1.otn_inf <<"\nUtmost absolute infelicity: "<< a1.abs_inf<<"\n\n";
//----------4)----------
	cout << "Numbers: a=4.3, b=17.21, c=8.2, m=12.417, n=8.37\n( (a+b)*c/(m-n) )^2 = ?\n";
	MyFloat a3, a4, a5;
	a1.wipe();
	a2.wipe();
	
	a1.fill_from_r_d_num(nums4[0]);
	a2.fill_from_r_d_num(17.21);	//17.209999 - ????
	a3.fill_from_r_d_num(nums4[2]);
	a4.fill_from_r_d_num(nums4[3]);
	a5.fill_from_r_d_num(nums4[4]);
	//((a1+a2)*a3/(a4-a5))^2  =>  ((a1)*a3/(a4))^2
	a1.fill_from_abs_inf(a1.number + a2.number, a1.abs_inf + a2.abs_inf);
	a4.fill_from_abs_inf(a4.number - a5.number, a4.abs_inf + a5.abs_inf);	
	//((a1)*a3/(a4))^2 => (a1/a4)^2
	a1.fill_from_otn_inf(a1.number * a3.number, a1.otn_inf + a3.otn_inf);
	//(a1/a4)^2 => a1^2
	a1.fill_from_otn_inf( a1.number / a4.number, a1.otn_inf + a4.otn_inf);
	//a1^2 = a1
	a1.fill_from_otn_inf( a1.number * a1.number, a1.otn_inf + a1.otn_inf);	//1899.5123291
	std::cout << "Result: " << a1.number << "\nInfelicity: ";
	printf("%f\n", a1.abs_inf);
}
