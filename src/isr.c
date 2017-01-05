#include "common.h"
#include "include.h"

extern u8  IMG_finish;  //引用主函数中定义的变量
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
*                             野火嵌入式开发工作室
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch = uart_getchar (UART1);      //接收到一个数据
    uart_sendStr  (UART1, "\n你发送的数据为：");
    uart_putchar (UART1, ch);       //就发送出去

    EnableInterrupts;		    //开总中断
}

void PORTD_IRQHandler()
{
    u8  n=0;      //引脚号

    n=VSYN_PIN;
    if(PORTD_ISFR & (1<<n))           //PTD14触发场中断
    {
        PORTD_ISFR  |= (1<<n);        //写1清中断标志位
        IMG_finish=0;
        IMG_get=1;
        H_count=1;
        DMA_DADDR(CAMERA_DMA_CH) = (u32)IMG_BUFF;    //恢复地址     

    }

    n=HREF_PIN;
    if(PORTD_ISFR & (1<<n))           //PTD13触发行中断
    {
        PORTD_ISFR  |= (1<<n);          //写1清中断标志位
        if(IMG_get==1)
        {
            DMA_EN(CAMERA_DMA_CH);     //使能通道CHn 硬件请求
            H_count++;
        }
    }
}

void DMA_CH0_Handler()
{
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);   //清除通道传输中断标志位    (这样才能再次进入中断)
    DMA_DIS(CAMERA_DMA_CH);         //采集完W个数据后进入这个DMA中断，停止DMA传输。行中断中打开DMA传输
    if(H_count > CAMERA_H)
    {
        IMG_finish=1;
        IMG_get=0;
        disable_irq(90);
    }
}

void UART1_IRQHandler()
{       
	DisableInterrupts;          //关总中断      
	//接收一个字节数据并回发    
	/*uart_getstr(UART1, (char *)cmdBuff,10);
	printf("\n你发送的数据为：%s",cmdBuff);      //发送出去
	buffu8_zero(cmdBuff, 10);*/
        Cmd=uart_getchar(UART1);
	//printf("\nyou sent char is：%c",cmd);      //发送出去
	EnableInterrupts;           //开总中断    
}

void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //清中断标志位

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断，而是在main函数里根据需要来开启
        //通道 CH0、CH1、Ch2、Ch3 有滤波器
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
        //delayms(10);        //因为输入的信号跳变过程不稳定，容易触发多次输入捕捉，所以添加延时
        //但考虑到中断不应该过长延时，所以开输入捕捉中断就放在main函数里，根据需要来开启
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
    }

}
uint32_t velocity;
uint32_t Lpt_cu,Lpt_his;
void PIT0_IRQHandler(void)
{
	Lpt_cu = LPTMR0_CNR;                                                     //保存脉冲计数器计算值
	velocity = (Lpt_cu-Lpt_his);
	lptmr_counter_clean();                                                  //清空脉冲计数器计算值（马上清空，这样才能保证计数值准确）
	PIT_Flag_Clear(PIT0);       //清中断标志位
}

void  LPT_Handler(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
}
