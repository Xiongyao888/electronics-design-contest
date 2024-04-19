#ifndef __KEY_H
#define __KEY_H

 
#include "stm32f10x.h"
 
//KEY1
#define KEY1_GPIO_CLK			RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO
 
#define KEY1_GPIO_PIN			GPIO_Pin_6
#define KEY1_PORT				GPIOA
#define	KEY1_IRQn				EXTI9_5_IRQn 
#define	KEY1_PortSource			GPIO_PortSourceGPIOA
#define KEY1_PinSource			GPIO_PinSource6
#define KEY1_IRQHandler			EXTI9_5_IRQHandler
#define	KEY1_Line				EXTI_Line6
 
//KEY2
//#define KEY2_GPIO_CLK			RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO
// 
//#define KEY2_GPIO_PIN			GPIO_Pin_13
//#define KEY2_PORT				GPIOC
//#define	KEY2_IRQn				EXTI15_10_IRQn
//#define	KEY2_PortSource			GPIO_PortSourceGPIOC
//#define KEY2_PinSource			GPIO_PinSource13
//#define KEY2_IRQHandler			EXTI15_10_IRQHandler
//#define	KEY2_Line				EXTI_Line13

//KEY3     
#define KEY3_GPIO_CLK			RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO
           
#define KEY3_GPIO_PIN			GPIO_Pin_7
#define KEY3_PORT				GPIOA
//#define	KEY3_IRQn				EXTI9_5_IRQn  
#define	KEY3_PortSource			GPIO_PortSourceGPIOA
#define KEY3_PinSource			GPIO_PinSource7
//#define KEY3_IRQHandler			EXTI9_5_IRQHandler
#define	KEY3_Line				EXTI_Line7

//KEY4
#define KEY4_GPIO_CLK			RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO
           
#define KEY4_GPIO_PIN			GPIO_Pin_4
#define KEY4_PORT				GPIOA
#define	KEY4_IRQn				EXTI4_IRQn  
#define	KEY4_PortSource			GPIO_PortSourceGPIOA
#define KEY4_PinSource			GPIO_PinSource4
#define KEY4_IRQHandler			EXTI4_IRQHandler
#define	KEY4_Line				EXTI_Line4

//KEY5
#define KEY5_GPIO_CLK			RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO
           
#define KEY5_GPIO_PIN			GPIO_Pin_1
#define KEY5_PORT				GPIOB
#define	KEY5_IRQn				EXTI1_IRQn
#define	KEY5_PortSource			GPIO_PortSourceGPIOB
#define KEY5_PinSource			GPIO_PinSource1
#define KEY5_IRQHandler			EXTI1_IRQHandler
#define	KEY5_Line				EXTI_Line1

//KEY6
//#define KEY6_GPIO_CLK			RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO
//           
//#define KEY6_GPIO_PIN			GPIO_Pin_0
//#define KEY6_PORT				GPIOC
////#define	KEY6_IRQn				EXTI15_10_IRQn
//#define	KEY6_PortSource			GPIO_PortSourceGPIOC
//#define KEY6_PinSource			GPIO_PinSource0
////#define KEY6_IRQHandler			EXTI15_10_IRQHandler
//#define	KEY6_Line				EXTI_Line10
//KEY7     
//#define KEY7_GPIO_CLK			RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO         

//#define KEY7_GPIO_PIN			GPIO_Pin_12
//#define KEY7_PORT				GPIOB
////#define	KEY7_IRQn				EXTI15_10_IRQn
//#define	KEY7_PortSource			GPIO_PortSourceGPIOB
//#define KEY7_PinSource			GPIO_PinSource12
////#define KEY7_IRQHandler			EXTI15_10_IRQHandler
//#define	KEY7_Line				EXTI_Line12

//KEY8
#define KEY8_GPIO_CLK			RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO          

#define KEY8_GPIO_PIN			GPIO_Pin_5
#define KEY8_PORT				GPIOA
//#define	KEY8_IRQn				EXTI9_5_IRQn
#define	KEY8_PortSource			GPIO_PortSourceGPIOA
#define KEY8_PinSource			GPIO_PinSource5
//#define KEY8_IRQHandler			EXTI9_5_IRQHandler
#define	KEY8_Line				EXTI_Line5

void KEY_Config(void);
void NVIC_Config(void);
uint8_t Key_GetNum(void);

#endif



