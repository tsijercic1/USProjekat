#pragma once
#include<wiringPi.h>

class Motor{

	int stepsPerMilimeter;
	int pinA;
	int pinB;
	int pinC;
	int pinD;
	int dir;
	int step;
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
	Motor(int pinA, int pinB, int pinC, int pinD, int stepsPerMilimeter){
		step=0;
		dir=1;
		this->pinA=pinA;
		this->pinB=pinB;
		this->pinC=pinC;
		this->pinD=pinD;
		this->stepsPerMilimeter=stepsPerMilimeter;
		wiringPiSetupPhys();//use physical numbering for pins
		pinMode(this->pinA,OUTPUT);
		pinMode(this->pinB,OUTPUT);
		pinMode(this->pinC,OUTPUT);
		pinMode(this->pinD,OUTPUT);
	}
	
	void step(int d);

	int getStepsPerMilimeter(){
		return stepsPerMilimeter;
	}

	~Motor(){
		digitalWrite(pinA,0);
		digitalWrite(pinB,0);
		digitalWrite(pinC,0);
		digitalWrite(pinD,0);
	}


};