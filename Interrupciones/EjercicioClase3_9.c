#include<LPC1679.H>

#define TIEMPO_NORMAL 10000000;   //100ms
#define TIEMPO_RAPIDO 3300000; //30ms
void configGPIO();
void delay(TIEMPO_NORMAL);

int main(){
    configGPIO();

    while(1){
        if(count%3){
            tiempo = TIEMPO_RAPIDO;
        }else{
            tiempo = TIEMPO_LENTO;
        }
        LPC_GPIO0->FIOPIN ^= (1 << 15);
        delay(tiempo);
        
        
    }
}

void configGPIO(){
    LPC_GPIO0->FIODIR |= (3 << 15); 

    LPC_GPIOINT->IO0IntEnR |= (1 << 15); //Interrupcion por flanco de subida
    LPC_GPIO0INT->IO0IntClr |= (1 << 15); 

    NVIC_EnableIRQn(GPIO_IRQn);
    //Preguntar si hace falta limpiar la interrupcion

    LPC_GPIO0->FIOSET |= (1 << 15);
}

void GPIO_Handler(){ //pregunta si hay una interrupcion y cuenta
    if(LPC_GPIO0INT->IntStatR & ( 1 << 15)){
        count++;
        LPC_GPIO0INT->IntClr = (1 << 15);
    }
}

void delay(uint32_t a){
    for( volatile uint32_t b = 0 ; b < a ; b++ );
}