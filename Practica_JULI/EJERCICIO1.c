#include<LPC1679.H>

void configGPIO();
void configST();

const uint8_t tabla[] = {};
volatile uint8_t count;
volatile uint8_t is_fast;
volatile uint8_t is_pause;
#define SEC_FREC 16000000;
#define MILI_FREC 1600000;

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

    LPC_SC->EXTPOLAR |= ~(1 << 0); 
    LPC_SC->EXTPOLAR &= ~(1 << 1); 
    LPC_SC->EXTPOLAR &= ~(1 << 2); 

    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
}


void configST(){
    Systick->LOAD = SEC_FREC;
    Systick->VAL = 0; 
    Systick->CTRL = 0x07;
}

void Systick_Handler(){
    if(is_fast){
        
    }
    if(!is_pause){
        count++
        if(count<=9){
            TeQueroActualizado(count);
        }else{
            count = 0;
        }
    }
}

void TeQueroActualizado(value){
    LPC_GPIO0->FIOCLR |= 0x7F;
    LPC_GPIO0->FIOSET |= tabla[value] << 0;

}


void EINT0_Handler(){
        count = 0; 
        TeQueroActualizado(count);
        Systick->LOAD = TIME;
        Systick->VAL = 0;
        Systick->CTRL = 0x07;
        
    LPC_SC->EXTINT |= ( 1 << 0 );
}
//pausa y continue
void EINT1_Handler(){
    is_pause ^= 1 ; 
    LPC_SC->EXTINT |= ( 1 << 1 );
}

void EINT2_Handler(){
    is_fast ^= 1;
    if(is_fast){
        Systick->LOAD = SEC_FREC;
    }else{
        Systick->LOAD = MILI_FREC;
    }
}
