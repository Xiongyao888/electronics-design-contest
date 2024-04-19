#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "PWM.h"
#include "time.h"
#include "Key.h"


uint16_t x = 0,Keynum = 0;
uint16_t zx = 1816, zy =982;

int main(void)
{
	PWM_Init();
	KEY_Config();
	NVIC_Config();
	OLED_Init();
	Serial_Init();
	OLED_ShowString(2,1,"x:");
	PWM_SetCompare4(zx);
	PWM_SetCompare3(zy);
	while (1)
	{
		Keynum = Key_GetNum();
		if ( Keynum != 0 )
		{
			x = Keynum;
		}
		//OLED_ShowNum(2,4,x,2);
		if ( x == 1 )
		{
			//PWM_SetCompare4(1500);
			//PWM_SetCompare3(973);
			zx = 1816;
			zy = 982;//815
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			PWM_SetCompare4(zx);
			PWM_SetCompare3(zy);
			x = 0;			
		} else if ( x == 2 )
		{
			zy -= 5;
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			PWM_SetCompare3(zy);
			OLED_ShowNum(2,4,x,2);
			x = 0;
		} else if ( x == 3 )
		{
			zy += 5;
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			PWM_SetCompare3(zy);
			OLED_ShowNum(2,4,x,2);
			x = 0;
		} else if ( x == 4 )
		{
			zx += 5;
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			PWM_SetCompare4(zx);
			OLED_ShowNum(2,4,x,2);
			x = 0;
		} else if ( x == 5 )
		{
			zx -= 5;
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			PWM_SetCompare4(zx);
			OLED_ShowNum(2,4,x,2);
			x = 0;
		} else if ( x == 6 )
		{
			//Ë®Æ½×ó 1650 815   Ë®Æ½ÓÒ  1352 815
			//Ë®Æ½ÉÏ 1500 673   Ë®Æ½ÏÂ  1500 973
			//×óÉÏ½Ç 1659 676   ÓÒÉÏ½Ç  1357 676
			//×óÏÂ½Ç 1653 970   ÓÒÏÂ½Ç  1344 967
			OLED_ShowNum(2,4,x,2);
			//ÖÐÐÄµã
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1844); 
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1844); 
			Delay_ms(500);
			
			//×óÉÏ½Ç 1659 676 
			PWM_SetCompare3(840);  
			PWM_SetCompare4(1956);  
			Delay_ms(500);
			
			//Ë®Æ½ÉÏ 1500 673
			PWM_SetCompare3(859);  
			PWM_SetCompare4(1820);  
			Delay_ms(500);
			
			//ÓÒÉÏ½Ç  1357 676
			PWM_SetCompare3(859);  
			PWM_SetCompare4(1679); 
			Delay_ms(500);
			
			//ó Ë®Æ½ÓÒ  1352 815
			PWM_SetCompare3(982);  
			PWM_SetCompare4(1679); 
			Delay_ms(500);
			
			//ÓÒÏÂ½Ç  1344 967
			PWM_SetCompare3(1120);  
			PWM_SetCompare4(1679); 
			Delay_ms(500);
			
			//Ë®Æ½ÏÂ  1500 973
			PWM_SetCompare3(1120);  
			PWM_SetCompare4(1820); 
			Delay_ms(500);
			
			//×óÏÂ½Ç 1653 970
			PWM_SetCompare3(1105);  
			PWM_SetCompare4(1966); 
			Delay_ms(500);
			
			//Ë®Æ½×ó 1650 815
			PWM_SetCompare3(982);  
			PWM_SetCompare4(1956); 
			Delay_ms(500);
			
			//×óÉÏ½Ç 1659 676 
			PWM_SetCompare3(840);  
			PWM_SetCompare4(1948);  
			Delay_ms(500);
			
			//ÖÐÐÄµã
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1824);  
			Delay_ms(500);
			x = 0;
		} 
		else if ( x == 7 )
		{
			//Ë®Æ½×ó 1650 815   Ë®Æ½ÓÒ  1352 815
			//Ë®Æ½ÉÏ 1500 673   Ë®Æ½ÏÂ  1500 973
			//×óÉÏ½Ç 1659 676   ÓÒÉÏ½Ç  1357 676
			//×óÏÂ½Ç 1653 970   ÓÒÏÂ½Ç  1344 967
			OLED_ShowNum(2,4,x,2);
			//ÖÐÐÄµã
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1824);  
			Delay_ms(500);
			
			PWM_SetCompare3(950);  
			PWM_SetCompare4(1880);  
			Delay_ms(500);
			
			//×óÉÏ½Ç 1659 676 
			PWM_SetCompare3(930);  
			PWM_SetCompare4(1900);  
			Delay_ms(500);
			
			//Ë®Æ½ÉÏ 1500 673
			PWM_SetCompare3(930);  
			PWM_SetCompare4(1824);  
			Delay_ms(500);
			
			//ÓÒÉÏ½Ç  1357 676
			PWM_SetCompare3(930);  
			PWM_SetCompare4(1735); 
			Delay_ms(500);
			
			//ó Ë®Æ½ÓÒ  1352 815
			PWM_SetCompare3(982);  
			PWM_SetCompare4(1735); 
			Delay_ms(500);
			
			//ÓÒÏÂ½Ç  1344 967
			PWM_SetCompare3(1036);  
			PWM_SetCompare4(1735); 
			Delay_ms(500);
			
			//Ë®Æ½ÏÂ  1500 973
			PWM_SetCompare3(1036);  
			PWM_SetCompare4(1824); 
			Delay_ms(500);
			
			//×óÏÂ½Ç 1653 970
			PWM_SetCompare3(1035);  
			PWM_SetCompare4(1900); 
			Delay_ms(500);
			
			//Ë®Æ½×ó 1650 815
			PWM_SetCompare3(982);  
			PWM_SetCompare4(1900); 
			Delay_ms(500);
			
			//×óÉÏ½Ç 1659 676 
			PWM_SetCompare3(930);  
			PWM_SetCompare4(1900);  
			Delay_ms(500);
			
			//ÖÐÐÄµã
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1816); 
			PWM_SetCompare3(982);   
			PWM_SetCompare4(1816); 
			Delay_ms(500);
			x = 0;
		}
		else if (x == 8)
		{
			//  ÉÏ580   ÏÂ1018
			//  ×ó1700  ÓÒ1300
			OLED_ShowNum(2,4,x,2);
			while ( Serial_GetRxFlag() == 0 ) ;
			if ( Serial_RxPacket[0] == 1)
			{
				if( Serial_RxPacket[1] == 0 )
					;
				else 
					zx -= 1;
			} else if ( Serial_RxPacket[0] == 2)
			{
				if( Serial_RxPacket[1] == 0 )
					;
				else 
					zx += 1;
			}
			if ( Serial_RxPacket[2] == 1)
			{
				if( Serial_RxPacket[3] == 0 )
					;
				else 
					zy += 1;
			} else if ( Serial_RxPacket[2] == 2)
			{
				if( Serial_RxPacket[3] == 0 )
					;
				else 
					zy -= 1;
			}
			if ( zx >= 1980)
				zx = 1980;
			if ( zx <= 1300)
				zx = 1300;
			if ( zy >= 1180)
				zy = 1180;
			if ( zy <= 673)
				zy = 673;
			PWM_SetCompare3(zy);  //  ÉÏ580   ÏÂ1018
			PWM_SetCompare4(zx);
			//OLED_ShowNum(3, 4,Serial_RxPacket[1],4);
			//OLED_ShowNum(4, 4,Serial_RxPacket[3],4);
			
			//OLED_ShowNum(4,10,y,4);
			Delay_ms(30);
		}
		
	}
	
}
void KEY1_IRQHandler(void)
{
	if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0) ;
		Delay_ms(20);
		
		EXTI_ClearITPendingBit(KEY1_Line);
		x = 3;
	}

	  
	//key3
	if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7) == 0) ;
		Delay_ms(20);
		
		EXTI_ClearITPendingBit(KEY3_Line);
		x = 4;
	}

	//key8
	if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0) ;
		Delay_ms(20);
		
		EXTI_ClearITPendingBit(KEY8_Line);
		x = 2;
	} 
}
 
//void KEY2_IRQHandler(void)
//{
//	//key2
//	if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == 0 )
//	{
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == 0) ;
//		Delay_ms(20);
//		
//		EXTI_ClearITPendingBit(KEY2_Line);
//		x = 8;
//	} 

	//key6
//	if ( GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) == 0 )
//	{
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) == 0) ;
//		Delay_ms(20);
//		
//		EXTI_ClearITPendingBit(KEY6_Line);
//		x = 6;
//	} 

	//key7
//	if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0 )
//	{
//		Delay_ms(20);
//		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0) ;
//		Delay_ms(20);
//		
//		EXTI_ClearITPendingBit(KEY7_Line);
//		x = 7;
//	} 
//}



void KEY4_IRQHandler(void)
{
	if ( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0) ;
		Delay_ms(20);
		
		EXTI_ClearITPendingBit(KEY4_Line);
		x = 1;
	} 

	EXTI_ClearITPendingBit(KEY4_Line);  
}
void KEY5_IRQHandler(void)
{
	if ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0 )
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0) ;
		Delay_ms(20);
		
		EXTI_ClearITPendingBit(KEY5_Line);
		x = 5;
	} 
}
