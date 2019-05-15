#include "motor.h"
#include <stdio.h>
void Motor::write(int d)
{
		static int cycle = 0;
		if(d>0)dir=1;
		else dir=-1;
		step+=dir;
		if(step<0)step=7;
		else step = step % 8;
		if(step==0)printf("%d\n",cycle++);
		digitalWrite(pinA,sequence[step][0]);
		digitalWrite(pinB,sequence[step][1]);
		digitalWrite(pinC,sequence[step][2]);
		digitalWrite(pinD,sequence[step][3]);
}
