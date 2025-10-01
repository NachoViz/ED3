/*
 * ControlLed.c
 *	Drivers GPIO-PINSEL
 *  Created on: 30 sept 2025
 *      Author: jnach
 */

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

#include "lpc17xx.h"

#define P1_18 (1<<18) 	//OUT
#define P0_1 (1<<1)		//IN

void configGPIO(){
	GPIO_SetDir(1,P1_18,1);
	GPIO_SetDir(0,P0_1, 0);
	GPIO_ClearValue(1, P1_18);

	PINSEL_CFG_Type psel_conf;

	psel_conf.Portnum = 0;
	psel_conf.Pinnum = 1;
	psel_conf.Pinmode = PINSEL_PINMODE_PULLUP;  //pullup entrada
    psel_conf.Funcnum = 0;
    psel_conf.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&psel_conf);

	PINSEL_CFG_Type psel_conf1;

	psel_conf1.Portnum = 1;
	psel_conf1.Pinnum = 18;
	psel_conf1.Pinmode = PINSEL_PINMODE_TRISTATE;
    psel_conf1.Funcnum = 0;
    psel_conf1.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_ConfigPin(&psel_conf1);
}


int main(){
	configGPIO();


	while(1){
		if((GPIO_ReadValue(0)& P0_1)== 0){
			GPIO_SetrValue(1,P1_18);
			delay();
		}
		GPIO_ClearValue(1,P1_18);
	}
}
