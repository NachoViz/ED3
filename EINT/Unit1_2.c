#include "LPC17xx.h"
#include<iostream>

using namespace std;

/*Utilice un pin del Puerto 0 como entrada para el pulsador y 7 pines del Puerto 2 para el
display de 7 segmentos.
Configure el pin de entrada para que genere una interrupción solo cuando se detecte un
flanco de subida (paso de 0 a 1).
o La lógica de incremento del contador debe residir en el Handler de la Interrupción (ISR).
*/

int main(){

    while(1){

    }
}

void configGPIO(){
    LPC_PINCON->PINSEL4 &= ~(3 << 10); 
    LPC_PINCON->PINSEL4 |= (1 << 10); 

    LPC_PINCON->PINMODE0 |= (3 << 0); //P0.0 pull down

    LPC_GPIO0->FIODIR |= ~(1 << 0 ); //Entrada P0.0
    LPC_GPIO2->FIODIR |= ( 0x7F << 10 ); //Salida P2.0-7   



}

void configST(){


}

void Systick_Handler(){

}

void EINT0_Init(){
    
}

void EINT0_Handler(){

}
