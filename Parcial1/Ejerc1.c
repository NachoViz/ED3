#include<LPC1679.H>

void configGPIO();
void configST();

    uint8_t ticket_val = 1;
    uint8_t sensorDePres;
    uint32_t timeConf = 7000000; //10mill para 0.1seg
    uint8_t buttonCount;

    volatile uint16_t count;

int main(){
    configGPIO();
    configST();

    while(1){
        
    }
}

void configGPIO(){
    LPC_GPIO1->FIODIR |= 1 << 5;            //LED
    LPC_GPIO2->FIODIR &= ~(1 << 10);        //EINT sensor de presencia 
    LPC_GPIO0->FIODIR |= 1 << 15;           //MOTOR
    LPC_GPIO0->FIODIR &= ~(1 << 15);        //boton de config

    LPC_PINCON->PINMODE4 |= 3 << 20;        //PULL-DOWN
    LPC_PINCON->PINMODE2 |= 3 << 20;

    LPC_GPIO1->FIOCLR |= ( 1  << 5);

}

void boton_pres(){
    //DEBERIA SER GPIO ESTO, TENGO QUE CONFIGURARLO 
    if(ticket_val &&!(LPC_GPIO0->FIOPIN & (1 << 15))){
        delay();
        ButtonCount++;
    }
    if(ButtonCount < 5){
    switch(ButtonCount){
                case 0:
                ticks =  50;
                break;
                case 1: 
                ticks =  50;
                break;
                case 2:
                ticks = 100;
                break;
                case 3: 
                ticks = 200;
                break;
                case 4: 
                ticks = 400;
                break;
            }
        }else{
            ButtonCount = 0;
            ticks=50;
        } 
}

void delay(){
    int i = 2000000; //2mill
    for( i ; i>0; i--); //20miliseg
}

void configEINT(){
    LPC_PINCON->PINSEL4 |= 1 << 20;
    LPC_SC->EXTMODE0 &= ~(1 << 0);
    LPC_SC->EXTPOLAR0 |= 1 <<0; 

    NVIC_EnableIRQ(EINT0_IRQn);
}

void configST(){
    Systick->LOAD = timeConf;
    Systick->VAL = 0;
    Systick->CTRL = 0; 
}

void Systick_Handler(){
    count++;
    if( count == ticks){
        LPC_GPIO0->FIOCLR |= ( 1 << 15); //Cierro la barrera
        count = 0;
        ticks = 0;
        Systick->CTRL |= ~(1 << 0);
    }

}

void EINT3_IRQHandler(){
    if(ticket_val){
        LPC_GPIO0->FIOSET |= ( 1 << 15 );  //abro la barrera ticket y sensor en alto
         // Reinicio y habilito el SysTick para que empiece a contar
        SysTick->LOAD = timeConf; // Para 100ms
        SysTick->VAL = 0;
        SysTick->CTRL = 0x07;

    }else{
        LPC_GPIO1->FIOSET |= ( 1 << 5 ); //PRENDO LED ROJO
    }
    
    LPC_SC->EXTINT = 1 << 3;
}
