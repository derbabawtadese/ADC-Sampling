#include "ADC.h"

void InitADC_0(void)
{
	SYSCTL->RCGCADC = 0x01;		// Enable clock for ADC module 0
	while((SYSCTL->RCGCADC & 0x01) == 0){}
	SYSCTL->RCGCGPIO |= 0x10;	// Enable clock for portE
	GPIOE->DIR &= ~0x04;		// PE2 as an input
	GPIOE->ADCCTL |= 0x01;
	GPIOE->AFSEL |= 0x04;		// Set alternate function on PE2 used for ADCin
	GPIOE->DEN &= ~0x04;		// Disable digital I/O on PE2
	GPIOE->AMSEL |= 0x04;		// Enable analog function on PE2
	
	ADC0->ACTSS &= ~0x0F; 
	ADC0->EMUX |= 0x00;
	ADC0->SSMUX0 |= 0x01;
	ADC0->SSCTL0 |= 0x20;
	ADC0->ACTSS |= 0x01; 
}

uint16_t SampleADC_0(void)
{
	uint16_t Result;
	ADC0->PSSI |= 0x01;			// Begin sampling on Sample Sequencer 0
	while((ADC0->ACTSS & 0x1000) == 0x1000){}		// ADC Busy
	Result = ADC0->SSFIFO0;
	return Result;				// Conversion Result Data
}
