#include<LPC1679.H>

void configGPIO();
void configST();

volatile uint32_t tick;
volatile pwm_enable = 0; 

int main(){
    configGPIO();
    configST();

    while(1){
        __WFI();
    }

}

//Pongo un boton para prender y apagar el generador
void configGPIO(){
    //Boton activo por alto
    LPC_PINCON->PINMODE0 |= ( 3 << 0 );   
    LPC_GPIO0->FIODIR &= ~(1 << 0);

    LPC_GPIO0->FIODIR |= (1 << 2);




} 

void configEINT(){
    LPC_GPIOINT ->IO0IntEnR |= (1 << 0);  //habilita interrupcion por flanco de subida P0.0 
    NVIC_Enable(EINT3_IRQn); //habilito interrupcion
}

void configST(){
    Systick->LOAD = 100000;    //100ms
    Systick->VAL = 0;
    Systick->CTRL = 0x07;  //Habilito interrupcion, clk interno, comienza a contar 0111
}

void Systick_Handler(){
    tick++; 
    if(pwm_enable){
        tick++;
        if(tick<75){
            LPC_GPIO0->FIOSET |= (1 << 2);
        } else {
            LPC_GPIO0->FIOCLR |= (1 << 2);
        }

        if (tick >= 100) {
            tick = 0;
        }
    }
}

void EINT3_Handler(){
    if(LPC_GPIOINT->IO0IntStatR & ( 1 << 0)){
        pwm_enable ^= 1;
        LPC_GPIOINT->IO0IntClr;
    }
}
