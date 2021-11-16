#ifndef __UTILITIES_H__
#define	__UTILITIES_H__
#include "stm32f3xx.h"                  // Device header

#define		MASK(x)		(1<<x)



void Rd_get(void);   
void Rm_mod();
void Md(const uint8_t start, const uint8_t end);
void Mm(uint16_t addr, uint8_t size);


void clk_config(void);
void USART1_config(void);
void USART1_send(char c);
void USART1_putString(char * string);
void Read_uart(void);
void printconsol(void);
void help(void);
void iomap(uint8_t nPin, uint8_t mode);
void printconsol(void);
#endif /* __UTILITIES_H__*/



