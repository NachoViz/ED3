#include<LPC1679.H>
#define LED_AZUL (1 << 0);
#define LED_ROJO (1 << 1);
#define LED_VERDE (1 << 2);

void configGPIO();
void configADC();

int main(){

    while(1){

    }
}

void configGPIO(){
    LPC_GPIO2->FIODIR |=  (1 << 0) | (1 << 1 ) |( 1 << 2 );
    LPC_PINCON->PINSEL0 |= ~(3 << 30);  //P0.15    //configuro en 01 para poder hacer la funcion alternativa
    LPC_PINCON->PINSEL1 |= ~(3 << 0);   //P0.16
    LPC_PINCON->PINSEL1 |= ( 1 << 14); //P0.23

    LPC_GPIOINT->IO0IntEnR |= ( 1 << 15); //Interrupcion P0.15
    LPC_GPIOINT->IO0IntEnR |= ( 1 << 16); //Interrupcion P0.15
    NVIC_Enable(EINT3_IRQn);
}

void EINT3_IRQHandler(){
    if(LPC_GPIOINT->IO0IntStatR & (1 << 15 )){
        LPC_ADC->ADCR = 
    }

}

void configST(){
    Systick_config(1000000); //10ms
}

void Systick_Handler(){
     static uint32_t diez = 10;
     diez--;
     if(diez == 0){
        LPC_ADC->ADCR |= (7 << 24);
     }

}
void configADC(){
    LPC_SC->PCONP |= (1 << 12);
LPC_ADC->ADCR |= (1 << 21); //habilita el ADC
LPC_SC->PCLKSEL0 |= (3<<24);  //CCLK/8
LPC_ADC->ADCR &=~(255 << 8);  //[15:8] CLKDIV
//LPC_ADC->ADCR |=(255 << 8);  //[15:8] CLKDIV
LPC_ADC->ADCR |= (1 << 0);   // channel
LPC_ADC->ADCR |= ~(1 << 16);   // burst
LPC_PINCON->PINMODE1 |= (1<<15); //neither pull-up nor pull-down.
LPC_PINCON->PINSEL1 |= (1<<14);	 //seleccionar función ADC en pinconnect block
LPC_ADC->ADINTEN |= (1<<0);
LPC_ADC->ADINTEN &=~ (1<<8);
NVIC_EnableIRQ(ADC_IRQn);

}

void ADC_Handler(){
    ADC0Value = ((LPC_ADC->ADDR0)>>4) & 0xFFF;
    LPC_ADC->ADCR |= ~(7 << 24);
}

