


#include "headfile.h"

extern int duty[4];
void main()
{ int i=0;         //防止蓝牙陷入死循环  i>10000  
  get_clk();          //上电以后  初始化时钟
  DisableInterrupts;  //关掉全局中断
  OLED_Init();        //oled初始化
  gpio_init(C0,GPI,0);//蓝牙  连接成功后  G1变高     跳出
  gpio_init(I2,GPI,0);//I2定义为输入//用来编码器测向
  gpio_init(I3,GPI,0);//I3定义为输入//用来编码器测向
  gpio_init(D3,GPI,0);//D3定义为输入
  gpio_init(C7,GPO,0);//C7定义为输出   关掉蜂鸣器
  gpio_init(C0,GPI,0);//蓝牙  连接成功后  G1变高     跳出
  gpio_init(G0,GPI,1);//G0定义为输入/**********
  gpio_init(G1,GPI,1);//G1定义为输入  拨码开关
  gpio_init(G2,GPI,1);//G2定义为输入
  gpio_init(G3,GPI,1);//G3定义为输入**********/
  port_pull(G0);      //内部上拉使能
  port_pull(G1);
  port_pull(G2);
  port_pull(G3);
        ftm_pwm_init(ftm2,ftm_ch4,36000,0);		//pwm1   b4  黑
        ftm_pwm_init(ftm2,ftm_ch5,36000,0);		//pwm2   b5  红
        ftm_pwm_init(ftm2,ftm_ch2,36000,0);		//pwm3   c2  白
        ftm_pwm_init(ftm2,ftm_ch3,36000,0);		//pwm4   c3  黄   
  while(!gpio_get(C0))//等待蓝牙连接成功
  {i++;
   if(i>10000)
   { i=0;
     break;
   }
  }
  OLED_P8x16Str(0,0,"OK");
  ftm_count_init(ftm1);//初始化FTM1用作编码器1
  ftm_count_init(ftm0);//初始化FTM0用作编码器0
  adc_init8();//8路adc  初始化
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

pit_init(pit0,200000);//5ms中断					
set_irq_priority(PIT_CH0_IRQn,0);		//设置优先级,根据自己的需求设置 可设置范围为 0 - 3  越小优先级越高
enable_irq(PIT_CH0_IRQn);		        //打开pit0的中断开关

    
EnableInterrupts;  
while(1);    
   
  
 
}
