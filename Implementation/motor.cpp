#include "motor.h"
#include <stdio.h>

void Motor::step(int d)
{
	if(d>0)dir=1;
	else dir=-1;
	_step+=dir;
	if(_step<0)_step=7;
	else _step = _step % 8;
	digitalWrite(pinA,sequence[_step][0]);
	digitalWrite(pinB,sequence[_step][1]);
	digitalWrite(pinC,sequence[_step][2]);
	digitalWrite(pinD,sequence[_step][3]);
}
