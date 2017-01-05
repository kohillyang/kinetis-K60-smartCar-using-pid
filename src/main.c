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

/*************************************************************************
*                             野火嵌入式开发工作室
*                               野火工程模版
*  实验说明：野火工程模版
*
*  实验操作：
*
*  实验效果：
*
*  实验目的：
*
*  修改时间：
*
*  备    注：
*************************************************************************/

/******  需要调节参数  ******/
#define MOTOR_VALUE_L 50    //使小车直行的左电机占空比
#define MOTOR_VALUE_R 49    //使小车直行的右电机占空比
int P = 3;                    // PID的P值，减小P值过弯灵敏

/******  图像采集初始化  ******/
u8  IMG_BUFF[CAMERA_H][CAMERA_W]; //图像缓存区
u8  IMG_finish = 0;                 //图像采集完成标记
u8  IMG_get = 0;                    //开始采集图像标记
int  H_count = 1;                   //当前采集行数   
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
/******  主函数  ******/

//PC1是INH,PC2正转,PC3反转
//舵机范围0.5-2.5（50-250），可用范围60-120度（117-183）
#define MOTO_R_MOST     166
#define MOTO_L_MOST     180
#define MOTO_MID        173
int main()
{
	init_gpio();
	GPIOA_PDOR &= ~GPIO_PDOR_PDO(GPIO_PIN(17));
	//SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
	DisableInterrupts;  //关中断
	FTM_PWM_init(FTM0, CH1, 8000, 0);  //PWM通道初始化
	FTM_PWM_init(FTM0, CH2, 8000, 150);  //PWM通道初始化
	gpio_init(PORTC, 1, GPO, 1); //MOTOR4,INH 恒定为1
	gpio_init(PORTC, 2, GPO, 0);
	FTM_PWM_init(FTM1, CH1, 100, 173);  //舵机PWM通道（也可能是FTM1的CH0）
	delayms(1500);       //延时1.5s，等待电流稳定
	OV7620_init();     //摄像头初始化
	sccb_init();        //SCCB初始化（修改摄像头配置）

	EnableInterrupts;   //开中断

	while (1)
	{
		if (IMG_finish == 1)
		{

			disable_irq(90);    //关中断，图像处理过程禁止图像采集
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
			enable_irq(90);     //开中断，继续采集数据    
		}
	}
}



