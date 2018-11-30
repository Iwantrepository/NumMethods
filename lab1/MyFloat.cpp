#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>

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
}

int MyFloat::fill_from_otn_inf( float _otn_inf )
{
	abs_inf = number * _otn_inf / 100;
	std::string str_number = std::to_string(number);
	int first_digit, i=0;
	if(str_number[0] != '0'){
		first_digit = str_number[0] - '0';
	}else{
		while( str_number[i] != '\0' && ( str_number[i] == 0 || str_number[i] == '.' )){
			i++;
		}
		first_digit = str_number[i];
	}

	int n=0;
	float dec_buf = 1;
	while(_otn_inf/100 <= ((float)1/first_digit*dec_buf)){
		n++;
		dec_buf/=10;
	}
	i = 0;
	while(str_number[i] != '\0'){
		if(str_number[i] != '.' && n==0){
			str_number[i] = '0';
		}
		n = (n<1)? 0 : n-1;
		if(str_number[i] == '.')
			n++;
		i++;
	}
	float new_number = std::stof(str_number);
	abs_inf += abs(number - new_number);
	otn_inf = abs_inf/new_number;
	number = new_number;
}
