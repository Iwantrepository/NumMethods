#ifndef	MY_FLOAT_H
#define MY_FLOAT_H

class MyFloat{
public:
	float	number;
	int	good_digits;
	float	abs_inf;	//infelicity
	float	otn_inf;	//infelicity

	void wipe();
	int fill_from_otn_inf( float _number, float _otn_inf);
	int fill_from_abs_inf( float _number, float _abs_inf);
	int fill_from_r_d_num( float _number);	//fill from right digit number

	MyFloat();
	~MyFloat(){};
};

#endif
