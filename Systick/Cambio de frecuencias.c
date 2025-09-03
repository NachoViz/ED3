#include<iostd>
//El ejercicio consta de tener en dos pines salidas que generen una onda cuadrada de una X frecuencia 
// Cuand oestas ondas coincidan se aumenta la frecuencia de la primera X*3 
//Puedo asumir que lo que estoy tratando de controlar es un led, que cuando no hay nada pulsado tiene un periodo de 0.1s
// cuando aprieto el boton la frecuencia aumenta X*3 osea pasar de 10HZ a 30hz
//Con el systick puedo contar hasta 0.167ms

const uint32_t TIEMPO_NORMAL = 10000000;
const uint32_t TIEMPO_RAPDIO = 3000000; 
{
    /* data */
};

void configGPIO();
void configST();


int main(){ 
    void configGPIO();
    void configST();

    while(1){

    }

}

void configGPIO(){
    //SUPONGO CONFIGURACION INICIAL TODOS ENTRADAS POR GPIO
    //Configuro dos puertos como GPIO no hacia falta aca por lo menos, solo cuando quiera usar interrupcion externa

    //LPC_PINCON->PINSEL1 |= (3 << 0);      //P0.16  ->PINSEL(2X+1) 2(Y-16)+1
    //LPC_PINCON->PINSEL2 |= ~(3 << 10);        //P1.5 -> PINSEL2 BIT 11  ENTRADA

    //PLACA NUEVA ES ACTIVO POR ALTO HAGO UN PULL-DOWN PARA ANTIRREBOTE
    LPC_PINCON->PINMODE3 |= (3 << 10);

    //CONFIG IN/OUT
    LPC_GPIO0->FIODIR |= (3 << 16 );        //P0.16 SALIDA
    LPC_GPIO1->FIODIR |= ~(3 << 5);          //P1.5 ENTRADA


    LPC_GPIO0->FIOSET |= (1 << 16);

}

void configST(){                                      //2.000.000 = 20ms
    Systick_config(TIEMPO_NORMAL-1);                         //2^24-1 = 0.167 SEG  con un load de 100.000 = 1,6miliseg

}

void Systick_Handler(){
    if( LPC_GPIO1->FIOPIN & (1 << 5)){  //El boton no esta presionado
        
        periodo_requerido = TIEMPO_NORMAL;

    }else{
        periodo_requerido = TIEMPO_RAPIDO;
    }

    if(Systick->LOAD != periodo_requerido){
        Systick->LOAD = periodo_requerido;
        Systick->VAL = 0;
    }

    LPC_GPIO0->FIOSET ^= 1 << 5; 

}

