
#ifdef __USE_CMSIS

#include "LPC17xx.h"

#endif

#include <iostream>

volatile uint32_t counter; 

const uint8_t table[16] = {
    ..
    ..
    ..
}

void EINT0_Init(void);
void EINT1_Init(void);
void led_config(void);
void configGPIO();

//CONTADOR EN P0.10
//7SEGMENTOS hexagesimal (P2.0-7)
//Incremento de la cuenta por interrupcion 
// Incrementa la cuenta mediante una flanco de subida 

int main(){
    
EINT0_Init(void);

led_config(void);
configGPIO();
}

void configGPIO(){
    //SUPONGO CONFIGURACION INICIAL
    LPC_PINCON->PINSEL0 &= ~(3 << 20);       //BIT 20 
    LPC_PINCON->PINSEL0 |= (1 << 20);

    LPC_PINCON->PINMODE0 |= (1 << 20);

    LPC_GPIO0->FIODIR |= ~(1 << 10);

    LPC_GPIO2->FIODIR |= 0x7F;
    /*
        resolucion
        LPC_GPIO0->FIODIR | =(1 <22);
        LPC_GPIO3->FIODIR  |= (3 << 25);
        LPC_PINCON->PINSEL4 |= (1 << 20);     //P2.10 EINT2 Pulsador externo
        

    */

}

void configST(){
    Systick_Config(2000000);  //prioridad 31
    //hacer eso o sino manualmente: 
    Systick_LOAD = 2000000   -1 ;
    Systick_VAL = 0;
    Systick_CTRL = 1 << 1 |1 << 2;   //normalmente no cambia/7 no arranco aun
}

void EIN0_Init(void){ //ConfigEINT
    LPC_PINCON->PINSEL0 &= ~(3 << 0);
    LPC_PINCON->PINSEL0 |= (1 << 0);    //P0.0 como 


    LPC_SC->EXTMODE |= (1 << 0);  //MODO DE FLANCO
    LPC_SC->EXTPOLAR|= ( 1 << 0);  //MODO DE SUBIDA
//Al tocar estos dos registros hay que bajar si o si la bandera 
//para evitar que se vuelva a atender la misma interrupcion

    LPC_SC->EXTINT | = 1 << 0; 
    NVIC_ClearPending(EINT0_IRQn); //limpia le flag del nvic pero no de la interrupcion
    NVIC_EnableIRQ(EINT0_IRQn);

    /*

    */
}

void EIN0_IRQHandler(){
    //Hago un antirrebote con el NVIC
    NVIC_Disable(EINT0_IRQn);
    LPC_SC->EXINT |= (1 << 0);
    //PODEMOS HACER QUE EL SISTICK ARRANQUE CUANDO YO QUIERA CON LA CONFIG MANUAL
    Systick->CTRL = 1 << 0;
}

void Systick_Hnadler(){

    Systick->CTRL &= ~(1 << 0);   //Para que no te genere mas interrupciones

    if(LPC_GPIO2->FIOPIN & (0x1 << 10) ){ //Pregunto si esta encendido
        LED_SWAP();
        NVIC_EnableIRQ(EINT0_IRQn);

    }else{
        NVIC_EnableIRQn(EINT0_IRQn); // para habilitar el boton
    }   
}



