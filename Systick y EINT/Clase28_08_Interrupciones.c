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

#include <stdio.h>



static uint32_t flanco1=0;

static uint32_t flanco2=0;

static uint32_t counter=0;



void EINT0_Init(void);

void EINT1_Init(void);

void led_config(void);



int main(void) {

	SysTick_Config(100000);

	EINT0_Init();

	EINT1_Init();

	led_config();

    // Inicialización ITM/Trace hecha automáticamente por el IDE

//    printf("Mensaje por ITM/SWO\n");

	while(1);



}



void EINT0_IRQHandler(void) {

    // Tu código al detectar flanco

    LPC_SC->EXTINT = (1 << 0); // Limpiar flag de interrupción

    flanco1 = counter;

}

void EINT1_IRQHandler(void) {

    // Tu código al detectar flanco



    flanco2 = counter;

    printf("flanco1: %d\n", flanco1);

    printf("flanco2: %d\n", flanco2);

    printf("El tiempo entre flancos es: %d\n", flanco2-flanco1);

    LPC_SC->EXTINT = (1 << 1); // Limpiar flag de interrupción

}



void SysTick_Handler(void) {

    counter++;

	LPC_GPIO0->FIOPIN ^= (1 << 22);  // Toggle LED

}



void led_config(void){

	LPC_GPIO0->FIODIR |= (1 << 22);  // Configurar P0.22 como salida

	LPC_GPIO0->FIOCLR = (1 << 22);   // Apagar LED al inicio

}



void EINT0_Init(void){

	LPC_PINCON->PINSEL4 &= ~(3 << 20);  // Limpiar bits

	LPC_PINCON->PINSEL4 |=  (1 << 20);  // Función EINT0 (01)



	LPC_PINCON->PINMODE4 &= ~(3 << 20);

	LPC_PINCON->PINMODE4 |=  (3 << 20);  // Modo pull down



	LPC_SC->EXTMODE |= (1 << 0); // 1 = flanco para EINT0



	//LPC_SC->EXTPOLAR |= (1 << 0);  // 1 = flanco ascendente (rising edge)

	LPC_SC->EXTPOLAR &= ~(1 << 0); // 0 = flanco descendente (falling edge)



	LPC_SC->EXTINT = (1 << 0);  // Limpiar cualquier interrupción pendiente



	// Habilitar EINT0 en NVIC

	NVIC_EnableIRQ(EINT0_IRQn);

}



void EINT1_Init(void) {

    // 1. Configurar P2.11 como EINT1

    LPC_PINCON->PINSEL4 &= ~(3 << 22);   // limpiar bits 23:22

    LPC_PINCON->PINSEL4 |=  (1 << 22);   // seleccionar función EINT1



    // 2. Configurar resistores: sin pull-up ni pull-down

    LPC_PINCON->PINMODE4 &= ~(3 << 22);  // limpiar

    LPC_PINCON->PINMODE4 |=  (3 << 22);  // '10' = inactive (sin resistores)



    // 3. Configurar como sensible a flanco descendente

    LPC_SC->EXTMODE  |=  (1 << 1);  // 1 = edge sensitive

    LPC_SC->EXTPOLAR &= ~(1 << 1);  // 0 = falling edge



    // 4. Habilitar interrupción en NVIC

    NVIC_EnableIRQ(EINT1_IRQn);

}

