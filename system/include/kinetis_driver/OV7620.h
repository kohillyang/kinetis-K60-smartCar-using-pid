#ifndef _OV7620_H_
#define _OV7620_H_

#include "common.h"

/*************************************************
 * ��������
 *         ���ж� - PORTD14
 *         ���ж� - PORTD13
 *           PCLK - PORTD12
 *         ����λ - PORTE0~7                                 
*************************************************/
#define   VSYN_PORT               PORTD                //���ж϶˿ں�
#define   VSYN_PIN                14                   //���ж����ź�
#define   HREF_PORT               PORTD                //���ж϶˿ں�
#define   HREF_PIN                13                   //���ж����ź�
#define     PCLK                  PTD12                //PCLK
#define    DATA_IN             PTE_BYTE0_IN            //����λ- PORTE0~7
#define	CAMERA_DMA_CH 	         DMA_CH0               //��������ͷ��DMA�ɼ�ͨ��

#define CAMERA_W            160                        //��������ͷ�ɼ����
#define CAMERA_H            120				           //��������ͷ�ɼ��߶�
#define CAMERA_SIZE         (CAMERA_W * CAMERA_H)      //ͼ��ռ�ÿռ��С

//Ӧ��main�����ж����ȫ�ֱ���
extern u8  IMG_BUFF[CAMERA_H][CAMERA_W];       //ͼ�񻺴�
extern u8  IMG_finish;                       //��ǲɼ����
extern u8  IMG_get;                          //�������ɼ�
extern int  H_count;                          //��ǰ�ɼ��м�����

/* ����ͷģ���ʼ������ */
void OV7620_init ();

#endif
