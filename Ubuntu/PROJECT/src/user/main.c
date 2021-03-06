
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱S9KEAZ128智能车MINI核心板母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年11月11日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】S9KEAZ128
【Crystal 】16.000Mhz
【busclock】40.000MHz
【pllclock】40.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
/*************************测试说明******************************/
/****************************************************************
  测试什么功能就去掉对应函数前的“//”
  该例程针对mini核心板以及配套母版编写，其他版本核心板修改引脚
  TF卡&OLED版本核心板上OLED接口与ADC例程中的ADC引脚冲突，注意修改
  PWM和编码器采集函数不能同时启用，因为FTM模块冲突
  每个测试函数都写有 while（1），同时使能两个测试函数先执行的函数有效
*******************************************************************/
/******************************************************************
接口定义：
-------------------------------------------------------------
LED         单片机接口
//核心板上RGB灯珠
LED0           PTC2
LED1           PTB4
LED2           PTE5
//母板上LED灯珠
LED3           PTI4
LED4           PTH6
===============================================================
KEY        单片机接口
//核心板上按键
KEY0          PTA0
//母板按键
KEY1          PTB5
KEY2          PTH2
KEY3          PTE6
===============================================================
拨码开关    单片机接口
KEY0          PTI2
KEY1          PTI3
KEY2          PTE2
KEY3          PTE3
===============================================================
TSL1401模块     单片机接口
VCC             5V
GND             GND
SI              I5/D5
SCK             I6/D6
ADCGND
SDA1                      AD8 C0/AD9 C1
===============================================================
多路电感模块    单片机接口
VCC             5V
GND             GND
ADC通道         管脚关系     
ADC12           F4      
ADC13           F5      
ADC14           F6      
ADC15           F7       
ADC4            B0      
ADC5            B1   
ADC6            B2       
ADC7            B3
-------------------------------------------------------------
电源监控或者它用    
ADC11           C3              
-------------------------------------------------------------
MPU6050        单片机接口   FLEXCOMM8
VCC             5V
GND                H3
SCL1            H4
//////////////////////////////////////////////////////////通用部分功能//////////
电机驱动        单片机接口   
VCC             5V
PWM1            FTM2-CH0  H0
PWM2            FTM2-CH1  H1
PWM3            FTM2-CH2  D0
PWM4            FTM2-CH3  D1
-------------------------------------------------------------
舵机接口        单片机接口
VCC             可调
GND             GND
PWM1            FTM1-CH1  E7
-------------------------------------------------------------
龙邱512编码器   单片机接口   
VCC             5V
GND             GND      
LSB/A           FTM0 E0    
DIR/B           H7     
LSB/A           FTM1 E7     
DIR/B           H5     
-------------------------------------------------------------
OLED模块        单片机接口
VCC             5V
GND             GND
SCK             F3
SDA             F2
RST             A7
DC              A6
-------------------------------------------------------------
蓝牙/USBTTL    单片机接口   FLEXCOMM0
VCC             5V
GND             GND
UART2_RX        I1    
UART2_TX        I0
=============================================================*/

#include "include.h"

void main(void)
{  
  DisableInterrupts;                  //禁止中断    
  EnableInterrupts;    
  //gpio_init (PTB2, GPO,LOW);
  //TestLED();//测试GPIOmini核心板RGB灯珠颜色闪烁
  //Test_KEY(); //测试GPIO按键功能
  //Test_KEY1(); //测试GPIO拨码开关功能
  //TestADC();//测试ADC转换并通过OLED显示和UART发出
  //TestKBI();//测试GPIO外部中断 母版上K0，K1按键有效
  //TestPIT();//测试PIT定时中断
  //TestFTM_PWM();//测试PWM/OLED及电机控制功能
  //TestUART012();//测试UART012发送及接收中断
  //TestFTM_InputCapture();//测试编码器脉冲采集功能
  //TestMPU6050();
  //Test_2100_8700();//测试龙邱九轴传感器
  TestRTC();//LED闪烁，同时OLED上显示时间，单位秒
  while(1)
  {
  }
  
}



