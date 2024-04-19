#include "Led.h"   
 
 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP ;
	GPIO_InitStruct.GPIO_Pin=LED_RED_PIN|LED_GREEN_PIN|LED_YELLOW_PIN;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz ;
 
	GPIO_SetBits(LED_PORT,LED_RED_PIN|LED_GREEN_PIN|LED_YELLOW_PIN);
	GPIO_Init(LED_PORT,&GPIO_InitStruct);
	
 
}
