/*	Drivers GPIO-PINSEL-EINT
 *  Created on: 1 october 2025
 *      Author: jnach
 *
 *
 * El objetivo es cambiar el estado del LED P0.22
 *  cada vez que se detecte un flanco de bajada en el pin P2.10,
 *  el cual estará configurado como EINT0.
 */
#include "lpc17xx_gpio.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_exti.h"

#define PIN2_10 (1 << 10)
#define PIN0_22 (1 << 22)

void configGPIO();
void configST();

int main(){
    configGPIO();
    configEINT();

    while(1){

    }

}

void configGPIO(){
		GPIO_SetDir(2 , PIN2_10, 0);
		GPIO_SetDir(0 , PIN0_22, 1);
		GPIO_ClearValue(0 ,PIN0_22);

		PINSEL_CFG_Type psel_conf;
		psel_conf.Portnum = 2;
		psel_conf.Pinnum = 10;
		psel_conf.Pinmode = PINSEL_PINMODE_PULLDOWN;  //pullup entrada
	    psel_conf.Funcnum = 01;
	    psel_conf.OpenDrain = PINSEL_PINMODE_NORMAL;

		PINSEL_CFG_Type psel_conf1;
		psel_conf1.Portnum = 0;
		psel_conf1.Pinnum = 22;
		psel_conf1.Pinmode = PINSEL_PINMODE_TRISTATE;
	    psel_conf1.Funcnum = 0;
	    psel_conf1.OpenDrain = PINSEL_PINMODE_NORMAL;

	    PINSEL_ConfigPin(&psel_conf);
	    PINSEL_ConfigPin(&psel_conf1);

}

void configEINT(){
    EXTI_InitTypeDef  conf_eint;
    conf_eint.EXTI_Line = EINT0;
    conf_eint.EXTI_Mode = 1;
    conf_eint.EXTI_polarity = 0;

    EXTI_Config( &conf_eint );

    NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT0_Handler(){
	//codigo que va a hacer la interrupcion
	LPC_GPIO0->FIOSET ^= PIN0_22;

	EXTI_ClearEXTIFlag( EXTI_EINT0 );
}
