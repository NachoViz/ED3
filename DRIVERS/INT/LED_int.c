/*
 * ControlLed.c
 *	Drivers GPIO-PINSEL
 *  Created on: 30 sept 2025
 *      Author: jnach
 */
/*
Configuraremos el pin P2.10 para que, al detectar un flanco de bajada (botón presionado),ACTIVO POR BAJO BOTTON
 active una interrupción que cambie el estado del LED P0.22.
*/



#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"

#include "lpc17xx.h"

#define PIN2_10 (1<<10) 		//IN
#define PIN0_22 (1<<22)		//OUT

void configGPIO(){
	GPIO_SetDir(2 , PIN2_10, 0);
	GPIO_SetDir(0 , PIN0_22, 1);
	GPIO_ClearValue(0 ,PIN0_22);

	PINSEL_CFG_Type psel_conf;
	psel_conf.Portnum = 2;
	psel_conf.Pinnum = 10;
	psel_conf.Pinmode = PINSEL_PINMODE_PULLUP;  //pullup entrada
    psel_conf.Funcnum = 0;
    psel_conf.OpenDrain = PINSEL_PINMODE_NORMAL;

	PINSEL_CFG_Type psel_conf1;
	psel_conf1.Portnum = 0;
	psel_conf1.Pinnum = 22;
	psel_conf1.Pinmode = PINSEL_PINMODE_TRISTATE;
    psel_conf1.Funcnum = 0;
    psel_conf1.OpenDrain = PINSEL_PINMODE_NORMAL;

    PINSEL_ConfigPin(&psel_conf);
    PINSEL_ConfigPin(&psel_conf1);

   GPIO_IntCmd(2, (1 << 10), 1);

   NVIC_EnableIRQ(EINT3_IRQn);

}

void EINT3_IRQHandler(){

	if(GPIO_GetIntStatus(2,P2_10 ,1)){
		LPC_GPIO0->FIOSET ^= (1 << 22);
	}

	GPIO_ClearInt(2,10);
}

int main(){
	configGPIO();


	while(1){

	}
}


