 #include "driverlib.h"
#include "gpio.h"
#include "pmm.h"
#include "ucs.h"

 void UCStoGet25M_Init(void)
 {  
    //根据想要配置的MCLK频率设置核心电平
    PMM_setVCoreDown(PMM_CORE_LEVEL_3);


    //XT2引脚复用
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN2);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN3);


    //起振XT2
    UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);


    //XT2作为FLL参考时钟，先8分频
    UCS_initClockSignal(UCS_FLLREF,UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_8);

    //配置FLL,50倍频   4/8*50=25MHZ
    UCS_initFLLSettle(25000, 50);

    //XT2作为ACLK时钟源=32768Hz
    UCS_initClockSignal(UCS_ACLK, UCS_XT2CLK_SELECT,UCS_CLOCK_DIVIDER_1);

    //DCOCLK作为MCLK时钟源=25MHZ
    UCS_initClockSignal(UCS_MCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);


     //DCOCLK作为SMCLK时钟源=25MHZ
    UCS_initClockSignal(UCS_SMCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //设置外部时钟源的频率
    //在调用UCS_GETMCLK,UCS_GETSMCLK或UCS_GETACLK时刻得到正确值

    UCS_setExternalClockSource(32768, 4000000);


 } 

 