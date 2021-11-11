#include "stm32f3xx.h"                  // Device header
#include <stdio.h>
#include <string.h>

char tx_string[32];
char data;

uint8_t n=0;
uint8_t coman_ready=0;

extern void RD_display( const char a[]);


void Rd_get(const char* a[]){
	RD_display(*a);
}

void Rm_mod(){
	
}

void Md(const uint8_t start, const uint8_t end){
	
}
void Mm(uint16_t addr, uint8_t size){
	
}






void clk_config(void){
		// PLLMUL <- 0x0E (PLL input clock x 16 --> (8 MHz / 2) * 16 = 64 MHz )  
	RCC->CFGR |= 0xE<<18;
	// Flash Latency, two wait states for 48<HCLK<=72 MHz
	FLASH->ACR |= 0x2;
	// PLLON <- 0x1 
  RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));	
	// SW<-0x02 (PLL as System Clock), HCLK not divided, PPRE1<-0x4 (APB1 <- HCLK/2), APB2 not divided 
	RCC->CFGR |= 0x402;
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10);
}

//puerto serial config PC5 Y PC4
void USART1_config(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN ; 																	//clock puerto c
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;																	//clock usart1
	
	GPIOC->MODER |= (2<<8)+(2<<10) ; 																		 //funcion alternatica a PC5 Y PC4
	GPIOC->AFR[0] |= (7<<16)+(7<<20); 																		// funcion alternativa 2 al pin 0 (AFRL) 
	
	
	USART1->BRR = (uint16_t)(SystemCoreClock/115200);											//64M/115200 =555
	USART1->CR1 |= USART_CR1_TE +USART_CR1_RE;														//Habilitar recepcion y transmision
	USART1->CR1 |=	USART_CR1_RXNEIE; 																		//Habilitar interrupciones en recepcion
	USART1->CR1 |=	USART_CR1_UE;																					//Habilita puerto serial
	NVIC_EnableIRQ(USART1_IRQn);
}


void USART1_send(char c){
	while(!(USART1->ISR & USART_ISR_TC));
	USART1->TDR =c;
}


void USART1_putString(char * string){
	while(*string){
		USART1_send(*string);
		string++;
	}
}

void USART1_IRQHandler(void){
	if(USART1->ISR & USART_ISR_RXNE){
		data= USART1->RDR;
		if(data !=  '\r'){
			tx_string[n]=data;
			n++;
			coman_ready = 0;
		}else{
			tx_string[n] = '\0';
			n=0;
			coman_ready = 1;
		}
	}
}