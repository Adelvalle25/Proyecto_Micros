#ifndef __UTILITIES_H__
#define	__UTILITIES_H__
#include "stm32f3xx.h"                  // Device header

#define		MASK(x)		(1<<x)



void Rd_get(void);   
void Rm_mod(uint32_t ref, uint32_t da);
void Md(void);
void Mm(void);


void clk_config(void);
void USART1_config(void);
void USART1_send(char c);
void USART1_putString(char * string);
void Read_uart(void);
void printconsol(void);
void help(void);
void printconsol(void);
#endif /* __UTILITIES_H__*/



