#include "OV7620.h"
#include "exti.h"
#include "dma.h"
#include "gpio.h"

void OV7620_init (void)
{
    exti_init(HREF_PORT,HREF_PIN,rising_down);       //���жϣ�PORTD13 �������ش����жϣ��ڲ�����
    exti_init(VSYN_PORT,VSYN_PIN,falling_down);      //���жϣ�PORTD14 ���½��ش����жϣ��ڲ����� 
    //DMAͨ��0��ʼ����PTD12�����ش���DMA���䣬Դ��ַΪPTE_BYTE0_IN��Ŀ�ĵ�ַΪ��IMG_BUFF ��ÿ�δ���1Byte������CAMERA_W�κ�ֹͣ����
    DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&DATA_IN, IMG_BUFF, PCLK, DMA_BYTE1, CAMERA_W , DMA_rising_keepon);
    DMA_DIS(CAMERA_DMA_CH);         //ֹͣDMA���䡣���ж��д�DMA����
}






