#include <LPC1769.H>

// GPIO pins for the 4-bit input switches (assuming P0.0 to P0.3)
#define INPUT_PINS_MASK 0x0F 

// Circular buffer to store the last 10 numbers
#define BUFFER_SIZE 10
volatile uint8_t data_buffer[BUFFER_SIZE];
volatile int8_t head = 0; // Index of the next available position
volatile uint32_t input_counter = 0;

// Maximum and minimum interrupt priority values for LPC1769
#define MAX_PRIORITY 0 // Higher number means lower priority
#define MIN_PRIORITY 255

void configGPIO();
void configGPIOInterrupt();

int main() {
    configGPIO();
    configGPIOInterrupt();
    
    // Main loop: program remains in a low-power state, waiting for interrupts.
    while (1) {
        __WFI(); // Wait For Interrupt instruction
    }
}

/**
 * @brief Configures GPIO pins for input switches.
 * Assumes P0.0 to P0.3 are used as inputs.
 */
void configGPIO() {
    // Configure P0.0-P0.3 as inputs
    LPC_GPIO0->FIODIR &= ~(INPUT_PINS_MASK);
    
    // External pull-up resistors are mentioned, so no need for internal pull-up/pull-down
    // LPC_PINCON->PINMODE_OD0 &= ~INPUT_PINS_MASK; 
}

/**
 * @brief Configures GPIO interrupt for P0.0-P0.3.
 */
void configGPIOInterrupt() {
    // Enable interrupt for all four pins on port 0, for both rising and falling edges.
    LPC_GPIOINT->IO0IntEnR |= INPUT_PINS_MASK;
    LPC_GPIOINT->IO0IntEnF |= INPUT_PINS_MASK;
    
    // Set the highest possible interrupt priority initially
    NVIC_SetPriority(EINT3_IRQn, MAX_PRIORITY);
    
    // Enable the GPIO interrupt in the NVIC
    NVIC_EnableIRQ(EINT3_IRQn);
}

/**
 * @brief Stores a new 4-bit number in the circular buffer.
 *
 * @param new_data The 4-bit number to be stored.
 */
void store_data(uint8_t new_data) {
    // Store the new number at the current head position
    data_buffer[head] = new_data;
    
    // Move the head index to the next position in the buffer (circular)
    head++;
    if (head >= BUFFER_SIZE) {
        head = 0;
    }
}

/**
 * @brief Handles the GPIO interrupt.
 * This function is executed whenever a switch changes state.
 */
void EINT3_IRQHandler() {
    uint32_t pending_int_flags = LPC_GPIOINT->IO0IntStatR | LPC_GPIOINT->IO0IntStatF;
    
    // Check if the interrupt is from any of the input pins
    if (pending_int_flags & INPUT_PINS_MASK) {
        // Read the 4-bit number from the input pins
        uint8_t current_data = LPC_GPIO0->FIOPIN & INPUT_PINS_MASK;
        
        // Store the number in the circular buffer
        store_data(current_data);
        
        // Increment the counter for priority management
        input_counter++;
        
        // Decrease interrupt priority every 200 inputs
        if (input_counter % 200 == 0 && NVIC_GetPriority(EINT3_IRQn) < MIN_PRIORITY) {
            NVIC_SetPriority(EINT3_IRQn, NVIC_GetPriority(EINT3_IRQn) + 1);
            
            // Check if we have reached the minimum priority
            if (NVIC_GetPriority(EINT3_IRQn) == MIN_PRIORITY) {
                // Disable GPIO interrupts when minimum priority is reached
                NVIC_DisableIRQ(EINT3_IRQn);
            }
        }
    }
    
    // Clear the interrupt flags to avoid re-entering the handler
    LPC_GPIOINT->IO0IntClr |= INPUT_PINS_MASK;
}