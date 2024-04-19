#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle1(float Angle)
{
	PWM_SetCompare2(Angle / 360 * 2000 + 100);
}
void Servo_SetAngle2(float Angle)
{
	PWM_SetCompare3(Angle / 360 * 2000 + 100);
}

