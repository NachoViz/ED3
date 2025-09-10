#include<LPC1679.H>

const uint8_t maximoDato = 10;
const uint16_t PrioritySetting= 1; 
const uint8_t MEMORIA [];
volatile uint32_t count;
volatile uint8_t is_full;

void configGPIO();


int main(){
    configGPIO();
    
    while(1){

    }

}

void configGPIO(){
    LPC_GPIO0->FIODIR &= ~(0xF);
    LPG_GPIOINT->IO0IntEnF |= (0xF);
    
    NVIC_EnableIRQ(EINT3_IRQn);
    NVIC_SetPriority(EINT3_IRQn,SettingPriority);
}

void EINT3_Handler(){
    const uint8_t valor = LPC_GPIO0->FIOPIN &= 0xF ;
    update_memory(valor);
}

void update_memory(uint8_t nuevo_valor){
    count++; //cantidad de datos

    for(uint32_t )
}

void setearPrioridad(){
    if(count>= 200){
        count = 0;
        SettingPriority++;
        if(SettingPriority > 32){
            NVIC_DisableIRQ(EINT3_IRQn);
        }

    }
}
