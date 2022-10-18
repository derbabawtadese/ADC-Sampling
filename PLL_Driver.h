#ifndef __PLL_DRIVER_H
#define __PLL_DRIVER_H

#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define SYSTEM_CLOCK_MHZ	80000000UL

void InitPLL(void);
void InitSysTick(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait1ms(uint32_t delay);

#endif
