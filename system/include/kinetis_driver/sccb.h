/******************** (C) COPYRIGHT 2012 DEMOK������ ********************
 * �ļ���       ��sccb.c
 * ����         ��OV7620 OV7640 OV6620��������ͷSCCB��������
 *
 * ʵ��ƽ̨     ��K60  OV7620/OV7640/OV6620
 *
 * ����         ��DEMOK������
 * �Ա���       ��http://demok.taobao.com
 * ����OV7620   ��http://item.taobao.com/item.htm?spm=a1z10.1.3.1.56b358&id=17121695790&
 * ����OV6620   ��http://item.taobao.com/item.htm?spm=a1z10.1.35.3.56b358&id=10917998245
 * ����OV7640   �������ϼ�
**********************************************************************************/
#ifndef __SCCB_H__
#define __SCCB_H__

#include "common.h"
#include "gpio.h"

//--- Ĭ��SCL��PE10   SDA��PE12------//
void sccb_init(void);                           //��ʼ��SCCB�˿�ΪGPIO
void sccb_wait(void);                           //SCCBʱ����ʱ
void sccb_start(void);                          //��ʼ��־
void sccb_stop(void);                           //ֹͣ��־
u8 sccb_sendByte(u8 data);
u8 sccb_receiveByte(void);
void sccb_regWrite(u8 device,u8 address,u8 data);
u8 sccb_regRead(u8 device,u8 address);

//--GPIO_DDR_1bit(PORTx,n,ddr)--//
#define SCL_OUT   GPIO_DDR_1bit(PORTE,10,1)      //SCL-PA0����Ϊ����˿�
#define SDA_OUT   GPIO_DDR_1bit(PORTE,12,1)      //SDA-PA1����Ϊ����˿�
#define SDA_IN    GPIO_DDR_1bit(PORTE,12,0)      //SDA-PA1����Ϊ����˿�

//--GPIO_SET_1bit(PORTx,n,data)--//
#define SCL_HIGH  GPIO_SET_1bit(PORTE,10,1)
#define SCL_LOW   GPIO_SET_1bit(PORTE,10,0)
#define SDA_HIGH  GPIO_SET_1bit(PORTE,12,1)
#define SDA_LOW   GPIO_SET_1bit(PORTE,12,0)
#define SDA_DATA  GPIO_GET_1bit(PORTE,12) 



#endif