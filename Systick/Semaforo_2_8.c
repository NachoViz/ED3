#include<LPC1679.H>
//incompleto

#define Tiempo_requerido 10000000;
#define count1 = 0; 
#define count2 = 0; 


void configSemaforo(){
    int ROJO = 25; 
    int AMARILLO = 5;
    int VERDE = 25;


}

void 

int main(){
    configGPIO();
    configST();
    while(1){
        //vacio todo controlado en el systick
    }
}

void configGPIO(){
    LPC_GPIO1->FIODIR = ( 0x7 << 0)//P1.0-3

    LPC_GPIO1->FIOCLR | = ( 0X7 << 0);
}

void configST(){
    Systick_config(Tiempo_requerido); //100 ms

}

void Systick_Handler(){

    

}
