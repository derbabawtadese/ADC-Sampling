#include "PLL_Driver.h" 

void InitPLL(void)
{
	SYSCTL->RCC2 = 0x80000000;				// Use RCC2
	SYSCTL->RCC &= ~(0x1<<22 | 0x0<<11);	// Setting the BYPASS bit and clearing the USESYS bit
	SYSCTL->RCC &= ~(0x8<<4 | 0x2<<8);		// Select the crystal value (XTAL - 10101 = 0x15 -> 16MHz) and oscillator source (OSCSRC - Main Osc)			
	SYSCTL->RCC2 |= 0x40000000;  			// Set DIV400
	SYSCTL->RCC2 &= ~(0xC<<20 | 0xE<<24);	// Select the desired system divider (SYSDIV)
	SYSCTL->RCC &= ~(0<<22);				// Set the USESYS bit
	while((SYSCTL->RIS & 0x40) == 0){}		// Wait for the PLL to lock by polling the PLLLRIS bit
	SYSCTL->RCC &= ~(0x1<<11);				// Clearing the BYPASS bit
}

void InitSysTick(void)
{
	SysTick->VAL = 0;						// disable SysTick during setup
	SysTick->CTRL |= 0x05;					// enable SysTick with core clock	
}

// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)

void SysTick_Wait(uint32_t delay)
{
	SysTick->LOAD = delay-1;  				// number of counts to wait
	SysTick->VAL = 0;       				// any value written to CURRENT clears
	while((SysTick->CTRL&0x00010000)==0){} 	// wait for count flag
}

// 80000*12.5ns equals 1ms
void SysTick_Wait1ms(uint32_t delay)
{
	uint32_t i;

	for(i=0; i<delay; i++)
	{
		SysTick_Wait(80000);  				// wait 1ms
	}
}
