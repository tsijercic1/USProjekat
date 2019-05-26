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
	Motor(int pinA, int pinB, int pinC, int pinD){
		_step=0;
		dir=1;
		this->pinA=pinA;
		this->pinB=pinB;
		this->pinC=pinC;
		this->pinD=pinD;
		// Use physical numbering for pins
		wiringPiSetupPhys();
		pinMode(this->pinA,OUTPUT);
		pinMode(this->pinB,OUTPUT);
		pinMode(this->pinC,OUTPUT);
		pinMode(this->pinD,OUTPUT);
	}
	
	void step(int d) {
		if(d<=0)dir=1;
		else dir=-1;
		_step+=dir;
		if(_step<0)_step=7;
		else _step = _step % 8;
		digitalWrite(pinA,sequence[_step][0]);
		digitalWrite(pinB,sequence[_step][1]);
		digitalWrite(pinC,sequence[_step][2]);
		digitalWrite(pinD,sequence[_step][3]);
	}
<<<<<<< HEAD
	
=======

	int getStepsPerMilimeter(){
		return stepsPerMilimeter;
	}

>>>>>>> 34a2f75c1f91673e5ca0a1a70b5422c7396b9a14
	~Motor(){
		digitalWrite(pinA,0);
		digitalWrite(pinB,0);
		digitalWrite(pinC,0);
		digitalWrite(pinD,0);
	}


};
