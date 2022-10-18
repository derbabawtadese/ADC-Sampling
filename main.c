#include <stdlib.h>
#include "ADC.h"    
#include "UART.h"
#include "PLL_Driver.h"
#include "GPIO_Driver.h"

#define BUFFER_SIZE	4096

char BufferMATLAB[BUFFER_SIZE];
//uint16_t Buffer[BUFFER_SIZE];

void GetResualtADC(void);

int main(void)
{	
    int i;
    InitPLL();		// 80MHz clock
    InitSysTick();
    InitGPIOF();
    InitADC_0();
    InitGPIOF();
    InitGPIOA_4_UART();
    InitUART_0(230400);

    while (1)
    {
		for(i = 0; i<3; i++)
		{
			GPIOF->DATA ^= 0x04;
			SysTick_Wait1ms(500);	// System stabilaztion for 5 sec
		}
        GetResualtADC();
    }
}

void GetResualtADC(void)
{
    uint16_t i;
    char MSB, LSB;
    uint16_t AnalogInput;

	for(i = 0; i < BUFFER_SIZE-1; i = i+2)
	{
        AnalogInput = SampleADC_0();    // 0111 0111 0101 1001 -> [1 1 2 2 3 3]
        //Buffer[i] = AnalogInput;
        MSB = AnalogInput>>8;
        LSB = AnalogInput;
        BufferMATLAB[i] = MSB;
        BufferMATLAB[i+1] = LSB;
        SysTick_Wait1ms(1);
	}

    GPIOF->DATA = 0x08;
	for(i = 0; i < BUFFER_SIZE; i++)
	{
        UART0Tx(BufferMATLAB[i]);
	}
	GPIOF->DATA = 0x0;
}
