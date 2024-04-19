#include "Key.h"
#include "Delay.h"
 
void NVIC_Config(void)
{
	NVIC_InitTypeDef	NVIC_Initstruct;
	
	//Ƕ������KEY1�жϿ�����
 
    //�������ȼ���Ϊ1������Խ�ͣ��ȼ�Խ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    //ѡ���ж�Դ����KEY1����
	NVIC_Initstruct.NVIC_IRQChannel=KEY1_IRQn;
    //��ռ���ȼ�����Ϊ1
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
    //�����ȼ�Ϊ1
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
    //ʹ���ж�ͨ��
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_Initstruct);
 
    //KEY2����������Ķ�һ��
	//NVIC_Initstruct.NVIC_IRQChannel=KEY2_IRQn;
	//NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=KEY1_IRQn;
	NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=KEY4_IRQn;
	NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=KEY5_IRQn;
	NVIC_Init(&NVIC_Initstruct);
	//NVIC_Initstruct.NVIC_IRQChannel=KEY2_IRQn;
	//NVIC_Init(&NVIC_Initstruct);
	//NVIC_Initstruct.NVIC_IRQChannel=KEY2_IRQn;
	//NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=KEY1_IRQn;
	NVIC_Init(&NVIC_Initstruct);
	

}
 
 
void KEY_Config(void)
{		
	GPIO_InitTypeDef	GPIO_InitStruct;
	EXTI_InitTypeDef	EXTI_Initatruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//KEY1/2ʱ��ʹ��
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
	//RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(KEY5_GPIO_CLK,ENABLE);
	//RCC_APB2PeriphClockCmd(KEY6_GPIO_CLK,ENABLE);
	//RCC_APB2PeriphClockCmd(KEY7_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(KEY8_GPIO_CLK,ENABLE);
	
    // ��ʼ���жϿ�����   
	NVIC_Config();
    
    //�����������룬����������������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU ;
	GPIO_InitStruct.GPIO_Pin=KEY1_GPIO_PIN;
	
    //EXTI�ź�Դ��ѡ��
	GPIO_EXTILineConfig(KEY1_PortSource,KEY1_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line6;
    //����Ϊ�ж�ģʽ
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
    //�����ؼ�⣬����Ҳ�������½��غ������½���
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
    //ʹ���ж�
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);  
 
	GPIO_Init(KEY1_PORT,&GPIO_InitStruct);
	
	//KEY1��ʼ��
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY1_GPIO_PIN;
	GPIO_Init(KEY1_PORT,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY1_PortSource,KEY1_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line6;
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);	
	
//	//KEY2��ʼ��
//	RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK,ENABLE);
//	GPIO_InitStruct.GPIO_Pin=KEY2_GPIO_PIN;
//	GPIO_Init(KEY2_PORT,&GPIO_InitStruct);
//	
//	GPIO_EXTILineConfig(KEY2_PortSource,KEY2_PinSource);
//	EXTI_Initatruct.EXTI_Line=EXTI_Line13;
//	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_Initatruct);

	//KEY3��ʼ��
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY3_GPIO_PIN;
	GPIO_Init(KEY3_PORT,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY3_PortSource,KEY3_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line7;
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);	
	
	//KEY4��ʼ��
	RCC_APB2PeriphClockCmd(KEY4_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY4_GPIO_PIN;
	GPIO_Init(KEY4_PORT,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY4_PortSource,KEY4_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line4;
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);

	//KEY5��ʼ��
	RCC_APB2PeriphClockCmd(KEY5_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY5_GPIO_PIN;
	GPIO_Init(KEY5_PORT,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY5_PortSource,KEY5_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line1;
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);
	
//	//KEY6��ʼ��
//	RCC_APB2PeriphClockCmd(KEY6_GPIO_CLK,ENABLE);
//	GPIO_InitStruct.GPIO_Pin=KEY6_GPIO_PIN;
//	GPIO_Init(KEY6_PORT,&GPIO_InitStruct);
//	
//	GPIO_EXTILineConfig(KEY6_PortSource,KEY6_PinSource);
//	EXTI_Initatruct.EXTI_Line=EXTI_Line10;
//	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_Initatruct);
	
//	//KEY7��ʼ��
//	RCC_APB2PeriphClockCmd(KEY7_GPIO_CLK,ENABLE);
//	GPIO_InitStruct.GPIO_Pin=KEY7_GPIO_PIN;
//	GPIO_Init(KEY7_PORT,&GPIO_InitStruct);
//	
//	GPIO_EXTILineConfig(KEY7_PortSource,KEY7_PinSource);
//	EXTI_Initatruct.EXTI_Line=EXTI_Line12;
//	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
//	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
//	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_Initatruct);
	
	//KEY8��ʼ��
	RCC_APB2PeriphClockCmd(KEY8_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Pin=KEY8_GPIO_PIN;
	GPIO_Init(KEY8_PORT,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(KEY8_PortSource,KEY8_PinSource);
	EXTI_Initatruct.EXTI_Line=EXTI_Line5;
	EXTI_Initatruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initatruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initatruct.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initatruct);
}

 uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);
		Delay_ms(20);
		KeyNum = 6;
	}
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);
		Delay_ms(20);
		KeyNum = 7;
	}
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);
		Delay_ms(20);
		KeyNum = 8;
	}
	
	return KeyNum;
}


