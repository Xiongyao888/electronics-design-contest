#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

extern int16_t Cx,Cy,Cz; 
void Serial_Init(void);
void USART1_IRQHandler(void);

#endif
