#include<wiringPi.h>
#include "motor.h"

int main(){

	Motor motor(7,11,13,15);
	for(int i = 0;i<4096;i++){
		motor.write(-1);
		delayMicroseconds(680);
	}//moves the motor one full cycle in one direction
	
	for(int i = 0;i<4096;i++){
		motor.write(1);
		delayMicroseconds(680);
	}//moves the motor one full cycle in other direction
	for(int i = 0;i<4096;i++){
		motor.write(-1);
		delayMicroseconds(680);
	}
	for(int i = 0;i<4096;i++){
		motor.write(1);
		delayMicroseconds(680);
	}
	
}
