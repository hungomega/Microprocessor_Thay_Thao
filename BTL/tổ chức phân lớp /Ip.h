#ifndef __IP_LAYER_H
#define __IP_LAYER_H

#include "stm32f10x.h"


extern uint16_t Sound_Buffer[128];

void Ip_GPIO_Init(void);

void Ip_ADC_Init(void);

void Ip_TIMER_BaseInit(void);

void DMA_Sound_Config(void);

void UART1_Init(void);

void UART1_SendByte(uint8_t b);

void UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size);

void delay_ms(int time);

#endif
