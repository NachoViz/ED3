/* Configurar la interrupción externa EINT1 para que interrumpa por flanco de
bajada y la interrupción EINT2 para que interrumpa por flanco de subida. En la
interrupción por flanco de bajada configurar el systick para desbordar cada 25
mseg, mientras que en la interrupción por flanco de subida configurarlo para que
desborde cada 60 mseg. Considerar que EINT1 tiene mayor prioridad que EINT2.
 */
#include<LPC17xx.h>
using namespace std;

int main(){

    while(1 ){

    }
}

void configGPIO(){
    LPC_PINCON->PINSEL
}


void EINT0_Init(){
    
}

void EINT0_Handler(){

}

void EINT1_Init(){

}

void EINT1_Handler(){

}
