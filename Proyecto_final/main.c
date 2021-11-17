#include "stm32f3xx.h"                  // Device header
#include <stdio.h>
#include "drivers.h"


const char* registers[16];


int main(void){
	clk_config();
	USART1_config();
	
		USART1_putString("\33[104m---------------------------------------------------------------\033[0m\n\r");
		USART1_putString("\33[100m\33[1m		Proyecto final														\n\r");
		USART1_putString("integrantes :  																									\n\r");
		USART1_putString("-Andres del Valle 18005802 																			\n\r");
		USART1_putString("-Melissa Gonzalez 19003141																			\n\r");
		USART1_putString("-Sabine Sundfeld  18001640																				\n\r");
		USART1_putString("-Luis Reyes       19000446																						\n\r");
		USART1_putString("-Carlos Barrera   19000732																				\n\r");
		USART1_putString("\33[91m'-h' para abrir el menu de ayuda											\033[0m		\n\r");
		USART1_putString("\33[104m-----------------------------------------------------------------\033[0m\n\r");
		printconsol();

	while(1){
		Read_uart();
	}
}




