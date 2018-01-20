#include "isr.h"


//����0�����жϷ�������
void UART0_ISR(void)
{
  uint8_t ReData;
  uint8_t txt[20];
  
  DisableInterrupts ;//�����ж�
  
  ReData = Uart_GetChar(UARTR0);
  sprintf((char*)txt,"UART0_RX: %c \n",ReData);  
  Uart_SendString(UARTR0,txt);
  
  EnableInterrupts;   //�����ж�
}


//����1�����жϷ�������
void UART1_ISR(void)
{
  uint8_t ReData;
  uint8_t txt[20];
  
  DisableInterrupts ;//�����ж�
  
  ReData = Uart_GetChar(UARTR1);
  sprintf((char*)txt,"UART1_RX: %c \n",ReData);  
  Uart_SendString(UARTR1,txt);
  
  EnableInterrupts;   //�����ж�
}

//����2�����жϷ�������
void UART2_ISR(void)
{
  uint8_t ReData;
  uint8_t txt[20];
  
  DisableInterrupts ;//�����ж�
  
  ReData = Uart_GetChar(UARTR2);
  sprintf((char*)txt,"UART2_RX: %c \n",ReData);  
  Uart_SendString(UARTR2,txt);
  
  EnableInterrupts;   //�����ж�
}

//��ʱ��0�жϺ���
void PIT0_ISR(void)
{
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;//����жϱ�־λ
  LED_Ctrl(LEDALL,LEDRVS);
  
}

//��ʱ��1�жϺ���
void PIT1_ISR(void)
{
  char  txt[30]="X:";
  int number=0;  
  PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;//����жϱ�־λ
  if(gpio_get(PTH7))
    number=FTM_count_get(CFTM0);
  else
    number=-FTM_count_get(CFTM0);
  sprintf(txt,"FTM0 PTE0: %05d \n",number);
  Uart_SendString(UARTR2,(uint8_t*)txt); 
  LCD_P6x8Str(0,0,txt);
  if(gpio_get(PTH5))
    number=FTM_count_get(CFTM1);
  else
    number=-FTM_count_get(CFTM1);
  sprintf(txt,"FTM1 PTE7: %05d \n",number);
  Uart_SendString(UARTR2,(uint8_t*)txt);
  LCD_P6x8Str(0,2,txt);
  FTM_count_clean(CFTM0); 
  FTM_count_clean(CFTM1);
}



//KBI0�жϺ���
void KBI0_Isr(void)	
{  
  KBI0->SC |= KBI_SC_KBACK_MASK;       /* clear interrupt flag */
  uint16_t n = PTn(KBI_PTB5) ;   //PTA0���Ŵ����ж� 
  if(KBI0->SP &(1<<n))
  {
    //�û����� 
    LED_Ctrl(LED0, LEDRVS);             
  } 
}

//KBI1�жϺ���
void KBI1_Isr(void)	
{  
  KBI1->SC |= KBI_SC_KBACK_MASK;                /* clear interrupt flag */
  
  uint16_t n = PTn(KBI_PTH2) ;   //PTH2���Ŵ����ж� 
  if(KBI1->SP &(1<<n))
  {
    //�û����� 
    LED_Ctrl(LED1, LEDRVS);             
  }
}


/*****************************************************************************//*!
*
* @brief  FTM0_Isr interrupt service routine.
*        
* @param  none.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM0_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM0]->SC &= ~FTM_SC_TOF_MASK;
  
}

/*****************************************************************************//*!
*
* @brief  FTM1_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM1_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM1]->SC &= ~FTM_SC_TOF_MASK;
}

/*****************************************************************************//*!
*
* @brief  FTM2_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/

void FTM2_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM2]->SC &= ~FTM_SC_TOF_MASK;
}