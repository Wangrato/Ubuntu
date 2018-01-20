#include "pid.h"
#include "headfile.h"
float Velocity_Kp=0.01;//,Velocity_Ki=0.4;//PID参数
int Velocity_Pwm,Turn_Pwm=0;//速度和角度
int Motor1,Motor2;
extern int duty[4];//电机占空比

int LD=300,RD=300,K=3;//设定电机初始 与比例
/**************************************************************************
函数功能：速度PI控制 
入口参数：左轮编码器、右轮编码器
返回  值：速度控制PWM
**************************************************************************/
int velocity(int encoder_left, int encoder_right)
{
  float Encoder_Least, Encoder, Movement;
  float Encoder_Integral, Target_Velocity;
 int Velocity;
 //int kp = 2, ki = kp / 200;    //PI参数
 Movement = (LD+RD)/K;


  //=============速度PI控制器=======================//
  Encoder_Least = ((encoder_left + encoder_right) - 0);               //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）
//  Encoder *= 0.7;                                                   //===一阶低通滤波器
//  Encoder += Encoder_Least * 0.3;                                   //===一阶低通滤波器
//  Encoder_Integral += Encoder;                                      //===积分出位移 积分时间：40ms
  Encoder_Integral = Movement-Encoder_Least;                  
//  if (Encoder_Integral > 21000)    Encoder_Integral = 21000;        //===积分限幅
//  if (Encoder_Integral < -21000) Encoder_Integral = -21000;         //===积分限幅
  Velocity =(int)( Encoder_Integral * Velocity_Kp); //+ Encoder_Integral * Velocity_Ki);                  //===速度控制
 // if (Turn_Off(KalFilter.angle, Battery_Voltage) == 1 || Flag_Stop == 1)    Encoder_Integral = 0;//小车停止的时候积分清零
  return Velocity;
}
/**************************************************************************
函数功能：转向控制 
入口参数：Z轴陀螺仪
返回  值：转向控制PWM
**************************************************************************/
int turn(int Turn_Convert)//转向控制int gyro //随后添加陀螺仪
{
  
  int Turn;
  float  Kp = 10, Kd = 0.001;  //PD参数
 // Turn_Target += Turn_Convert;//根据电感改变转向偏差
  

  //if (Turn_Target > Turn_Amplitude)  Turn_Target = Turn_Amplitude; //===转向速度限幅
  //if (Turn_Target < -Turn_Amplitude) Turn_Target = -Turn_Amplitude;
  Turn = (int)(-Turn_Convert * Kp);// + gyro * Kd;         //===结合Z轴陀螺仪进行PD控制
  return Turn;
}
/**************************************************************************
函数功能：赋值给PWM寄存器 
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1, int moto2)
{
  if(moto1>0) 
  { duty[0]=moto1;
    duty[1]=0;
  }
  else  
  {    duty[0]=0;
       duty[1]=moto1;
  }
  if(moto2>0) 
  {   
       duty[2]=0;
       duty[3]=moto2;
  }
  else  
  {    
       duty[2]=moto2;
       duty[3]=0;
  }
  ftm_pwm(duty);
}
/**************************************************************************
函数功能：限制PWM赋值  
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{
  int Amplitude = 300;  //===PWM满幅是255 限制在250

  if (Motor1 < -Amplitude) Motor1 = -Amplitude;
  if (Motor1 > Amplitude)  Motor1 = Amplitude;
  if (Motor2 < -Amplitude) Motor2 = -Amplitude;
  if (Motor2 > Amplitude)  Motor2 = Amplitude;
}
/**************************************************************************
函数功能：5ms控制函数 核心代码 
入口参数：无
返回  值：无
**************************************************************************/
void control(int ad,int Velocity_Left,int Velocity_Right)
{
   
    Velocity_Pwm = velocity(Velocity_Left, Velocity_Right);//速度PI控制，控制周期40ms
    Velocity_Left = 0;   
    Velocity_Right = 0;    

    Turn_Pwm = turn(ad);//转向环


    Motor1 = Velocity_Pwm + Turn_Pwm+LD;  //直立速度转向环的叠加
    Motor2 = Velocity_Pwm - Turn_Pwm+RD; //直立速度转向环的叠加
    Xianfu_Pwm();//限幅

    Set_Pwm(Motor1, Motor2);//如果不存在异常，赋值给PWM寄存器控制电机


}