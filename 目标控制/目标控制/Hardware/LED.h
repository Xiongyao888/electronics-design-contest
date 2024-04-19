#ifndef __LED_H
#define	__LED_H
 
#include "stm32f10x.h"
 
//LED
#define LED_GPIO_CLK			RCC_APB2Periph_GPIOB
 
#define LED_GREEN_PIN			GPIO_Pin_7
#define LED_PORT				GPIOB
 
#define LED_RED_PIN				GPIO_Pin_15
#define LED_YELLOW_PIN			GPIO_Pin_6
 
#define		ON					1
#define 	OFF					0
 
#define	LED_GREEN(a)			if(a)\
									{GPIO_ResetBits(LED_PORT,LED_GREEN_PIN);}\
								else\
									{GPIO_SetBits(LED_PORT,LED_GREEN_PIN);}
 
#define	LED_RED(a)				if(a)\
									{GPIO_ResetBits(LED_PORT,LED_RED_PIN);}\
								else\
									{GPIO_SetBits(LED_PORT,LED_RED_PIN);}
 
 
#define	LED_YELLOW(a)			if(a)\
									{GPIO_ResetBits(LED_PORT,LED_YELLOW_PIN);}\
								else\
									{GPIO_SetBits(LED_PORT,LED_YELLOW_PIN);}
//´ò¿ªµÆ									
//#define	LED_G					{LED_GREEN(ON);LED_RED(OFF);LED_YELLOW(OFF);}
#define	LED_G					{LED_GREEN(ON)}
//#define	LED_R					{LED_GREEN(OFF);LED_RED(ON);LED_YELLOW(OFF);}
#define	LED_R					{LED_RED(ON)}
//#define	LED_Y					{LED_GREEN(OFF);LED_RED(OFF);LED_YELLOW(ON);}
#define	LED_Y					{LED_YELLOW(ON)}

//¹Ø±ÕµÆ									
#define	LED_GF					{LED_GREEN(OFF)}					
#define	LED_RF					{LED_RED(OFF)}
#define	LED_YF					{LED_YELLOW(OFF);}
 
#define LED_G_TOGGLE			{LED_PORT->ODR^=GPIO_Pin_7;}
#define LED_R_TOGGLE			{LED_PORT->ODR^=GPIO_Pin_15;}
#define LED_Y_TOGGLE			{LED_PORT->ODR^=GPIO_Pin_6;}
 
//BEEPER
#define BEEP_GPIO_CLK			RCC_APB2Periph_GPIOA
#define BEEP_PIN				GPIO_Pin_8
#define BEEP_PORT				GPIOA
 
 
void LED_GPIO_Config(void);

#endif


