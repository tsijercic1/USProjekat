#include<wiringPi.h>
#include "CNC/motor.h"

constexpr double stepsPermm = 4096*2.0;

int main(){

	
	for(int i = 0;i<4096;i++){
		motor.step(1);
		delayMicroseconds(680);
	}//moves the motor one full cycle in other direction
	for(int i = 0;i<4096;i++){
		motor.step(-1);
		delayMicroseconds(680);
	}
	for(int i = 0;i<4096;i++){
		motor.step(1);
		delayMicroseconds(680);
	}
	
}
