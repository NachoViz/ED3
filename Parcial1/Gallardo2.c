#include "LPC17xx.h"

volatile uint8_t memoria[10];
volatile uint32_t contador_numeros = 0;
volatile uint8_t prioridad_actual = 0;

// Prototipos de funciones
void configGPIO(void);
void agregar_numero(uint8_t nuevo_valor);
void EINT3_IRQHandler(void);

void EINT3_IRQHandler(void) {
    
    // Leer el valor de los 4 pines de entrada (P0.0 a P0.3).
    uint8_t valor_leido = LPC_GPIO0->FIOPIN & 0xF;
    
    // Guardar el nuevo número en el array y desplazar los anteriores.
    agregar_numero(valor_leido);
    
    // Incrementar el contador.
    contador_numeros++;
    
    
    if (contador_numeros >= 200) {
        
        
        if (prioridad_actual < 15) {
            prioridad_actual++;
            NVIC_SetPriority(EINT3_IRQn, prioridad_actual);
        } else {
            
            LPC_GPIOINT->IO0IntEnF &= ~(0xF);
            NVIC_DisableIRQ(EINT3_IRQn);
        }
        
        
        contador_numeros = 0;
    }
    
    
    LPC_GPIOINT->IO0IntClr = 0xF;
}


void agregar_numero(uint8_t nuevo_valor) {
    
    
    for (int i = 8; i >= 0; i--) {
        memoria[i + 1] = memoria[i];
    }
    
    
    memoria[0] = nuevo_valor;
}

void configGPIO(void) {
    
    LPC_PINCON->PINSEL0 &= ~(0xFF);
    
    LPC_GPIO0->FIODIR &= ~(0xF);
    
    LPC_GPIOINT->IO0IntEnF |= 0xF;
    
    NVIC_SetPriority(EINT3_IRQn, 0);
    NVIC_EnableIRQ(EINT3_IRQn);
}

int main(void) {
    
    for (int i = 0; i < 10; i++) {
        memoria[i] = 0;
    }
    
    configGPIO();
    
    while(1) {
    }
    
    return 0;
}