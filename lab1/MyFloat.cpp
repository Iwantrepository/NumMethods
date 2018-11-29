#include <iostream>
#include <stdio.h>

#include "MyFloat.h"

MyFloat::MyFloat()
{
	number = 0;
	good_digits = 0;
	abs_inf = 0;
	otn_inf = 0;
}

void MyFloat::wipe()
{
	number = 0;
	good_digits = 0;
	abs_inf = 0;
	otn_inf = 0;
	//
}
