/******************** (C) COPYRIGHT 2012 DEMOK工作室 ********************
 * 文件名       ：sccb.c
 * 描述         ：OV7620 OV7640 OV6620数字摄像头SCCB驱动函数
 *
 * 实验平台     ：野火K60  
 *                DEMOK工作室OV7620/OV7640/OV6620
 *
 * 作者         ：DEMOK工作室
 * 淘宝店       ：http://demok.taobao.com
 * 热销OV7620   ：http://item.taobao.com/item.htm?spm=a1z10.1.3.1.56b358&id=17121695790&
 * 热销OV6620   ：http://item.taobao.com/item.htm?spm=a1z10.1.35.3.56b358&id=10917998245
 * 热销OV7640   ：即将上架
**********************************************************************************/
#include "sccb.h"
#include "gpio.h"


/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_init
*  功能说明：利用IO初始化sccb           
*            SCL--->PE10 
*            SDA--->PE12
*  参数说明：无
*  函数返回：无
*  备    注：
*************************************************************************/
void sccb_init(void)
{
  PORT_PCR_REG(PORTE_BASE_PTR, 10) = (0 | PORT_PCR_MUX(1) );
  PORT_PCR_REG(PORTE_BASE_PTR, 12) = (0 | PORT_PCR_MUX(1) );
}

/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_wait
*  功能说明：sccb延时函数         
*  参数说明：无
*  函数返回：无
*  备    注：移植至其他MCU注意延时时长的修改
*************************************************************************/
void sccb_wait(void)
{
  u32 i;
  
  for( i=0; i<2000; i++)
  {
    asm ("nop");
  }
}

/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_start
*  功能说明：sccb开始信号         
*  参数说明：无
*  函数返回：无
*  备    注：
*************************************************************************/
void sccb_start(void)
{
  SCL_OUT;
  SDA_OUT;
 
  SDA_HIGH;
  //sccb_wait();
  SCL_HIGH;
  sccb_wait();
  SDA_LOW;
  sccb_wait();
  SCL_LOW;
}

/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_stop
*  功能说明：sccb停止信号         
*  参数说明：无
*  函数返回：无
*  备    注：
*************************************************************************/
void sccb_stop(void)
{
  SCL_OUT;
  SDA_OUT;
  
  SDA_LOW;
  sccb_wait();
  SCL_HIGH;
  sccb_wait();
  SDA_HIGH;
  sccb_wait();
}

void sccb_sendAck(u8 ack){
	SDA_OUT;
	if(ack)
		SDA_HIGH;
	else
		SDA_LOW;
	SCL_HIGH;
	sccb_wait();
	SCL_LOW;
}
/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_sendByte
*  功能说明：sccb字节写入         
*  参数说明：data--待写入字节内容
*  函数返回：ack--应答信号
*            ack=1未收到应答    ack=0收到应答
*  备    注：
*************************************************************************/
u8 sccb_sendByte(u8 data)
{
  u8 i;
   u8 ack;
  SDA_OUT;
  for( i=0; i<8; i++)
  {
    if(data & 0x80)
      SDA_HIGH;
    else 
      SDA_LOW;
    data <<= 1;
    sccb_wait();
    SCL_HIGH;
    sccb_wait();
    SCL_LOW;
    sccb_wait();
  }
  SDA_HIGH;
  SDA_IN;
  sccb_wait();
  SCL_HIGH;
  sccb_wait();
  ack = SDA_DATA;
  SCL_LOW;
  sccb_wait();
  return ack;
}

u8 sccb_receiveByte(void){
	u8 data=0;
	u8 i=0;
	SDA_IN;
	for( i=0; i<8; i++){
		SCL_HIGH;
		sccb_wait();
		data<<=1;
		if(SDA_DATA){
			data|=0x01;
		}
		SCL_LOW;
		sccb_wait();
	}
	return data;
	
}

/*************************************************************************
*             【DEMOK工作室】数字摄像头SCCB驱动函数
*
*  函数名称：sccb_regWrite
*  功能说明：在指定设备的指定地址中写入指定数据        
*  参数说明：device--摄像头设备号（其中OV7620写为0X42   OV7640写为0X42  OV6620写为0XC0）
*            address--要写入的地址
*            data--要写入的数据
*  函数返回：
*  备    注：
*************************************************************************/
void sccb_regWrite(u8 device,u8 address,u8 data)
{
  u8 i;
  u8 ack;
  for( i=0; i<20; i++)
  {
    sccb_start();
    ack = sccb_sendByte(device);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    ack = sccb_sendByte(address);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    ack = sccb_sendByte(data);
    if( ack == 1 )
    {
     // sccb_stop();
      continue;
    }
    
    sccb_stop();
    if( ack == 0 ) break;
  }
}


u8 sccb_regRead(u8 device,u8 address){
	u8 data=0;
	 u8 i;
	  u8 ack;
	  for( i=0; i<20; i++)
	  {
	    sccb_start();
	    ack = sccb_sendByte(device);
	    if( ack == 1 )
	    {
	     // sccb_stop();
	      continue;
	    }
	    
	    ack = sccb_sendByte(address);
	    if( ack == 1 )
	    {
	     // sccb_stop();
	      continue;
	    }
	    if( ack == 0 ) break;
	  }
	 for( i=0; i<20; i++)
	  {
	    sccb_start();
	    sccb_sendByte(device|0x01);
	    if( ack == 1 )
	    {
	     // sccb_stop();
	      continue;
	    }
	    if( ack == 0 ) break;
	  }
	data=sccb_receiveByte();
	sccb_sendAck(0);
	data=sccb_receiveByte();
	sccb_sendAck(1);
	
	sccb_stop();
	return data;
	
}