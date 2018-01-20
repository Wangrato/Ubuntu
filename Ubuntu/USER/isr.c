/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�ж��ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
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
uint32 LSPEED=0,RSPEED=0,L=0,R=0,i=0;//������� �ұ����� ռ�ձ�
int duty[4]={0}; 
int lad=0,rad=0,aderror; 


void PIT_CH0_IRQHandler(void)  
{
  PIT_FlAG_CLR(pit0);   //�����жϱ�־
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
   lvbo();//ad�����������˲� 
   lad=adc[5];
   rad=adc[7];
   aderror=lad-rad;
   control(aderror,LSPEED,RSPEED);
    while(i>20)
    {i=0;
     OLED_Fill(0x00);  //����
     OLED_Print_Num1(0,0,LSPEED);
     OLED_Print_Num1(0,1,RSPEED);
     OLED_Print_Num1(0,2,adc[5]);
     OLED_Print_Num1(0,3,adc[6]);
     OLED_Print_Num1(0,4,adc[7]);  
    }
    adc[0]=LSPEED;
    adc[1]=RSPEED;
    
    Data_Send(uart2,adc); //�������ݵ�����
    ftm_count_clean(ftm0);//����������
    ftm_count_clean(ftm1);
}


/*void ADC0_IRQHandler()
//{
//  int i,result=0;
 //   if(AD_time==100)
 //  {
 //    AD_time=1;  //��������
 // }
 //  for(i=0;i<8;i++)
 //  { 
     result = ADC->R;      //���� ��ȡ 
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
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

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
PIT_CH0_IRQHandler   //��ʱ��������   �µ�
PIT_CH1_IRQHandler   //��ʱ������
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/

