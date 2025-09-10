    #include<LPC1679.H>

    void configGPIO();
    void configST();
    void configEINT();
    void conf_clave();
    volatile uint8_t count;

    int main(){
        configGPIO();
        configST();
        configEINT();
        
        while(1){

        }

    }

    void configGPIO(){
        LPC_GPIO0->FIODIR &= ~( 1 << 6 );
        LPC_GPIO2->FIODIR &= ~(0xF << 0);

        LPC_GPIO1->FIODIR &= ~(1 << 11 );
        LPC_GPIO1->FIOCLR |= ( 1 << 11 );
    }

    void configST(){
        Systick->LOAD = TIME;
        Systick->VAL = 0;
        Systick->CTRL = 0;
    }

    void Systick_Handler(){
        count++;
        if(count == 30){
            LPC_GPIO1->FIOSET |= ( 1 << 11 ); //Activ_Alarma
            count = 0;
        }
    }

    void configEINT(){
        LPC_GPIOINT->IO0IntEnR |= 1 << 6 ; 
        LPC_GPIOINT->IO0IntClr |= 1 << 6;

        NVIC_EnableIRQ(EINT3_IRQn);
    }

    void conf_clav(){
        uint16_t Claro = (LPC_GPIO2->FIOPIN >> 0) & 0xF; 
        if(Claro & 0x0A){
            clave = 0;
            LPC_GPIO1->FIOCLR |= (1 << 11 );  //Desactivo la alarma
        }else{
            clave++;
        }
        if(clave == 2 ){
            LPC_GPIO1->FIOSET |= 1 << 11;   //Activ_Alarma()
        }
    }

    void EINT3_Handler(){
        if(LPC_GPIOINT->IO0IntStatR & ( 1 << 6 )){
            Systick->CTRL = 0x07;
            conf_clav(); 
        }
    
        LPC_GPIOINT->IO0IntClr |= 1 << 6;
    }
