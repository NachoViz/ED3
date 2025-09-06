/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

void confGPIO(void);
void confADC(void);

uint16_t ADC0Value = 0;

int main(void) {
confGPIO();
confADC();
while(1){}
return 0;
}

void confGPIO(void){
LPC_GPIO0->FIODIR |= (1<<22);
return;
}

void confADC(void){
LPC_SC->PCONP |= (1 << 12);
LPC_ADC->ADCR |= (1 << 21); //habilita el ADC
LPC_SC->PCLKSEL0 |= (3<<24);  //CCLK/8
LPC_ADC->ADCR &=~(255 << 8);  //[15:8] CLKDIV
//LPC_ADC->ADCR |=(255 << 8);  //[15:8] CLKDIV
LPC_ADC->ADCR |= (1 << 0);   // channel
LPC_ADC->ADCR |= (1 << 16);   // burst
LPC_PINCON->PINMODE1 |= (1<<15); //neither pull-up nor pull-down.
LPC_PINCON->PINSEL1 |= (1<<14);	 //seleccionar función ADC en pinconnect block
LPC_ADC->ADINTEN |= (1<<0);
LPC_ADC->ADINTEN &=~ (1<<8);
NVIC_EnableIRQ(ADC_IRQn);

return;
}
void ADC_IRQHandler(void)
{
	ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF; //Variable auxiliar para observar el valor del registro de captura

	if (ADC0Value<2054){
		LPC_GPIO0->FIOSET = (1<<22);
	}
	else{
		LPC_GPIO0->FIOCLR = (1<<22);
	}

return;
}