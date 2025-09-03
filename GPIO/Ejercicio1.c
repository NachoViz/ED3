#include "LPC17xx.h"
#define CLK 5000000UL
#define led_red (1 << 22)
#define led_green (1 << 25)
#define led_yellow ( 1 << 26)


int main(){
    configGPIO();
    while(1){
    LPC_GPIO0->FIOCLR |= led_red;
    delay();

    LPC_GPIO0->FIOSET |= led_red;
    delay();
    }

}

void configGPIO(void){
LPC_GPIO0->FIODIR |= led_red;
LPC_GPIO3->FIODIR |= led_green;
LPC_GPIO3->FIODIR |= led_yellow;

LPC_GPIO0->FIOSET |= led_red;
LPC_GPIO3->FIOSET |= led_green;
LPC_GPIO3->FIOSET |= led_yellow;


}

void delay(void){
    
    for(volatile int i= 0; i < CLK; i++);

}
