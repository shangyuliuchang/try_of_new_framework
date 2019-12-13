#include "main.h"
pid_unit_struct pidUnits[10];
void pid_init(uint8_t num, float kp, float ki, float kd, float limit_i, float limit_t){
	pidUnits[num].kp=kp;
	pidUnits[num].ki=ki;
	pidUnits[num].kd=kd;
	pidUnits[num].limit_i=limit_i;
	pidUnits[num].limit_t=limit_t;
	pidUnits[num].error=pidUnits[num].error_d=pidUnits[num].error_i=pidUnits[num].errror_p=0.0f;
	pidUnits[num].p=pidUnits[num].i=pidUnits[num].d=0.0f;
	pidUnits[num].total=0.0f;
	pidUnits[num].init=1;
}
float pid_caculate(uint8_t num, float value_exp, float value_true){
	pidUnits[num].error=value_exp-value_true;
	if(pidUnits[num].init==1){
		pidUnits[num].errror_p=pidUnits[num].error;
		return 0;
	}
	else{
		pidUnits[num].error_d=pidUnits[num].error-pidUnits[num].errror_p;
		pidUnits[num].error_i+=pidUnits[num].error;
		if(pidUnits[num].error_i>pidUnits[num].limit_i){
			pidUnits[num].error_i=pidUnits[num].limit_i;
		}
		if(pidUnits[num].error_i<-1.0f*pidUnits[num].limit_i){
			pidUnits[num].error_i=-1.0f*pidUnits[num].limit_i;
		}
		pidUnits[num].p=pidUnits[num].error*pidUnits[num].kp;
		pidUnits[num].i=pidUnits[num].error_i*pidUnits[num].ki;
		pidUnits[num].d=pidUnits[num].error_d*pidUnits[num].kd;
		pidUnits[num].total=pidUnits[num].p+pidUnits[num].i+pidUnits[num].d;
		if(pidUnits[num].total>pidUnits[num].limit_t){
			pidUnits[num].total=pidUnits[num].limit_t;
		}
		if(pidUnits[num].total<-1.0*pidUnits[num].limit_t){
			pidUnits[num].total=-1.0f*pidUnits[num].limit_t;
		}
		return pidUnits[num].total;
	}
}
