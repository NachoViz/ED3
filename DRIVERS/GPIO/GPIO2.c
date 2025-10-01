/*
===============================================================================
 Name        : Timer_and_GPIO.c
 Author      :
 Version     :
===============================================================================
*/

#include "LPC17xx.h"

/*!
 * Header files to project. Include library
 */

#include "lpc17xx_gpio.h"

#define ROJO (1<<22)
#define VERDE (1 << 25)
#define AZUL (1 << 26)

void configGPIO();
void configTimer();

int main(){


	while(){
	GPIO_ClearValue(0,ROJO);
	delay();

	GPIO_SetValue(0, ROJO);	//Pongo el led rojo en alto
	delay();


	}

}

void configGPIO(){

	GPIO_SetDir(0, (1<< 22), 1 );		//ROJO
	GPIO_SetDir(3, (1 << 25), 1);		//VERDE
	GPIO_SetDir(3, (1 << 26), 1);		//AZUL


}


void delay(){

	for(volatile i = 0; i < 1000; i++);
}
