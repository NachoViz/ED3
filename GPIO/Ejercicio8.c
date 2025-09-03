#include<lpc1769.h>


#define BIT_MASK(x)  (0x1 << (x))
#define BITS_MASK(x,s)  (((0x1 << (x))-1 << (s)))

#define LED_MASK     BITS_MASK(4,0)




int main(){

     
    LPC_PINCON->FIOPIN = 

}

void configGPIO(void){

    LPC_SC->PCONP |= (1 << 15);   //Habilito el reloj y le doy power a los GPIO

    LPC_PINCON-> PINSEL0 &= (0x0F << 0);    //P0.0
    LPC_PINCON-> PINSEL4 &= ~(0x08F << 0);   //P2.0-P2.7   

    LPC_PINCON-> PINMODE()


    LPC_GPIO-> FIODIR |= (1 << 20 );
}