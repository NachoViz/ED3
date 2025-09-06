#include<LPC1679.H>

#define ROJO (1 << 0);
#define VERDE (1 << 1);
#define AZUL (1 << 2);

void configGPIO();
void configST();

int main(){
    configGPIO();
    configADC();
    
    while(1){

    }

}

void configGPIO(){
    LPC_PINCON->PINSEL1 |= (1 << 14);
    LPC_GPIO0->FIODIR |= (0 << 23);
    LPC_GPIO2->FIODIR |= ROJO | VERDE | AZUL ; 

    LPC_GPIO2->FIOCLR |= ROJO |VERDE | AZUL;


}

//CLK 100.000.000 / 100.000 = 1ms   

void configADC(){
    LPC_SC->PCONP |= 1 << 12 ;
    LPC_SC->PLCSEL0 |= 1 << 24;
    LPC_ADC->ADCR |= 1 << 0;
    LPC_ADC->ADCR |= 255 << 8;                           // PRESCALER A 256 100Mhz/256 ->Frecuencia del reloj del adc 
    
    // Para saber a que frecuencia opera debemos dividir los 65 ciclos que demora en hacer la conversion 
    // Frecuencia del reloj del ADC = FCLKADC => FCLKADC/65 = frecuencia minima de conversion
    LPC_ADC->ADCR |= 1 << 16;                                               //BURST 
    LPC_ADC->ADCR |=  1 << 21 ;                                             //Habilito ADC
    LPC_ADC->ADINTEN |= (1 << 0) | ( 1 << 8);                                             //Habilito Interrupcion Chanel0
    
    NIVC_EnableIRQ(ADC_IRQn)

}


void ADC_IRQHandler(){
    ADC_VAL = (LPC_ADC->ADDR0 >> 4 );  // se maneja con 12 bits = 4095
    if( ADC_VAL <= 1366){
        LPC_GPIO2->FIOSET |= AZUL ;
        LPC_GPIO2->FIOCLR |= ROJO | VERDE; 

    }else if( ADC_VAL> 1366 && ADC_VAL <=2731){
        LPC_GPIO2->FIOSET |= VERDE ;
        LPC_GPIO2->FIOCLR |= ROJO | AZUL; 

    }else if ( ADC_VAL > 2732){
        LPC_GPIO2->FIOSET |= ROJO ;
        LPC_GPIO2->FIOCLR |= AZUL | VERDE; 
    }

}
