#include "pid.h"
#include "headfile.h"
float Velocity_Kp=0.01;//,Velocity_Ki=0.4;//PID����
int Velocity_Pwm,Turn_Pwm=0;//�ٶȺͽǶ�
int Motor1,Motor2;
extern int duty[4];//���ռ�ձ�

int LD=300,RD=300,K=3;//�趨�����ʼ �����
/**************************************************************************
�������ܣ��ٶ�PI���� 
��ڲ��������ֱ����������ֱ�����
����  ֵ���ٶȿ���PWM
**************************************************************************/
int velocity(int encoder_left, int encoder_right)
{
  float Encoder_Least, Encoder, Movement;
  float Encoder_Integral, Target_Velocity;
 int Velocity;
 //int kp = 2, ki = kp / 200;    //PI����
 Movement = (LD+RD)/K;


  //=============�ٶ�PI������=======================//
  Encoder_Least = ((encoder_left + encoder_right) - 0);               //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩
//  Encoder *= 0.7;                                                   //===һ�׵�ͨ�˲���
//  Encoder += Encoder_Least * 0.3;                                   //===һ�׵�ͨ�˲���
//  Encoder_Integral += Encoder;                                      //===���ֳ�λ�� ����ʱ�䣺40ms
  Encoder_Integral = Movement-Encoder_Least;                  
//  if (Encoder_Integral > 21000)    Encoder_Integral = 21000;        //===�����޷�
//  if (Encoder_Integral < -21000) Encoder_Integral = -21000;         //===�����޷�
  Velocity =(int)( Encoder_Integral * Velocity_Kp); //+ Encoder_Integral * Velocity_Ki);                  //===�ٶȿ���
 // if (Turn_Off(KalFilter.angle, Battery_Voltage) == 1 || Flag_Stop == 1)    Encoder_Integral = 0;//С��ֹͣ��ʱ���������
  return Velocity;
}
/**************************************************************************
�������ܣ�ת����� 
��ڲ�����Z��������
����  ֵ��ת�����PWM
**************************************************************************/
int turn(int Turn_Convert)//ת�����int gyro //������������
{
  
  int Turn;
  float  Kp = 10, Kd = 0.001;  //PD����
 // Turn_Target += Turn_Convert;//���ݵ�иı�ת��ƫ��
  

  //if (Turn_Target > Turn_Amplitude)  Turn_Target = Turn_Amplitude; //===ת���ٶ��޷�
  //if (Turn_Target < -Turn_Amplitude) Turn_Target = -Turn_Amplitude;
  Turn = (int)(-Turn_Convert * Kp);// + gyro * Kd;         //===���Z�������ǽ���PD����
  return Turn;
}
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ��� 
��ڲ���������PWM������PWM
����  ֵ����
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
�������ܣ�����PWM��ֵ  
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{
  int Amplitude = 300;  //===PWM������255 ������250

  if (Motor1 < -Amplitude) Motor1 = -Amplitude;
  if (Motor1 > Amplitude)  Motor1 = Amplitude;
  if (Motor2 < -Amplitude) Motor2 = -Amplitude;
  if (Motor2 > Amplitude)  Motor2 = Amplitude;
}
/**************************************************************************
�������ܣ�5ms���ƺ��� ���Ĵ��� 
��ڲ�������
����  ֵ����
**************************************************************************/
void control(int ad,int Velocity_Left,int Velocity_Right)
{
   
    Velocity_Pwm = velocity(Velocity_Left, Velocity_Right);//�ٶ�PI���ƣ���������40ms
    Velocity_Left = 0;   
    Velocity_Right = 0;    

    Turn_Pwm = turn(ad);//ת��


    Motor1 = Velocity_Pwm + Turn_Pwm+LD;  //ֱ���ٶ�ת�򻷵ĵ���
    Motor2 = Velocity_Pwm - Turn_Pwm+RD; //ֱ���ٶ�ת�򻷵ĵ���
    Xianfu_Pwm();//�޷�

    Set_Pwm(Motor1, Motor2);//����������쳣����ֵ��PWM�Ĵ������Ƶ��


}