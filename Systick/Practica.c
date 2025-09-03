#include<lpc17xx.h>

#include "Practica.h"


int main(){
    configGPIO();
    SysTick_Handler_Init(); // Initialize the SysTick handler

    Systick_config();

    while(1){

        return 0;
    }
}

void Systick_config() {
    SysTick->LOAD = 10000 - 1; // Para 100 MHz = 1 ms
    SysTick->VAL = 0;          // Reinicia el contador
    SysTick->CTRL = 0x07;      // Habilita SysTick, interrupción y usa clock interno
}

void Systick_Handler(void) {
    static uint32_t tick;
    tick++;
    if(tick >= 1000 ){

        LPC_GPIO0->FIOPIN ^= ( 1 << 20);
        tick = 0; 
    }
}

void configGPIO(void){

    LPC_SC->PCONP |= (1 << 15);   //Habilito el reloj y le doy power a los GPIO

    LPC_PINCON-> PINSEL1 &= ~(3 << 8);                //P0.20 como GPIO , EL & para no afectar a los otros bits
    LPC_PINCON-> PINMODE1 &= ~(3 << 8);

    LPC_GPIO-> FIODIR |= (1 << 20 );
}