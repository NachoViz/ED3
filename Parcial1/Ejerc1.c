#include<LPC1679.H>

void configGPIO();
void configST();

uint8_t ticket_val = 1;
uint8_t sensorDePres;
uint32_t timeConf = 10000000; //10mill para 0.1seg
uint8_t buttonCount;

int main(){
    configGPIO();
    configST();
    while(1){
        boton_pres();

    }

}

void configGPIO(){
    LPC_GPIO1->FIODIR |= 1 << 5;            //LED
    LPC_GPIO2->FIODIR &= ~(1 << 10);        //EINT
    LPC_GPIO0->FIODIR |= 1 << 15;           //MOTOR
    LPC_GPIO0->FIODIR &= ~(1 << 10);        //boton

    LPC_PINCON->PINMODE0 |= 3 << 20;        //PULL-DOWN

    LPC_GPIO1->FIOCLR |= ( 1  << 5);

}

void boton_pres(){
    if(LPC_GPIO0-> FIOPIN & ~(1 << 10)){
        delay();
        Button++;
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
    Systick->CTRL = 0x07; 
}

void Systick_Handler(){
    volatile uint16_t count;
    count++;
    if( count == ticks){
        LPC_GPIO0->FIOCLR |= ( 1 << 15); //Cierro la barrera
        ticks = 0;
    }

}

void EINT0_IRQHandler(){
    if(ticket_val){
        LPC_GPIO0->FIOSET |= ( 1 << 15 );  //abro la barrera ticket y sensor en alto
    }else{
        LPC_GPIO1->FIOSET |= ( 1 << 5); //PRENDO LED ROJO
    }
    LPC_SC->EXTINT0 = 1 << 0;
}
