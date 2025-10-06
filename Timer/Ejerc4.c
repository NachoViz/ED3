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

void configST(){

}

void configTIMER(){

    LPC_SC->PCONP |= 1<< 1 ; 
    LPC_SC->PINSEL7 |= 3 << 18;

    LPC_TIM0->
}