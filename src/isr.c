#include "common.h"
#include "include.h"

extern u8  IMG_finish;  //�����������ж���ı���
extern u8  IMG_get;
extern int  H_count;
//extern u8 cmdBuff[10];
extern u8 Cmd;
 
 /**  
 author:cong
 version:1.0
 begin IRQ_Handlers
 **/

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�USART1_IRQHandler
*  ����˵��������1 �ж� ���� ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*  ��    ע��
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //�����ж�

    //����һ���ֽ����ݲ��ط�
    ch = uart_getchar (UART1);      //���յ�һ������
    uart_sendStr  (UART1, "\n�㷢�͵�����Ϊ��");
    uart_putchar (UART1, ch);       //�ͷ��ͳ�ȥ

    EnableInterrupts;		    //�����ж�
}

void PORTD_IRQHandler()
{
    u8  n=0;      //���ź�

    n=VSYN_PIN;
    if(PORTD_ISFR & (1<<n))           //PTD14�������ж�
    {
        PORTD_ISFR  |= (1<<n);        //д1���жϱ�־λ
        IMG_finish=0;
        IMG_get=1;
        H_count=1;
        DMA_DADDR(CAMERA_DMA_CH) = (u32)IMG_BUFF;    //�ָ���ַ     

    }

    n=HREF_PIN;
    if(PORTD_ISFR & (1<<n))           //PTD13�������ж�
    {
        PORTD_ISFR  |= (1<<n);          //д1���жϱ�־λ
        if(IMG_get==1)
        {
            DMA_EN(CAMERA_DMA_CH);     //ʹ��ͨ��CHn Ӳ������
            H_count++;
        }
    }
}

void DMA_CH0_Handler()
{
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);   //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
    DMA_DIS(CAMERA_DMA_CH);         //�ɼ���W�����ݺ�������DMA�жϣ�ֹͣDMA���䡣���ж��д�DMA����
    if(H_count > CAMERA_H)
    {
        IMG_finish=1;
        IMG_get=0;
        disable_irq(90);
    }
}

void UART1_IRQHandler()
{       
	DisableInterrupts;          //�����ж�      
	//����һ���ֽ����ݲ��ط�    
	/*uart_getstr(UART1, (char *)cmdBuff,10);
	printf("\n�㷢�͵�����Ϊ��%s",cmdBuff);      //���ͳ�ȥ
	buffu8_zero(cmdBuff, 10);*/
        Cmd=uart_getchar(UART1);
	//printf("\nyou sent char is��%c",cmd);      //���ͳ�ȥ
	EnableInterrupts;           //�����ж�    
}

void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //��ȡ��׽�ͱȽ�״̬  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //���жϱ�־λ

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //��ֹ���벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�жϣ�������main�����������Ҫ������
        //ͨ�� CH0��CH1��Ch2��Ch3 ���˲���
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //�������벶׽�ж�
        //delayms(10);        //��Ϊ������ź�������̲��ȶ������״���������벶׽�����������ʱ
        //�����ǵ��жϲ�Ӧ�ù�����ʱ�����Կ����벶׽�жϾͷ���main�����������Ҫ������
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //��ֹ���벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //�������벶׽�ж�
    }

}
uint32_t velocity;
uint32_t Lpt_cu,Lpt_his;
void PIT0_IRQHandler(void)
{
	Lpt_cu = LPTMR0_CNR;                                                     //�����������������ֵ
	velocity = (Lpt_cu-Lpt_his);
	lptmr_counter_clean();                                                  //����������������ֵ��������գ��������ܱ�֤����ֵ׼ȷ��
	PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}

void  LPT_Handler(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //���LPTMR�Ƚϱ�־
}
