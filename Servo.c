#include "driverlib.h"

#include "PWM.h"
#include "math.h"

/**
  * 函    数：舵机初始化
  * 参    数：无
  * 返 回 值：无
  */
	
void Servo_Init(void)
{
	PWM_Init();									//初始化舵机的底层PWM
}


 
/**
  * 函    数：舵机设置角度
  * 参    数：Angle 要设置的舵机角度，范围：0~180
  * 返 回 值：无
  */


void Servo_SetAngle(float Angle1, float Angle2)
{
    // 设置PWM占空比，确保与舵机的转换公式一致
    uint16_t duty1 = (uint16_t)(((Angle1 / 270.0) * 2000.0 + 500.0) * (PWM_PERIOD / 20000.0));
    uint16_t duty2 = (uint16_t)(((Angle2 / 270.0) * 2000.0 + 500.0) * (PWM_PERIOD / 20000.0));
    PWM_SetDuty1(duty1);
    PWM_SetDuty2(duty2);
}
