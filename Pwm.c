#include "driverlib.h"
#include "PWM.h"
#include "msp430.h"
// void PWM_Init(void)
// {
//     // 设置时钟，假设使用16MHz的SMCLK
//     UCSCTL3 = SELREF_2;                          // 设置DCO FLL参考频率为REFO
//     UCSCTL4 |= SELA_2;                           // 设置ACLK为REFO

//     __bis_SR_register(SCG0);                     // 使能FLL控制环路
//     UCSCTL0 = 0x0000;                            // 设置DCOx和MODx
//     UCSCTL1 = DCORSEL_5;                         // 选择DCO范围为16MHz
//     UCSCTL2 = FLLD_1 + 487;                      // 设置DCOCLKDIV = 16MHz

//     __bic_SR_register(SCG0);                     // 使能FLL控制环路
//     __delay_cycles(782000);                      // 等待DCO稳定
//     // 解决可能的振荡器失锁问题
//     do
//     {
//         UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT2OFFG); // 清除振荡器故障标志
//         SFRIFG1 &= ~OFIFG;                         // 清除振荡器故障标志
//     } while (SFRIFG1 & OFIFG);                     // 振荡器故障标志被清除

//     // 配置P2.4和P2.5为Timer_A输出（PWM）
//     P2DIR |= BIT4 | BIT5;  // 设置为输出
//     P2SEL |= BIT4 | BIT5;  // 选择Timer_A功能

//     // 配置Timer_A
//     TA2CCR0 = PWM_PERIOD - 1;  // 设置周期
//     TA2CCTL1 = OUTMOD_7;   // 设置PWM模式为复位/置位
//     TA2CCR1 = 0;   // 初始占空比为0
//     TA2CCTL2 = OUTMOD_7;   // 设置PWM模式为复位/置位
//     TA2CCR2 = 0;   // 初始占空比为0
//     TA2CTL = TASSEL_2 + MC_1;  // 使用SMCLK，增计数模式
// }

// void PWM_SetDuty1(uint16_t duty)
// {
//     TA2CCR1 = duty;
// }

// void PWM_SetDuty2(uint16_t duty)
// {
//     TA2CCR2 = duty;
// }

void PWM_Init(void)
{
    // 停止看门狗定时器
    WDT_A_hold(WDT_A_BASE);

    // 设置DCO为16MHz
    UCS_setExternalClockSource(32768, 0);  // 设置外部时钟源
    UCS_initClockSignal(UCS_FLLREF, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);  // 设置FLL参考时钟
    UCS_initClockSignal(UCS_ACLK, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);  // 设置ACLK
    UCS_initFLLSettle(16000, 487);  // 设置DCO为16MHz

    // 配置P2.4和P2.5为Timer_A输出（PWM）

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5);
    // 配置Timer_A的第一个PWM通道
    Timer_A_outputPWMParam pwmConfig1 = {0}; // 初始化 PWM 配置结构体，所有字段初始为 0
    pwmConfig1.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; // 设置时钟源为子系统主时钟（SMCLK）
    pwmConfig1.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1; // 设置时钟源不分频，直接使用 SMCLK 的频率
    pwmConfig1.timerPeriod = PWM_PERIOD - 1; // 设置 PWM 周期（计数器最大值），周期减1
    pwmConfig1.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1; // 选择捕获/比较寄存器 1（CCR1）作为比较输出寄存器
    pwmConfig1.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET; // 设置 PWM 输出模式为复位/置位模式
    pwmConfig1.dutyCycle = 0; // 初始占空比为 0，即初始时 PWM 信号为低电平

    // 配置Timer_A的第二个PWM通道
    Timer_A_outputPWMParam pwmConfig2 = {0}; // 初始化 PWM 配置结构体，所有字段初始为 0
    pwmConfig2.clockSource = TIMER_A_CLOCKSOURCE_SMCLK; // 设置时钟源为子系统主时钟（SMCLK）
    pwmConfig2.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1; // 设置时钟源不分频，直接使用 SMCLK 的频率
    pwmConfig2.timerPeriod = PWM_PERIOD - 1; // 设置 PWM 周期（计数器最大值），周期减1
    pwmConfig2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2; // 选择捕获/比较寄存器 2（CCR2）作为比较输出寄存器
    pwmConfig2.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET; // 设置 PWM 输出模式为复位/置位模式
    pwmConfig2.dutyCycle = 0; // 初始占空比为 0，即初始时 PWM 信号为低电平

    // 启动PWM输出
    Timer_A_outputPWM(TIMER_A2_BASE, &pwmConfig1);
    Timer_A_outputPWM(TIMER_A2_BASE, &pwmConfig2);
}

void PWM_SetDuty1(uint16_t duty)
{
    Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1, duty);
}

void PWM_SetDuty2(uint16_t duty)
{
    Timer_A_setCompareValue(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2, duty);
}