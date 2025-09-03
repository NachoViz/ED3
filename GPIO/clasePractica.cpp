#include"LPC"


#define DELAY_TIME 100000

int main(){
    configGPIO();

    while(1){
        LPC_GPIO3->FIOCLR |= (1 << 25);
        delay();
        LPC_GPIO3->FIOSET |= (1 << 25 )
    }

    return 0;
}

void configGPIO(void){

    LPC_PINCON->PINSEL0 &= -(0x0003FFF);        //son 13 pin por puerto
    //LPC_PINCON->PINSEL7 &= -(0B11 << 18);

    LPC_GPIO0->FIODIR |= (0x7F << 0 ); // Prendo el led 
    //LPC_GPIO3->FIODIR |= (1 << 25); // Prendo el led 

    LPC_GPIO0->FIOCLR = 0X7F
    
    LPC_GPIO3->FIOSET |= (1 << 25); // Apago el led 
}

void delay(){
    for(int i = 0; i < DELAY_TIME; i++);   
}

