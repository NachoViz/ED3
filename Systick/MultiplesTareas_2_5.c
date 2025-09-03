#include<LPC1679.H>

#define Tiempo_requerido 10000000;
#define count1 = 0; 
#define count2 = 0; 

int main(){
    configGPIO();
    configST();
    while(1){
        //vacio todo controlado en el systick
    }
}

void configGPIO(){
    LPC_GPIO0->FIODIR = (3 << 0 ); //P0.0
    LPC_GPIO1->FIODIR = ( 0xF << 0)//P1.0-4

    LPC_GPIO0->FIOCLR |= ( 1 << 0);
    LPC_GPIO1->FIOCLR | = ( 0XF << 0);
}

void configST(){
    Systick_config(Tiempo_requerido); //100 ms
    count1++;
    count2++;

}

void Systick_Handler(){

    if(count2 >= 2 ){
        count2= 0; 
        LPC_GPIO1-> FIOPIN ^= 0XF << 0; 

    }
    if (count1 >= 5 )
    {
        LPC_GPIO0-> FIOPIN ^= 1 << 0;
        count1 = 0; 
    }

}
