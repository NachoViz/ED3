#include<LPC1679.H>
//Es un juguete que trendes y empieza a tomar muestras cada x cantidad de tiempo 
int main(){

    while(1){

    }
}

void configGPIO(){
    LPC_SC->PCONP |= (1 << 12);  // Encender ADC (bit 12)
    // Para AD0.0 en P0.23:
    LPC_PINCON->PINSEL1 |= (1 << 14);  // Bits 14-15: 01 para AD0.0
    LPC_PINCON->PINSEL1 &= ~(1 << 15);
}
uint16_t *buffer = (uint16_t *)0x2007C000;

void configADC(){
    LPC_SC->PCONP |= 1 << 12; 
    LPC_ADC->AD0CR |= 1 << 8 | 1 << 21; //en tiempo de interrupcion configurar a el 010 START
}   LPC_ADC->ADINTEN |= 1 << 0 ; //EL CANAL 0 ME GENERE UN 1 CADA VEZ QUE QUIERO CONVERTIR 


void ADC_IRQHandler(){
    ADC0Value = (( LPC_GPIO0->AD0CR) & 0xFFF)
}