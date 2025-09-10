#include <LPC1769.H>

volatile uint8_t seconds_count = 0;
volatile uint8_t attempts = 0;
#define CCLK_FREQ 10000000 
#define SYSTICK_LOAD_VALUE (CCLK_FREQ - 1) 

void configGPIO();
void configSysTick();
void configEINT();
void conf_clav();

int main() {
    configGPIO();
    configSysTick();
    configEINT();
    
    while(1) {
        __WFI(); 
    }
}

void configGPIO() {
    // P0.6 (Sensor de Puerta) - Entrada
    LPC_GPIO0->FIODIR &= ~(1 << 6);
    // P2.0 - P2.3 (DIP Switch) - Entradas
    LPC_GPIO2->FIODIR &= ~(0xF << 0);
    // P1.11 (Buzzer) - Salida, inicialmente apagado
    LPC_GPIO1->FIODIR |= (1 << 11);
    LPC_GPIO1->FIOCLR |= (1 << 11);
}


void configSysTick() {
    SysTick->LOAD = SYSTICK_LOAD_VALUE;
    SysTick->VAL = 0;
    SysTick->CTRL = 0; 
}

void SysTick_Handler() {
    
    if(((LPC_GPIO2->FIOPIN >> 0) & 0xF) == 0x0A) { 
        LPC_GPIO1->FIOCLR |= (1 << 11); 
        SysTick->CTRL = 0; // Detiene el SysTick
        seconds_count = 0;
        attempts = 0;
        return; // Salir de la rutina
    }
    
    // Si la clave es incorrecta, se incrementa el contador de segundos
    seconds_count++;
    
    if(seconds_count == 30) {
        // Han pasado 30 segundos, activa la alarma
        LPC_GPIO1->FIOSET |= (1 << 11); // Activa el buzzer
        SysTick->CTRL = 0; // Detiene el SysTick
    }
}

// Configuración de la interrupción del GPIO para el pin del sensor (P0.6)
void configEINT() {
    // Habilita la interrupción por flanco de subida en P0.6
    LPC_GPIOINT->IO0IntEnR |= (1 << 6); 
    // Limpia la bandera de interrupción en P0.6
    LPC_GPIOINT->IO0IntClr |= (1 << 6); 
    // Habilita la interrupción del GPIO en el NVIC
    NVIC_EnableIRQ(GPIO_IRQn);
}

// Rutina de interrupción del GPIO
void GPIO_IRQHandler() {
    // Verifica si la interrupción fue causada por el pin P0.6
    if (LPC_GPIOINT->IO0IntStatR & (1 << 6)) {
        // La puerta se abrió, reinicia el contador de segundos y los intentos
        seconds_count = 0;
        attempts = 0;
        
        // Habilita el SysTick para iniciar el conteo de 30 segundos
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

        // Limpia la bandera de interrupción del pin P0.6
        LPC_GPIOINT->IO0IntClr |= (1 << 6);
    }
}