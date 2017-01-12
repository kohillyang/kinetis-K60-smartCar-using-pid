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



/******  ͼ��ɼ���ʼ��  ******/
u8  IMG_BUFF[CAMERA_H][CAMERA_W]; //ͼ�񻺴���
u8  IMG_finish = 0;                 //ͼ��ɼ���ɱ��
#define MOTO_MID        95
int main()
{
	DisableInterrupts;  //���ж�

	gpio_init(PORTC,4,GPO,1);
	FTM_PWM_init(FTM0, CH1, 8000, 200);  //PWMͨ����ʼ��
	FTM_PWM_init(FTM0, CH2, 8000, 0);  //PWMͨ����ʼ��
	FTM_PWM_init(FTM1, CH1, 100, MOTO_MID);  //���PWMͨ����Ҳ������FTM1��CH0��
	delayms(1500);       //��ʱ1.5s���ȴ������ȶ�
	OV7620_init();     //����ͷ��ʼ��
	sccb_init();        //SCCB��ʼ�����޸�����ͷ���ã�
	EnableInterrupts;   //���ж�

	while (1)
	{
		if (IMG_finish == 1)
		{
			disable_irq(90);    //���жϣ�ͼ������̽�ֹͼ��ɼ�
			uint32_t image_pid_update(const uint8_t *image);
			FTM_PWM_Duty(FTM1, CH1, image_pid_update((uint8_t * )IMG_BUFF));
			IMG_finish = 0;
			enable_irq(90);     //���жϣ������ɼ�����
		}
	}
}



