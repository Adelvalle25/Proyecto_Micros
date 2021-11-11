#ifndef __UTILITIES_H__
#define	__UTILITIES_H__
#include "stm32f3xx.h"                  // Device header




void Rd_get(const char a[]);
void Rm_mod();
void Md(const uint8_t start, const uint8_t end);
void Mm(uint16_t addr, uint8_t size);


void clk_config(void);
void USART1_config(void);
void USART1_send(char c);
void USART1_putString(char * string);

#endif /* __UTILITIES_H__*/



