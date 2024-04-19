#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

#include "Serial.h"
#include "Servo.h"
#include "PWM.h"

uint8_t KeyNum;
float Angle1=180;	//左右范围：左240 - 120右 	P1.1
float Angle2=280;	//上下范围：上240-320下	P1.2
float rate = 0.09;
int16_t errx = 0;
int16_t erry = 0;

uint8_t KeyNum = 0;
	
void Voiceinit()		//蜂鸣器初始化，I/o接PB12
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//GPIOB12推挽输出，控制蜂鸣器
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Voicebegin()		//蜂鸣器发声
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);		//低电平输出
		Delay_ms(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		Delay_ms(100);

}

void ledinit()			//PA11
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使用RCC开启GPIO时钟
	GPIO_InitTypeDef GPIO_InitStructure;						//初始化函数中结构体参数
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//推挽输出,OD为开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//选中11号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//反转速度
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//初始化GPIO
}

void ledshow()
{
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)0);		//指定端口置0(枚举类型)
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)1);		//指定端口置1(枚举类型)
		Delay_ms(100);
}

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//上拉输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{

	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0);
		Delay_ms(20);
		
		if(KeyNum==0)
		{
			KeyNum = 1;
		}
		else
		{
			KeyNum = 0;
		}

	}

	return KeyNum;
}


int main(void)
{
	OLED_Init();
	Key_Init();
	Serial_Init();
	Servo_Init();

	OLED_ShowString(1,1,"keynum:");
	OLED_ShowString(2,1,"Angley:");
	OLED_ShowString(3,1,"Cy:");
	OLED_ShowString(4,1,"Cz:");
	
  OLED_ShowString(1, 1, "Angle:");
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	while (1)
	{
		
		KeyNum = Key_GetNum();
		
		if(KeyNum==0){
		errx = Cy;
		erry = Cz;
		
		if(errx==0&&erry==0)
		{
			Voiceinit();		//声光报警
			ledinit();
			Voicebegin();		//蜂鸣器发声
			ledshow();
		}
		else
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
			GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)1);
		}

		
		if(errx <50)							//在右边
		{
			
//			Angle1 -= 1;
			
			Angle1 -= (errx*rate+1);		//右移
		}
		if(errx >200)
		{
			
//			Angle1 += 1;
			Angle1 += ((255-errx)*rate+1);
		}
		
		if(Angle1>240)
		{
			Angle1 = 240;
		}
		if(Angle1<120)
		{
			Angle1 = 120;
		}
		
		
		if(erry <50)					//在上面
		{
			
//			Angle2 -= 1;
			Angle2 -= (erry*rate+1);			//上移
		}
		if(erry >200)
		{
			
//			Angle2 += 1;
			
			Angle2 += ((255-erry)*rate+1);
		}
		
		if(Angle2>320)
		{
			Angle2 = 320;
		}
		if(Angle2<240)
		{
			Angle2 = 240;
		}
		
		
		Servo_SetAngle1(Angle1);		//P1.1
		Servo_SetAngle2(Angle2);		//P1.2
		
		Delay_ms(100);
		
		OLED_ShowNum(1, 9, KeyNum, 3);
		OLED_ShowNum(2, 9, Angle2, 3);
		OLED_ShowNum(3,4,Cy,4);
		OLED_ShowNum(4,4,Cz,4);		
	}
		else
		{
			while(1)
			{
				OLED_ShowNum(1, 9, KeyNum, 3);
				KeyNum = Key_GetNum();
				if(KeyNum ==0)
				{
					break;
				}
			}
		}
		

	}
}
