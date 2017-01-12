/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
* 文件名       ：main.c
* 描述         ：工程模版实验
*
* 实验平台     ：野火kinetis开发板
* 库版本       ：
* 嵌入系统     ：
*
* 作者         ：野火嵌入式开发工作室
* 淘宝店       ：http://firestm32.taobao.com
* 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#include "include.h"



/******  图像采集初始化  ******/
u8  IMG_BUFF[CAMERA_H][CAMERA_W]; //图像缓存区
u8  IMG_finish = 0;                 //图像采集完成标记
#define MOTO_MID        95
int main()
{
	DisableInterrupts;  //关中断

	gpio_init(PORTC,4,GPO,1);
	FTM_PWM_init(FTM0, CH1, 8000, 200);  //PWM通道初始化
	FTM_PWM_init(FTM0, CH2, 8000, 0);  //PWM通道初始化
	FTM_PWM_init(FTM1, CH1, 100, MOTO_MID);  //舵机PWM通道（也可能是FTM1的CH0）
	delayms(1500);       //延时1.5s，等待电流稳定
	OV7620_init();     //摄像头初始化
	sccb_init();        //SCCB初始化（修改摄像头配置）
	EnableInterrupts;   //开中断

	while (1)
	{
		if (IMG_finish == 1)
		{
			disable_irq(90);    //关中断，图像处理过程禁止图像采集
			uint32_t image_pid_update(const uint8_t *image);
			FTM_PWM_Duty(FTM1, CH1, image_pid_update((uint8_t * )IMG_BUFF));
			IMG_finish = 0;
			enable_irq(90);     //开中断，继续采集数据
		}
	}
}



