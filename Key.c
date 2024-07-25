#include "gpio.h"
#include <msp430.h>
#include <driverlib.h>

// 延时函数，简单的延时实现（假设系统时钟为 1 MHz）
void Delay_ms(uint16_t ms)
{
    while (ms-- > 0)
    {
        __delay_cycles(1000);  // 假设系统时钟为 1 MHz，延时 1 ms
    }
}

// 初始化 GPIO
void Key_Init(void)
{
    // 设置 P1.0, P1.1, P1.2, P1.3 为输入模式
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);

    // 启用 P1.0, P1.1, P1.2, P1.3 上拉电阻（可选）
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3);
     GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,GPIO_PIN1);
}

// 读取按键状态
uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0;

    // 检查 P1.0
    if (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1) == GPIO_INPUT_PIN_LOW)  // 如果 P1.0 为低电平
    {
        Delay_ms(20);  // 去抖动延时
        while (GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1) == GPIO_INPUT_PIN_LOW);  // 等待按键释放
        Delay_ms(20);  // 去抖动延时
        KeyNum = 1;
    }

    // 检查 P1.1
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == 0)  // 如果 P1.1 为低电平
    {
        Delay_ms(20);  // 去抖动延时
        while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW);  // 等待按键释放
        Delay_ms(20);  // 去抖动延时
        KeyNum = 2;
    }

    // 检查 P1.2
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN2) == GPIO_INPUT_PIN_LOW)  // 如果 P1.2 为低电平
    {
        Delay_ms(20);  // 去抖动延时
        while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN2) == GPIO_INPUT_PIN_LOW);  // 等待按键释放
        Delay_ms(20);  // 去抖动延时
        KeyNum = 3;
    }

    // 检查 P1.3
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3) == GPIO_INPUT_PIN_LOW)  // 如果 P1.3 为低电平
    {
        Delay_ms(20);  // 去抖动延时
        while (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3) == GPIO_INPUT_PIN_LOW);  // 等待按键释放
        Delay_ms(20);  // 去抖动延时
        KeyNum = 4;
    }

    return KeyNum;
}
