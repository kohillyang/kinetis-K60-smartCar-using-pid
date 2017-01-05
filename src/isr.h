/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.h
 * ����         �����º궨���жϺţ���ӳ���ж�����������жϺ�����ַ��
 *                ʹ��ָ��������������жϷ������������жϷ�����
 *                ���棺ֻ����"vectors.c"���������ұ�����"vectors.h"�����ĺ��棡����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/	



#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

/*                          ���¶����ж�������
 *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��       #undef  VECTOR_xxx
 *  �����¶��嵽�Լ���д���жϺ���       #define VECTOR_xxx    xxx_IRQHandler
 *  ���磺
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
 */
#undef  VECTOR_014
#undef  VECTOR_015
#if     USOC_EN > 0u    //�����������ucosϵͳ  ��ucos�ĵδ�ʱ���жϷ�����
  #define VECTOR_014    OS_CPU_PendSVHandler
  #define VECTOR_015    OS_CPU_SysTickHandler
#else
  #define VECTOR_014    PendSV_Handler
  #define VECTOR_015    SysTick_Handler   //�δ�ʱ��  OS�õõ�
#endif

#undef  VECTOR_003
#define VECTOR_003    HardFault_Handler   //����Ӳ���Ϸ� �����ǳ����ܷ��ˣ�     �Ƽ����Գ���ʱ���ø�LED��ʾ��ָʾ�����ܷ���

extern void PendSV_Handler(void);         //�������ϵͳ�����жϷ�����
extern void HardFault_Handler(void);      //����Ӳ���Ϸã������ܷɣ�
extern void SysTick_Handler(void);        //�δ�ʱ��(os �õ�)


  /*********irq*************/
#undef  VECTOR_016
#define VECTOR_016    DMA_CH0_Handler     //DMA�ж�

#undef  VECTOR_106
#define VECTOR_106    PORTD_IRQHandler    //PORTD�ж�:���жϡ����ж�

#undef  VECTOR_063
#define VECTOR_063    UART1_IRQHandler      //UART1�жϣ������ַ�

extern void USART1_IRQHandler();          //����1 �жϽ��պ���
extern void DMA_CH0_Handler();
extern void PORTD_IRQHandler();
extern void UART1_IRQHandler();


 
#endif  //__ISR_H

/* End of "isr.h" */
