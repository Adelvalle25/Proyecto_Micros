#include "stm32f3xx.h"                  // Device header
#include <stdio.h>
#include "drivers.h"


const char* registers[16];


int main(void){
	clk_config();
	USART1_config();
	Rd_get(registers[0]);
	
	while(1){
		
	}
}



