#include "LPC17xx.h"


#define TIEMPO_REBOTE 2000000

void delay(void){
    for(volatile uint32_t i = 0; i < TIEMPO_REBOTE; i++);
}

void configGPIO(void){
    // LED en P0.22
    LPC_GPIO0->FIODIR |= (1 << 22);    // Salida
    LPC_GPIO0->FIOSET |= (1 << 22);     

    // Botón en P2.10 como EINT0
    LPC_PINCON->PINSEL4 &= ~(3 << 20);
    LPC_PINCON->PINSEL4 |=  (1 << 20);
    LPC_PINCON->PINMODE4 |=  (3 << 20); //PULL-DOWN
}

void EINT0_Init(void){
    LPC_SC->EXTMODE |= (1 << 0);   // Interrupción por flanco
    LPC_SC->EXTPOLAR &= ~(1 << 0); // Flanco de bajada

    NVIC_ClearPendingIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler(void){
    delay(); // Antirrebote simple

    // Cambiar estado del LED
    if(LPC_GPIO0->FIOPIN & (1 << 22))
        LPC_GPIO0->FIOCLR = (1 << 22);
    else
        LPC_GPIO0->FIOSET = (1 << 22);

    LPC_SC->EXTINT = (1 << 0); // Limpiar bandera
}

int main(void){
    configGPIO();
    EINT0_Init();

    while(1){
        __WFI();
    }
}
