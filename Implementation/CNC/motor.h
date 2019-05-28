#pragma once
#include<wiringPi.h>

class Motor{
	int stepsPerMilimeter;
	int pinA;
	int pinB;
	int pinC;
	int pinD;
	int dir;
	int _step;
	const int sequence[8][4]{
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,1},
		{0,0,0,1},
		{1,0,0,1}
	};
public:
	Motor(int pinA, int pinB, int pinC, int pinD);
	
	void step(int d);

	int getStepsPerMilimeter();

	~Motor();


};
