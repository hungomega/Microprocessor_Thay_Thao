#ifndef __MIDDLE_LAYER_H
#define __MIDDLE_LAYER_H

#include "Ip_Layer.h"

void Mid_GPIO_Init(void);

void Mid_ADC_Init(void);

void Mid_TIMER_BaseInit(void);

void Mid_DMA_Sound_Config(void);

void Mid_UART1_Init(void);

void Mid_UART1_SendByte(uint8_t b);

void Mid_UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size);

void Mid_delay_ms(int time);
	
#endif
