#ifndef PWM_H
#define PWM_H

#include <msp430.h>
#include "driverlib.h"

#define PWM_PERIOD 320000  // PWM信号周期，根据实际需求调整

void PWM_Init(void);
void PWM_SetDuty1(uint16_t duty);
void PWM_SetDuty2(uint16_t duty);

#endif
