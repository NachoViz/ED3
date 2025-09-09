#include <LPC17xx.h>

void configGPIO_Interrupt(void) {
    // 1. Configurar P0.10 como entrada GPIO
    LPC_GPIO0->FIODIR &= ~(1 << 10);    // Entrada
    
    // 2. Configurar pull-down (para botón activo por alto)
    LPC_PINCON->PINMODE0 &= ~(3 << 20); // Limpiar
    LPC_PINCON->PINMODE0 |= (2 << 20);  // 10 = pull-down
    
    // 3. Habilitar interrupción por flanco de bajada en P0.10
    LPC_GPIOINT->IO0IntEnF |= (1 << 10);
    
    // 4. Limpiar bandera de interrupción
    LPC_GPIOINT->IO0IntClr = (1 << 10);
    
    // 5. Habilitar interrupción GPIO en NVIC
    NVIC_EnableIRQ(GPIO_IRQn);
}

void GPIO_IRQHandler(void) {
    // Verificar si la interrupción fue por P0.10 (flanco bajada)
    if (LPC_GPIOINT->IO0IntStatF & (1 << 10)) {
        
        LPC_GPIO0->FIOPIN ^= (1 << 22); // toggle LED en P0.22
        
        // Limpiar bandera de interrupción
        LPC_GPIOINT->IO0IntClr = (1 << 10);
    }
}