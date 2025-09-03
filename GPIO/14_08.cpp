// Registro BLOCK-> nos da las coneccion a las patas fisicas del Micro
/*
DENTRO ESTA EL 
GPIO0 > PINSEL0 Y PINSEL1
GPIO1 ->PINSEL2 Y PINSEL3
ADC
DAC
TX
Se acceden mediante el PINSEL
OPEN DIRVE
    V_oh = 3v3 -0.4V 
    V_ol = 
    A medida que le hacemos pasar tension se nos va moviendo el 0 a otros valores(ver grafica) *PREGUNTA DE PARCIAL*
    PPORQUE SE USA V_ol, V_ol

*/

#include<LPC17XX.h>

#define DELAY_TIME 10000

int main(){

}

void configGPIO(void){
    LPC_SC->PCONP |= (1 << 15);
    LPC_PINCON->PINSEL0 |= ~(3 << 0);
    LPC_PINCON->PINSEL1 |= 

}

void delay(){
    for(volatile int i=0; i<DELAY_TIME;i++);
}