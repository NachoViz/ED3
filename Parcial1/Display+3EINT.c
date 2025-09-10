#include <LPC1769.H>

volatile uint8_t count = 0; 
volatile uint8_t is_paused = 0;
volatile uint8_t is_fast = 0; 
const uint8_t tabla[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67
};

// Constantes para el reloj del sistema de 16MHz
#define CCLK_FREQ 16000000 
#define SEC_LOAD_VALUE (CCLK_FREQ - 1)
#define MS_LOAD_VALUE (CCLK_FREQ / 1000 - 1)

void configGPIO();
void configSysTick();
void configEINT();
void update_display(uint8_t value);

int main() {
    configGPIO();
    configSysTick();
    configEINT();

    while(1) {
        
    }
}

void configGPIO() {
    
    LPC_GPIO2->FIODIR &= ~((1 << 10) | (1 << 11) | (1 << 12));
    
    LPC_GPIO0->FIODIR |= 0x7F;

    LPC_PINCON->PINSEL4 |= (1 << 20) | (1 << 22) | (1 << 24);
}


void configSysTick() {
    SysTick->LOAD = SEC_LOAD_VALUE; // Velocidad por defecto: 1 segundo
    SysTick->VAL = 0;
    SysTick->CTRL = 0x07;
}


void configEINT() {
    // Configura los pulsadores para detectar flanco de bajada (falling edge)
    // Esto evita lecturas falsas cuando se suelta el botón
    LPC_SC->EXTPOLAR &= ~((1 << 0) | (1 << 1) | (1 << 2));

    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);
}

void update_display(uint8_t value) {
    LPC_GPIO0->FIOCLR |= 0x7F; 
    LPC_GPIO0->FIOSET |= (segment_codes[value] & 0x7F); 
}


void SysTick_Handler() {
    if (!is_paused) {
        count++;
        if (count > 9) {
            count = 0;
        }
    }   
    update_display(count);
}

// Reiniciar y mantener
void EINT0_IRQHandler() {
    
    if (!(LPC_GPIO2->FIOPIN & (1 << 10))) {
        count = 0;
        update_display(count);
        is_paused = 1; 
    } else {
        is_paused = 0; 
    }
    LPC_SC->EXTINT |= (1 << 0); 
}

// Pausar/Continuar
void EINT1_IRQHandler() {
    is_paused ^= 1; 
    LPC_SC->EXTINT |= (1 << 1); 
}

// Cambiar velocidad
void EINT2_IRQHandler() {
    is_fast ^= 1; // Invierte el estado de velocidad
    if (is_fast) {
        SysTick->LOAD = MS_LOAD_VALUE;
    } else {
        SysTick->LOAD = SEC_LOAD_VALUE;
    }
    LPC_SC->EXTINT |= (1 << 2); // Limpia la bandera de interrupción
}