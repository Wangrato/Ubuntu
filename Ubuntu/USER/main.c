


#include "headfile.h"

extern int duty[4];
void main()
{ int i=0;         //��ֹ����������ѭ��  i>10000  
  get_clk();          //�ϵ��Ժ�  ��ʼ��ʱ��
  DisableInterrupts;  //�ص�ȫ���ж�
  OLED_Init();        //oled��ʼ��
  gpio_init(C0,GPI,0);//����  ���ӳɹ���  G1���     ����
  gpio_init(I2,GPI,0);//I2����Ϊ����//��������������
  gpio_init(I3,GPI,0);//I3����Ϊ����//��������������
  gpio_init(D3,GPI,0);//D3����Ϊ����
  gpio_init(C7,GPO,0);//C7����Ϊ���   �ص�������
  gpio_init(C0,GPI,0);//����  ���ӳɹ���  G1���     ����
  gpio_init(G0,GPI,1);//G0����Ϊ����/**********
  gpio_init(G1,GPI,1);//G1����Ϊ����  ���뿪��
  gpio_init(G2,GPI,1);//G2����Ϊ����
  gpio_init(G3,GPI,1);//G3����Ϊ����**********/
  port_pull(G0);      //�ڲ�����ʹ��
  port_pull(G1);
  port_pull(G2);
  port_pull(G3);
        ftm_pwm_init(ftm2,ftm_ch4,36000,0);		//pwm1   b4  ��
        ftm_pwm_init(ftm2,ftm_ch5,36000,0);		//pwm2   b5  ��
        ftm_pwm_init(ftm2,ftm_ch2,36000,0);		//pwm3   c2  ��
        ftm_pwm_init(ftm2,ftm_ch3,36000,0);		//pwm4   c3  ��   
  while(!gpio_get(C0))//�ȴ��������ӳɹ�
  {i++;
   if(i>10000)
   { i=0;
     break;
   }
  }
  OLED_P8x16Str(0,0,"OK");
  ftm_count_init(ftm1);//��ʼ��FTM1����������1
  ftm_count_init(ftm0);//��ʼ��FTM0����������0
  adc_init8();//8·adc  ��ʼ��
  //adc_init(ADC0_SE13);adc_init(ADC0_SE14);adc_init(ADC0_SE15);
     if(gpio_get(G1)==0)
      {duty[0]=300;
       duty[1]=0;
       duty[2]=0;
       duty[3]=300;
       ftm_pwm(duty);
      }  
      else if(gpio_get(G2)==0)
      {duty[0]=500;
       duty[1]=0;
       duty[2]=0;
       duty[3]=500;
       ftm_pwm(duty);
      }
      else
      {duty[0]=0;
       duty[1]=0;
       duty[2]=0;
       duty[3]=0;
       ftm_pwm(duty);   
      }

pit_init(pit0,200000);//5ms�ж�					
set_irq_priority(PIT_CH0_IRQn,0);		//�������ȼ�,�����Լ����������� �����÷�ΧΪ 0 - 3  ԽС���ȼ�Խ��
enable_irq(PIT_CH0_IRQn);		        //��pit0���жϿ���

    
EnableInterrupts;  
while(1);    
   
  
 
}
