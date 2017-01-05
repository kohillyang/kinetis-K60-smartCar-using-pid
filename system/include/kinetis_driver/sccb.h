/******************** (C) COPYRIGHT 2012 DEMOK工作室 ********************
 * 文件名       ：sccb.c
 * 描述         ：OV7620 OV7640 OV6620数字摄像头SCCB驱动函数
 *
 * 实验平台     ：K60  OV7620/OV7640/OV6620
 *
 * 作者         ：DEMOK工作室
 * 淘宝店       ：http://demok.taobao.com
 * 热销OV7620   ：http://item.taobao.com/item.htm?spm=a1z10.1.3.1.56b358&id=17121695790&
 * 热销OV6620   ：http://item.taobao.com/item.htm?spm=a1z10.1.35.3.56b358&id=10917998245
 * 热销OV7640   ：即将上架
**********************************************************************************/
#ifndef __SCCB_H__
#define __SCCB_H__

#include "common.h"
#include "gpio.h"

//--- 默认SCL接PE10   SDA接PE12------//
void sccb_init(void);                           //初始化SCCB端口为GPIO
void sccb_wait(void);                           //SCCB时序延时
void sccb_start(void);                          //起始标志
void sccb_stop(void);                           //停止标志
u8 sccb_sendByte(u8 data);
u8 sccb_receiveByte(void);
void sccb_regWrite(u8 device,u8 address,u8 data);
u8 sccb_regRead(u8 device,u8 address);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   GPIO_DDR_1bit(PORTE,10,1)      //SCL-PA0设置为输出端口
#define SDA_OUT   GPIO_DDR_1bit(PORTE,12,1)      //SDA-PA1设置为输出端口
#define SDA_IN    GPIO_DDR_1bit(PORTE,12,0)      //SDA-PA1设置为输入端口

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  GPIO_SET_1bit(PORTE,10,1)
#define SCL_LOW   GPIO_SET_1bit(PORTE,10,0)
#define SDA_HIGH  GPIO_SET_1bit(PORTE,12,1)
#define SDA_LOW   GPIO_SET_1bit(PORTE,12,0)
#define SDA_DATA  GPIO_GET_1bit(PORTE,12) 



#endif