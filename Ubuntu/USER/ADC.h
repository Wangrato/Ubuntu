#ifndef _ADC_H_
#define _ADC_H_

#include "common.h"
#include "headfile.h"

#define FILTER_N 12
#define min 0
#define max 4095
#define range 100


/*
����ADC�жϲɼ����ݣ�FIFO�����ɼ��˸����ݣ��洢�ڶ�λ���飺�б�ʾ�ɼ���������λFIFO��ȣ�8�����洢��ͬ������ݣ�
�ڶ�ʱ���ж�������˲��͹�һ��������Ҫ��������ݲɼ������ݴ����ʱ�䣬�����ͻ
*/

////////////////////////////////////
//����˲����ADֵ
//��Χ��0-4095   �ο���ѹλ5V
//���زɼ���ѹԼ2500
//
////////////////////////////////////
  extern float ad1_result;
  extern float ad2_result;
  extern float ad3_result;
  extern float ad4_result;
  extern float ad5_result;
  extern float ad6_result;
  extern float ad7_result;
  extern float ad8_result;

extern float ad1_sum,ad2_sum,ad3_sum,ad4_sum,ad5_sum,ad6_sum,ad7_sum,ad8_sum;

void ADC_Init(void);
void Filter(void); //��Ȩ����ƽ���˲�
void JUNZHI(void); //��ֵ�˲���  ʵ��
void GUIYI(void);  //��һ������
void adc_FIFO(ADC_nbit bit);

#endif