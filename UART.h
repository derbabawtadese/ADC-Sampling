#ifndef __UART_H
#define __UART_H

#include "TM4C123.h"                    // Device header

// UART
void InitUART_0 (uint32_t baudrate);
void InitUART_1 (uint32_t baudrate);
void UART0Tx (unsigned char data);
void UART1Tx (unsigned char data);
void UART0TxNonBlocking (char data[][25], unsigned char color);
void UART1TxNonBlocking (char data[][25], unsigned char color);
unsigned char UART0Rx (void);
unsigned char UART1Rx (void);
unsigned char UART0RxNonBlocking(void);
void OutUDec(unsigned long n);
// GPIO
void InitGPIOA_4_UART (void);
void InitGPIOB_4_UART (void);
void InitGPIOF_4_UART (void);


#endif

