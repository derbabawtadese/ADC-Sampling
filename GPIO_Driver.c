#include "GPIO_Driver.h"
#include <stdlib.h>
void InitGPIOF (void)
{
	SYSCTL->RCGCGPIO |= 1<<5;
	while((SYSCTL->RCGCGPIO & 0x20) == 0){}
	GPIOF->DIR |= 1<<1 | 1<<2 | 1<<3;
	GPIOF->DEN |= 1<<1 | 1<<2 | 1<<3;
}

void ToggleGPIOF (void)
{
	GPIOF->DATA ^= 1<<1;
}
