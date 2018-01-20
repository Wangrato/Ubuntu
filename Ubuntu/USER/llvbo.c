
#include "LVBO.h"
#include "headfile.h"

#define FILTER_N 12
#define min 80
#define max 250
#define range 100

extern unsigned short int adc[8];
 
  
///////////////////////////////////////////////////////
//定义结构体Adc_Value存放AD采集的数据
//////////////////////////////////////////////////////

struct Adc_Value
{
  float value1[FILTER_N];
  float value2[FILTER_N];
  float value3[FILTER_N];
  float value4[FILTER_N];
  float value5[FILTER_N];
  float value6[FILTER_N];
  float value7[FILTER_N];
  float value8[FILTER_N];
}ad;

int quan[FILTER_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12};    // 加权系数表
int sum_quan = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10+11+12; // 加权系数和 
float ad1_sum=0,ad2_sum=0,ad3_sum=0,ad4_sum=0,ad5_sum=0,ad6_sum=0,ad7_sum=0,ad8_sum=0;
  

void lvbo(void)  
{
 
  int i;
  
  for(i=0;i<FILTER_N;i++)
  {
    ad.value1[i]=adc_once(ADC0_SE4,ADC_12bit)*quan[i];    //加权计算，越靠后的采集值权重越大
    ad.value2[i]=adc_once(ADC0_SE5,ADC_12bit)*quan[i];
    ad.value3[i]=adc_once(ADC0_SE6,ADC_12bit)*quan[i];
    ad.value4[i]=adc_once(ADC0_SE7,ADC_12bit)*quan[i];
    ad.value5[i]=adc_once(ADC0_SE12,ADC_12bit)*quan[i];
    ad.value6[i]=adc_once(ADC0_SE13,ADC_12bit)*quan[i];
    ad.value7[i]=adc_once(ADC0_SE14,ADC_12bit)*quan[i];
    ad.value8[i]=adc_once(ADC0_SE15,ADC_12bit)*quan[i];
    
    
    ad1_sum+=ad.value1[i];  //累加
    ad2_sum+=ad.value2[i];
    ad3_sum+=ad.value3[i];
    ad4_sum+=ad.value4[i];
    ad5_sum+=ad.value5[i];
    ad6_sum+=ad.value6[i];
    ad7_sum+=ad.value7[i];
    ad8_sum+=ad.value8[i];
  }
  ad1_sum=ad1_sum/sum_quan;   //计算平均值
  ad2_sum=ad2_sum/sum_quan;
  ad3_sum=ad3_sum/sum_quan;
  ad4_sum=ad4_sum/sum_quan;
  ad5_sum=ad5_sum/sum_quan;
  ad6_sum=ad6_sum/sum_quan;
  ad7_sum=ad7_sum/sum_quan;
  ad8_sum=ad8_sum/sum_quan;
  
  adc[0]=(unsigned short int)((ad1_sum-min)/(max-min)*range);//归一化
  adc[1]=(unsigned short int)((ad2_sum-min)/(max-min)*range);
  adc[2]=(unsigned short int)((ad3_sum-min)/(max-min)*range);
  adc[3]=(unsigned short int)((ad4_sum-min)/(max-min)*range);
  adc[4]=(unsigned short int)((ad5_sum-min)/(max-min)*range);
  adc[5]=(unsigned short int)((ad6_sum-min)/(max-min)*range);
  adc[6]=(unsigned short int)((ad7_sum-min)/(max-min)*range);
  adc[7]=(unsigned short int)((ad8_sum-min)/(max-min)*range);
}