#ifndef _OV7620_H_
#define _OV7620_H_

#include "common.h"

/*************************************************
 * 引脚配置
 *         场中断 - PORTD14
 *         行中断 - PORTD13
 *           PCLK - PORTD12
 *         数据位 - PORTE0~7                                 
*************************************************/
#define   VSYN_PORT               PORTD                //场中断端口号
#define   VSYN_PIN                14                   //场中断引脚号
#define   HREF_PORT               PORTD                //行中断端口号
#define   HREF_PIN                13                   //行中断引脚号
#define     PCLK                  PTD12                //PCLK
#define    DATA_IN             PTE_BYTE0_IN            //数据位- PORTE0~7
#define	CAMERA_DMA_CH 	         DMA_CH0               //定义摄像头的DMA采集通道

#define CAMERA_W            160                        //定义摄像头采集宽度
#define CAMERA_H            120				           //定义摄像头采集高度
#define CAMERA_SIZE         (CAMERA_W * CAMERA_H)      //图像占用空间大小

//应在main函数中定义的全局变量
extern u8  IMG_BUFF[CAMERA_H][CAMERA_W];       //图像缓存
extern u8  IMG_finish;                       //标记采集完成
extern u8  IMG_get;                          //标记允许采集
extern int  H_count;                          //当前采集行计数器

/* 摄像头模块初始化函数 */
void OV7620_init ();

#endif
