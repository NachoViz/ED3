#include<LPC1679.H>
#define TIME 10000000;

const int tabla [] = {3F,06,5B,4F,66,6D,7D,07,7F,67};

void configGPIO();
void configST();
void configEINT();

int main(){
    configGPIO();
    configST();
    
    while(1){

    }

}

void configGPIO(){
    LPC_GPIO0->FIODIR |= (0X7F << 0); 
    LPC_GPIO2->FIODIR &= ~(7 << 10 );

    LPC_PINCON->PINSEL4 |= (1 << 20) | (1 << 22) | (1 << 24); //EINT0-1-2 
    LPC_PINCON->PINMODE4 |= (3 << 20);
    
}

void configST(){
    Systick->LOAD = TIME;
    Systick->VAL = 0; 
    Systick->CTRL = 0x07;
}

void Systick_Handler(){
    if (!is_paused) {
        count++;
        if (count > 9) {
            count = 0;
        }
    }
    update_display(count);
}

void configEINT(){

    LPC_SC->EXTPOLAR &= ~(~(1 << 0) | (1 << 1) | (1 << 2)); // Flanco de bajada

    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
}

// Actualizar el display
void update_display(uint8_t value) {
    LPC_GPIO0->FIOCLR |= 0x7F;
    LPC_GPIO0->FIOSET |= (segment_codes[value] & 0x7F); // Escribe el nuevo valor
}


void EINT0_IRQHandler(){
    //reinicia la cuenta y hasta que no cambia de valor se mantiene en 0
    cuenta = 0; 
    contador = 0; 
    Systick->LOAD = TIME;
    Systick->VAL = 0; 
    Systick->CTRL = 0x07; 
}

void EINT1_IRQHandler(){
    if(LPC_GPIO2->FIOPIN & 1 << 11){
        count
    }
}

void EINT2_IRQHandler(){


}