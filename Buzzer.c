#include "driverlib.h"             // Device header
#include "gpio.h"

// 初始化蜂鸣器
void Buzzer_Init(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
} // 初始化时关闭蜂鸣器


// 打开蜂鸣器
void Buzzer_OFF(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
}

// 关闭蜂鸣器
void Buzzer_ON(void)
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
}

void Buzzer_Turn(void)
{
      GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN0);


}

