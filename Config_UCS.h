#ifndef __CONFIG_UCS_H
#define __CONFIG_UCS_H
#include "driverlib.h"
#define MCLK_IN_HZ   25000000

#define delay_s(x)     _delay_cycles(MCLK_IN_HZ*(x))
#define delay_ms(x)     _delay_cycles(MCLK_IN_HZ/1000*(x))
#define delay_us(x)     _delay_cycles(MCLK_IN_HZ/1000000*(x))
void UCStoGet25M_Init(void);

#endif


 