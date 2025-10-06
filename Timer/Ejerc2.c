#include<LPC1679.H>

void configGPIO();
void configST();

int main(){
    configGPIO();
    configST();
    
    while(1){

    }

}

void configGPIO(){

}


void timerInit(){
LPC_SC->PCONP |= (1 << 1);    //TIMER0
LPC_SC->

NVIC_EnableIRQ(TIMER_IRQn);
}

void timer_IRQHandler(){

LPC_TMR0->IC
}