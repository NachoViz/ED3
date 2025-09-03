#include<lpc1769.h>


#define BIT_MASK(x)  (0x1 << (x))
#define BITS_MASK(x,s)  (((0x1 << (x))-1 << (s)))

#define LED_MASK     BITS_MASK(4,0)




int main(){

        for (volatile int i = 0; i < 32; i++) {
        int estado = (LPC_GPIO0->FIOPIN >> i) & 1;
        // Ahora 'estado' vale 1 si el pin i está en alto, 0 si está en bajo
    }


    while(1){

        return 0;
    }

}

void configGPIO(void){

    LPC_SC->PCONP |= (1 << 15);   //Habilito el reloj y le doy power a los GPIO

    LPC_PINCON-> PINSEL0 &= (0x0000FFF << 0);
    LPC_PINCON-> PINSEL1 &= (0x0000FFF << 16);

    LPC_PINCON-> PINMODE()


    LPC_GPIO-> FIODIR |= (1 << 20 );
}