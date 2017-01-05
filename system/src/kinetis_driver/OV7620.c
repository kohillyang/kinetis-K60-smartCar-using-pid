#include "OV7620.h"
#include "exti.h"
#include "dma.h"
#include "gpio.h"

void OV7620_init (void)
{
    exti_init(HREF_PORT,HREF_PIN,rising_down);       //行中断，PORTD13 ，上升沿触发中断，内部下拉
    exti_init(VSYN_PORT,VSYN_PIN,falling_down);      //场中断，PORTD14 ，下降沿触发中断，内部下拉 
    //DMA通道0初始化，PTD12上升沿触发DMA传输，源地址为PTE_BYTE0_IN，目的地址为：IMG_BUFF ，每次传输1Byte，传输CAMERA_W次后停止传输
    DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&DATA_IN, IMG_BUFF, PCLK, DMA_BYTE1, CAMERA_W , DMA_rising_keepon);
    DMA_DIS(CAMERA_DMA_CH);         //停止DMA传输。行中断中打开DMA传输
}






