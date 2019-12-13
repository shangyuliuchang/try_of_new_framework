#ifndef __PID__
#define __PID__
#include "main.h"

typedef struct{
	float kp, ki, kd, limit_i, limit_t;
	float error, errror_p, error_i, error_d;
	float p, i, d, total;
	uint8_t init;
}pid_unit_struct;

extern pid_unit_struct pidUnits[10];

void pid_init(uint8_t num, float kp, float ki, float kd, float limit_i, float limit_t);
float pid_caculate(uint8_t num, float value_exp, float value_true);
#endif
