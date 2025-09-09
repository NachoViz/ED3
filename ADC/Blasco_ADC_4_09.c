#include<LPC1679.H>
#define LED_AZUL (1 << 0);
#define LED_ROJO (1 << 1);
#define LED_VERDE (1 << 2);

void configGPIO();
void configADC();

volatile uint32_t ADC0Value;

int main(){

    LPC_ADC->ADCR |= (1 << 0 ) | ( 1 << 24) |( 1 << 27); // Activo canal 0 //Activo ADC //Interrupcion canal0

    while(1){
        ADC_StartConvertion();
    }
}

void configGPIO(){
    LPC_GPIO2->FIODIR |=  (1 << 0) | (1 << 1 ) |( 1 << 2 );

    
}

void ADC_StarConvertion(){

    LPC_ADC->ADCR &= ~(7 << 24);
    LPC_ADC->ADCR |= (1 << 24);
}

void configST(){
    Systick_config(1000000); //10ms
}

void Systick_Handler(){
     static uint32_t diez = 10;
     diez--;
if(diez== 0){
    LPC_GPIO2->FIOCLR |= LED_AZUL | LED_ROJO |LED_VERDE;
if(ADC0Value<=1240){
        LPC_GPIO2->FIOSET |= LED_AZUL;
        
    }else if(ADC0Value>1240 && ADC0Value <= 2482 ){
        LPC_GPIO2->FIOSET |= LED_VERDE;
    }else{
        LPC_GPIO2->FIOSET |= LED_ROJO;
    }
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
    
}

