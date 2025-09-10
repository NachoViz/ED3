#include<LPC1679.H>

void configGPIO();
void configST();

const uint8_t tabla[] = {};
volatile uint8_t count;
volatile uint8_t is_fast;
volatile uint8_t is_pause;

int main(){
    configGPIO();
    configST();
    
    while(1){

    }

}

void configGPIO(){
    //ENTRADAS P2.10-11-12
    //SALIDAS  P0.0-6 
    LPC_GPIO0->FIODIR |= 0x7F << 0;                                 //7F = 0111 1111 
    LPC_GPIO2->FIODIR &= ~(0X7 << 10);                              //0111 

    LPC_PINCON->PINSEL4 |= (1 << 24) | (1 << 22 )  | (1 << 20);   //P2.10-12 
    LPC_PINCON->PINMODE4 |= (3 << 20);
    LPC_PINCON->PINMODE4 |= (00 << 22);
    LPC_PINCON->PINMODE4 |= (00 << 24);

    LPC_SC->EXTPOLAR |= 1 << 0; 
    LPC_SC->EXTPOLAR &= ~(1 << 1); 
    LPC_SC->EXTPOLAR &= ~(1 << 2); 

    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
}


void configST(){

}

void Systick_Handler(){

}


void EINT0_Handler(){
    if(LPC_GPIO2->FIOPIN & (1 << 10)){
        cuenta = 0; 
        TeQueroActualizado(cuenta);
        //
    }
}

void EINT1_Handler(){
    if(!(LPC_GPIO2->FIOPIN & (1 << 11))){
        Systick->CTRL = 0; 
    }
}

void EINT2_Handler(){
    
}
