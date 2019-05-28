#include "motor.h"
#include <stdio.h>

void Motor::step(int d)
{
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

int Motor::getStepsPerMilimeter(){
    return stepsPerMilimeter;
}

Motor::Motor(int pinA, int pinB, int pinC, int pinD){
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
Motor::~Motor() {
    digitalWrite(pinA,0);
    digitalWrite(pinB,0);
    digitalWrite(pinC,0);
    digitalWrite(pinD,0);
}