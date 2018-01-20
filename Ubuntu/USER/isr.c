/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		中断文件
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"
#include "pid.h"
#include "LVBO.h"

   
unsigned short int adc[8]={0}; 
uint32 LSPEED=0,RSPEED=0,L=0,R=0,i=0;//左编码器 右编码器 占空比
int duty[4]={0}; 
int lad=0,rad=0,aderror; 


void PIT_CH0_IRQHandler(void)  
{
  PIT_FlAG_CLR(pit0);   //清零中断标志
  i++;
    RSPEED=ftm_count_get(ftm0); 
    LSPEED=ftm_count_get(ftm1); 
    if(gpio_get(I2)==0)
      RSPEED=-RSPEED;
    if(gpio_get(I3)==1)
      LSPEED=-LSPEED;
    if(gpio_get(G0)==0)
      {duty[0]=0;
       duty[1]=0;
       duty[2]=0;
       duty[3]=0;
       ftm_pwm(duty);
      }  
   lvbo();//ad采样并进行滤波 
   lad=adc[5];
   rad=adc[7];
   aderror=lad-rad;
   control(aderror,LSPEED,RSPEED);
    while(i>20)
    {i=0;
     OLED_Fill(0x00);  //清屏
     OLED_Print_Num1(0,0,LSPEED);
     OLED_Print_Num1(0,1,RSPEED);
     OLED_Print_Num1(0,2,adc[5]);
     OLED_Print_Num1(0,3,adc[6]);
     OLED_Print_Num1(0,4,adc[7]);  
    }
    adc[0]=LSPEED;
    adc[1]=RSPEED;
    
    Data_Send(uart2,adc); //发送数据到串口
    ftm_count_clean(ftm0);//编码器清零
    ftm_count_clean(ftm1);
}


/*void ADC0_IRQHandler()
//{
//  int i,result=0;
 //   if(AD_time==100)
 //  {
 //    AD_time=1;  //计数清零
 // }
 //  for(i=0;i<8;i++)
 //  { 
     result = ADC->R;      //连续 读取 
     adc_value[ADC_time][i]=result;
   }
   AD_time++;
   
   
}*/

void PIT_CH1_IRQHandler(void)
{
    PIT_FlAG_CLR(pit1);
   
}

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}


void KBI0_IRQHandler(void)
{
    CLEAN_KBI0_FLAG;
    
}





/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器 通道0得中断
void PIT_CH0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler   //定时器不链接   猜的
PIT_CH1_IRQHandler   //定时器链接
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/

