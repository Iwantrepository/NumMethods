#ifndef	MY_FLOAT_H
#define MY_FLOAT_H

class MyFloat{
public:
	float	number;
	int	good_digits;
	float	abs_inf;	//infelicity
	float	otn_inf;	//infelicity

	void wipe();

	MyFloat();
	~MyFloat(){};
};

#endif
