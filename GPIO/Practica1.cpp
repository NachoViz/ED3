//Conectar un 7 segmentos y mostrar del 1 al 7 
#include"LPC17xx.h"

#define DELAY_TIME 100000

void delay();

int main(){

    configGPIO();
    while (1)
    {
        LPC_GPIO0->FIOSET |=(1 << 20);
        LPC_GPIO0->FIOCLR |= (1 << 21);
        LPC_GPIO0->FIOCLR |= (1 << 22);
        delay();

        LPC_GPIO0->FIOSET |=(1 << 21);
        LPC_GPIO0->FIOCLR |= (1 << 20);
        delay();

        LPC_GPIO0->FIOSET |=(1 << 22);
        LPC_GPIO0->FIOCLR |= (1 << 21);
        delay();    

        LPC_GPIO0->FIOCLR |= (1 << 22);
        delay();


    }
    

}


void configGPIO(void){
    LPC_PCGPIO->PCONP |= (1 << 15); // Habilito el periferico GPIO BIT15

    LPC_PINCON->PINSEL1 &= ~(3 << 8);   //P0.20
    LPC_PINCON->PINSEL1 &= ~(3 << 10);  //P0.21 
    LPC_PINCON->PINSEL1 &= ~(3 << 12);  //P0.22

    LPC_GPIO0->FIODIR |= (1 << 20); // Configuro P0.20 como salida
    LPC_GPIO0->FIODIR |= (1 << 21);
    LPC_GPIO0->FIODIR |=(1 << 22);

}

void delay(void){
    for(volatile int i=0; i<DELAY_TIME; i++);
}



/*

Ejercicio: Semáforo Sencillo

Tu tarea es modificar el código que ya hemos visto para controlar tres LEDs, simulando un semáforo básico.
Instrucciones
Configurar tres pines: Elige tres pines GPIO diferentes (por ejemplo, P0.20, P0.21 y P0.22) y configúralos todos como salidas.
 Estos pines representarán el LED rojo, amarillo y verde.
Crear una secuencia de semáforo: Dentro del bucle while(1), implementa la siguiente secuencia:
Enciende el LED rojo (pon su pin en HIGH).
Apaga los LEDs amarillo y verde (pon sus pines en LOW).
Espera un tiempo (usa un bucle de retardo como el del ejemplo).
Enciende el LED amarillo (pon su pin en HIGH).
Apaga el LED rojo.
Espera un tiempo (un retardo más corto).
Enciende el LED verde (pon su pin en HIGH).
Apaga el LED amarillo.
Espera un tiempo (un retardo similar al del rojo).
Apaga el LED verde para volver al inicio del ciclo.
Espera un tiempo.
Para ayudarte:
Puedes crear una función de inicialización que configure los tres pines a la vez.
Recuerda usar los registros FIOSET y FIOCLR para controlar el estado de cada LED.
Asegúrate de que solo un LED esté encendido a la vez, excepto en la transición del rojo al verde
 (que en un semáforo real suele ser una fase de "rojo y amarillo"). Por ahora, para simplificar,
  puedes apagar el rojo antes de encender el amarillo.
Una vez que lo tengas, puedes mostrarme el código para revisarlo juntos. ¡Vamos a hacerlo!