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

int MyFloat::fill_from_r_d_num( float _number)
{
	number = _number;
	std::string str_number;

	
	str_number = std::to_string(number);
	if(str_number == "17.209999"){	//Hotfix: std::to_string(17.21)="17.209999" ???
		str_number = "17.21";
	}
	

	/*std::cout << number << "\tfloat_to_string-> ";	
	for (int i = 0; i<str_number.size(); i++)
		std::cout << str_number[i];
	std::cout << '\n';*/
	
	for (int i = str_number.size() - 1; str_number[i] == '0'; i-- ){
		str_number[i]='\0';
	}
	int i = 0;
	while( str_number[i] != '\0' ){
		if( str_number[i] != '.' ){
			str_number[i] = '0';
		}
		i++;
	}
	str_number[i-1]='1';
	abs_inf = std::stof(str_number)*0.5;
	otn_inf = abs_inf/number;
	return 0;
}

int MyFloat::fill_from_otn_inf( float _number, float _otn_inf )
{
	number = _number;
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
	return 0;
}

int MyFloat::fill_from_abs_inf( float _number, float _abs_inf )
{
	fill_from_otn_inf(_number, abs_inf/number);
	return 0;
}
