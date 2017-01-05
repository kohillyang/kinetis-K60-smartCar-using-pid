/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
* �ļ���       ��main.c
* ����         ������ģ��ʵ��
*
* ʵ��ƽ̨     ��Ұ��kinetis������
* ��汾       ��
* Ƕ��ϵͳ     ��
*
* ����         ��Ұ��Ƕ��ʽ����������
* �Ա���       ��http://firestm32.taobao.com
* ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#include "include.h"

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                               Ұ�𹤳�ģ��
*  ʵ��˵����Ұ�𹤳�ģ��
*
*  ʵ�������
*
*  ʵ��Ч����
*
*  ʵ��Ŀ�ģ�
*
*  �޸�ʱ�䣺
*
*  ��    ע��
*************************************************************************/

/******  ��Ҫ���ڲ���  ******/
#define MOTOR_VALUE_L 50    //ʹС��ֱ�е�����ռ�ձ�
#define MOTOR_VALUE_R 49    //ʹС��ֱ�е��ҵ��ռ�ձ�
int P = 3;                    // PID��Pֵ����СPֵ��������

/******  ͼ��ɼ���ʼ��  ******/
u8  IMG_BUFF[CAMERA_H][CAMERA_W]; //ͼ�񻺴���
u8  IMG_finish = 0;                 //ͼ��ɼ���ɱ��
u8  IMG_get = 0;                    //��ʼ�ɼ�ͼ����
int  H_count = 1;                   //��ǰ�ɼ�����   
u8  Cmd;

#define GPIO_PIN_MASK            0x1Fu
#define GPIO_PIN(x)              (((1)<<(x & GPIO_PIN_MASK)))
void init_gpio()
{

	//Set PTA10, PTA11, PTA28, and PTA29 (connected to LED's) for GPIO functionality
	PORTA_PCR17 = (0 | PORT_PCR_MUX(1));

	//Change PTA10, PTA11, PTA28, PTA29 to outputs
	GPIOA_PDDR = GPIO_PDDR_PDD(GPIO_PIN(17));
}
/******  ������  ******/

//PC1��INH,PC2��ת,PC3��ת
//�����Χ0.5-2.5��50-250�������÷�Χ60-120�ȣ�117-183��
#define MOTO_R_MOST     166
#define MOTO_L_MOST     180
#define MOTO_MID        173
int main()
{
	init_gpio();
	GPIOA_PDOR &= ~GPIO_PDOR_PDO(GPIO_PIN(17));
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
	DisableInterrupts;  //���ж�
	FTM_PWM_init(FTM0, CH1, 8000, 0);  //PWMͨ����ʼ��
	FTM_PWM_init(FTM0, CH2, 8000, 150);  //PWMͨ����ʼ��
	gpio_init(PORTC, 1, GPO, 1); //MOTOR4,INH �㶨Ϊ1
	gpio_init(PORTC, 2, GPO, 0);
	FTM_PWM_init(FTM1, CH1, 100, 173);  //���PWMͨ����Ҳ������FTM1��CH0��
	delayms(1500);       //��ʱ1.5s���ȴ������ȶ�
	OV7620_init();     //����ͷ��ʼ��
	sccb_init();        //SCCB��ʼ�����޸�����ͷ���ã�

	EnableInterrupts;   //���ж�

	while (1)
	{
		if (IMG_finish == 1)
		{

			disable_irq(90);    //���жϣ�ͼ������̽�ֹͼ��ɼ�
			/*SEGGER_RTT_printf(0, "&&&&&&&&&");
			for(int h = 0 ; h < CAMERA_H ; h++){
			for(int w = 0 ; w < CAMERA_W ; w++){
			SEGGER_RTT_printf(0, " %d ", IMG_BUFF[h][w]);
			}
			}
			SEGGER_RTT_printf(0, "##########");
			while(1);*/
			GPIOA_PDOR &= ~GPIO_PDOR_PDO(GPIO_PIN(17));
			uint32_t image_pid_update(const uint8_t *image);
			FTM_PWM_Duty(FTM1, CH1, image_pid_update((uint8_t * )IMG_BUFF));
			GPIOA_PDOR |= GPIO_PDOR_PDO(GPIO_PIN(17));
			IMG_finish = 0;
			enable_irq(90);     //���жϣ������ɼ�����    
		}
	}
}



