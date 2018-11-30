#ifndef	MY_FLOAT_H
#define MY_FLOAT_H

class MyFloat{
public:
	float	number;
	int	good_digits;
	float	abs_inf;	//infelicity
	float	otn_inf;	//infelicity

	void wipe();
	int fill_from_otn_inf( float _otn_inf);

	MyFloat();
	~MyFloat(){};
};

#endif
