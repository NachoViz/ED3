

#include "lpc17xx_gpio.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_gpdma.h"

//ESTO ESTA EN EL MAPA DE MEMORIA (LPC176x_5x_User_Manual.pdf)
#define DAC_COUNT 1000                      // Valor del contador para la frecuencia de actualizacion del DAC
uint16_t srcAddr = 0x2007C000;              // Direccion de memoria fuente
uint16_t *dstAddr = 0x4008C000;             // Direccion de memoria destino (DAC)


void configGPIO();
void configDAC();
void configDMA();

void configGPIO(){
    PINSEL_CFG_Type PinCfg;

    // Configuramos el pin P0.26 como salida DAC
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 26;
    PINSEL_ConfigPin(&PinCfg);
}

void configDAC(){
    DAC_Init();

    //DAC_CONVERTER_CFG_Type dacConfig = {ENABLE, ENABLE, ENABLE};  es lo mismo hacer esto
    DAC_CONVERTER_CFG_Type dacConfig = {0};             //Siempre hago esto para evitar errores
    dacConfig.counterEnable = ENABLE;
    dacConfig.dmaEnable = ENABLE;
    dacConfig.doubleBufferEnable = ENABLE;

    DAC_ConfigDAConverterControl(&dacConfig);
    DAC_SetDMATimeOut(DAC_COUNT);
}

void configDMA(){
    GPDMA_Init();

    GPDMA_Channel_CFG_Type dmaChannelCfg;
    dmaChannelCfg.ChannelNum = GPDMA_Channel_0;
    dmaChannelCfg.TransferSize = 256;                                // Numero de muestras a transferir
    dmaChannelCfg.TransferWidth = GPDMA_WIDTH_BYTE;                 // Ancho de transferencia (8 bits para DAC)
    dmaChannelCfg.TransferType = GPDMA_TRANSFERTYPE_M2P;            // Transferencia de memoria a periferico
    dmaChannelCfg.SrcMemAddr = (uint32_t)srcAddr;                       /*Direccion de memoria fuente*/; // Direccion de memoria fuente
    dmaChannelCfg.DstMemAddr = (uint32_t) &LPC_DAC->DACR;                                   // No se usa en M2P
    dmaChannelCfg.DstConn = GPDMA_DAC;                                                  // Conexion al DAC
    dmaChannelCfg.LinkedList = (uint32_t)&dmaLLI;                                       // Bloque del main dmaLLI

    GPDMA_Setup(&dmaChannelCfg);
    GPDMA_ChannelCmd(0, ENABLE);}



int main(){

    //LISTA ENLAZADA(OSEA SIGUIENTE BLOQUE QUE VE LA DMA)
    GDMA_LLI_Type dmaLLI = {0};
    dmaLLI.SrcAddr = (uint32_t)srcAddr;                               // Direccion de memoria fuente
    dmaLLI.DstAddr = (uint32_t)&LPC_DAC->DACR;                          // Direccion de memoria destino (DAC)
    dmaLLI.NextLLI = (uint32_t)&dmaLLI;                               // Apunta a si misma  (Transmite los 256 datos y vuelve a empezar)
    dmaLLI.Control = (256)                      //TransferSize
                    | (1 << 12)                 //SBSize
                    | (1 << 18)                 //SWidth  (HALFWORD 16bits)
                    | (1 << 21);                //DWidth  (HALFWORD 16bits)      // Control de la transferencia
    dmaLLI.Config = (1 << 11) | (GPDMA_DAC << 1);

    configGPIO();
    configDAC();
    configDMA();

    while(1){

    }

}
