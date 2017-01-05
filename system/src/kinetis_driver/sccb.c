/******************** (C) COPYRIGHT 2012 DEMOK������ ********************
 * �ļ���       ��sccb.c
 * ����         ��OV7620 OV7640 OV6620��������ͷSCCB��������
 *
 * ʵ��ƽ̨     ��Ұ��K60  
 *                DEMOK������OV7620/OV7640/OV6620
 *
 * ����         ��DEMOK������
 * �Ա���       ��http://demok.taobao.com
 * ����OV7620   ��http://item.taobao.com/item.htm?spm=a1z10.1.3.1.56b358&id=17121695790&
 * ����OV6620   ��http://item.taobao.com/item.htm?spm=a1z10.1.35.3.56b358&id=10917998245
 * ����OV7640   �������ϼ�
**********************************************************************************/
#include "sccb.h"
#include "gpio.h"


/*************************************************************************
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_init
*  ����˵��������IO��ʼ��sccb           
*            SCL--->PE10 
*            SDA--->PE12
*  ����˵������
*  �������أ���
*  ��    ע��
*************************************************************************/
void sccb_init(void)
{
  PORT_PCR_REG(PORTE_BASE_PTR, 10) = (0 | PORT_PCR_MUX(1) );
  PORT_PCR_REG(PORTE_BASE_PTR, 12) = (0 | PORT_PCR_MUX(1) );
}

/*************************************************************************
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_wait
*  ����˵����sccb��ʱ����         
*  ����˵������
*  �������أ���
*  ��    ע����ֲ������MCUע����ʱʱ�����޸�
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
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_start
*  ����˵����sccb��ʼ�ź�         
*  ����˵������
*  �������أ���
*  ��    ע��
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
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_stop
*  ����˵����sccbֹͣ�ź�         
*  ����˵������
*  �������أ���
*  ��    ע��
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
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_sendByte
*  ����˵����sccb�ֽ�д��         
*  ����˵����data--��д���ֽ�����
*  �������أ�ack--Ӧ���ź�
*            ack=1δ�յ�Ӧ��    ack=0�յ�Ӧ��
*  ��    ע��
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
*             ��DEMOK�����ҡ���������ͷSCCB��������
*
*  �������ƣ�sccb_regWrite
*  ����˵������ָ���豸��ָ����ַ��д��ָ������        
*  ����˵����device--����ͷ�豸�ţ�����OV7620дΪ0X42   OV7640дΪ0X42  OV6620дΪ0XC0��
*            address--Ҫд��ĵ�ַ
*            data--Ҫд�������
*  �������أ�
*  ��    ע��
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