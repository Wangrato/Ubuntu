#ifndef _ADC_H_
#define _ADC_H_

#include "common.h"
#include "headfile.h"

#define FILTER_N 12
#define min 0
#define max 4095
#define range 100


/*
利用ADC中断采集数据，FIFO连续采集八个数据，存储于二位数组：列表示采集次数，行位FIFO深度（8），存储不同电感数据；
在定时器中断里进行滤波和归一化处理，需要计算好数据采集与数据处理的时间，避免冲突
*/

////////////////////////////////////
//存放滤波后的AD值
//范围：0-4095   参考电压位5V
//空载采集电压约2500
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
void Filter(void); //加权递推平均滤波
void JUNZHI(void); //均值滤波法  实验
void GUIYI(void);  //归一化处理
void adc_FIFO(ADC_nbit bit);

#endif