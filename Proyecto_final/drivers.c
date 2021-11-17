#include "stm32f3xx.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char tx_string[32];
char data;
char *token[]={" "," "," "," "," "};
char D[64];
char D2[64];
char D3[64];
char D4[64];

uint32_t da;
uint32_t ref;
uint32_t resgister[16];
uint8_t n=0;
uint8_t coman_ready=0;
uint32_t i;

uint8_t memo;

uint32_t registro_rm;
uint32_t data_rm;

uint32_t direct;
uint32_t datamm;

uint32_t inicio;
uint32_t fin;
uint8_t memo_array[16];
uint32_t restr;
extern void RD_display(void);
extern void RM(uint32_t registro, uint32_t data);
extern void MM_BYTE(uint32_t direct, uint32_t data);
extern void MM_HALF(uint32_t direct, uint32_t data);
extern void MM_WORD(uint32_t direct, uint32_t data);
extern void MD(uint32_t inicio, uint32_t fin);




void USART1_IRQHandler(void){
	if(USART1->ISR & USART_ISR_RXNE){
		data= USART1->RDR;
		USART1->TDR=data;
		if(data !=  '\r'){
			tx_string[n]=data;
			if(data==0x7F){
				tx_string[n]=NULL;
				tx_string[n-1]=NULL;
				n=n-1;
			}else{
				n++;
			}
			coman_ready = 0;
		}else{
			tx_string[n] = '\0';
			n=0;
			coman_ready = 1;
		}
		
		

	}
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




void Rd_get(void){
	RD_display();
	for(i=0; i<=15; i++){
		sprintf(D,"R%d",i);
		sprintf(D3,"--->0x%08X\n\r",resgister[i]);
		strcat(strcpy(D2,D),D3);
		USART1_putString(D2);
	}
}



		



void help(void){
	USART1_putString("\33[100m\33[1mCOMANDO|------PARAMETROS-----|-------------|                            FUNCION                                       |\033[0m\r\n");
	USART1_putString("cls    |---------------------|-------------|limpia el display                                                         |\r\n");
	USART1_putString("RD     |---------------------|-------------|despliega el contenido de los registros del memoria                       |\r\n");
	USART1_putString("RM     |------R{x} data------|-------------|Modifica el contenido del registro indicado en data                       |\r\n");
	USART1_putString("MD     |----addr data size---|-------------|Escribir Data en la dirección de memoria addr size determina              |\r\n");
	USART1_putString("                                           |El def es 1, pero 1, 2 y 4son los tamanos requeridos.                     |\r\n");	
	USART1_putString("                                           |el tamaño en bytes El dato y la direccion se debenexpresar en hexadecimal |\r\n");	
	USART1_putString("MM     |--addr data [size]---|-------------|Escribir Data en la dirección de memoria addr.                            |\r\n");
	USART1_putString("                                           |El def es 1, pero 1, 2 y 4son los tamanos requeridos.                     |\r\n");	
	USART1_putString("                                           |el tamaño en bytes El dato y la direccion se debenexpresar en hexadecimal |\r\n");
	
}
void clear(void){	//se hace un salto en el puerto serial el que hace una limpieza de pantalla
	USART1_putString("\033[H\033[J");
}


void opciones(void){
	if(!strcmp(token[0],"-h")){
		help();
		coman_ready=0;
		USART1_putString("\n\r>> ");	
		
	}else if(!strcmp(token[0],"cls")||(!strcmp(token[0],"CLS"))){
		clear();
		coman_ready=0;
		USART1_putString("\n\r>> ");	
		
	}else if((!strcmp(token[0],"RD"))||(!strcmp(token[0],"rd"))){
			Rd_get();
			coman_ready=0;
		USART1_putString("\n\r>> ");	
		
	}else if((!strcmp(token[0],"RM"))||(!strcmp(token[0],"rm"))){
		ref=(uint32_t)strtoll(token[1], &token[1], 10);
		da = (uint32_t)strtoll(token[2], &token[2], 16);
		RM(da,ref);
		Rd_get();
		coman_ready=0;
		USART1_putString("\n\r>> ");	
	}else if((!strcmp(token[0],"MD"))||(!strcmp(token[0],"md"))){
			inicio=(uint32_t)strtoll(token[1], &token[1], 16);
			fin= (uint32_t)strtoll(token[2], &token[2], 16);
		MD(inicio,fin);
	restr=(fin-inicio);
		USART1_putString("\n\r");
		for(i=0;i<=restr;i++){	
			sprintf(D,"%x",memo_array[i]);
			USART1_putString(D);	
		}

			
		coman_ready=0;
		USART1_putString("\n\r>> ");	
		
	}else if((!strcmp(token[0],"MM"))||(!strcmp(token[0],"mm"))){
		if(!strcmp(token[3],"2")){
			direct=(uint32_t)strtoll(token[1], &token[1], 16);
			datamm= (uint32_t)strtoll(token[2], &token[2], 16);
			MM_HALF(direct,datamm);
		}else if(!strcmp(token[3],"4")){
			direct=(uint32_t)strtoll(token[1], &token[1], 16);
			datamm= (uint32_t)strtoll(token[2], &token[2], 16);
			MM_WORD(direct,datamm);
		}else {
			direct=(uint32_t)strtoll(token[1], &token[1], 16);
			datamm= (uint32_t)strtoll(token[2], &token[2], 16);
			MM_BYTE(direct,datamm);
		}
		
		coman_ready=0;
		USART1_putString("\n\r>> ");
	}else if((!strcmp(token[0],"MD"))||(!strcmp(token[0],"md"))){
		
	}else{
		USART1_putString("Ingrese un comando correcto \r\n");
			coman_ready=0;
		USART1_putString("\n\r>> ");	
	}
	
}

void Read_uart(void){
		if(coman_ready){		
			token[0]=strtok(tx_string," ");
			token[1]=strtok(NULL," ");
			token[2]=strtok(NULL," ");
			token[3]=strtok(NULL," ");
			token[4]=strtok(NULL," ");
			opciones();
			
		}
	}
