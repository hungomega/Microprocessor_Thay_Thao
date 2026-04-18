#ifndef __APP_LAYER_H
#define __APP_LAYER_H

#include "Middle_Layer.h"

void App_GPIO_Init(void);

void App_ADC_Init(void);

void App_TIMER_BaseInit(void);

void App_DMA_Sound_Config(void);

void App_UART1_Init(void);

void App_UART1_SendByte(uint8_t b);

void App_UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size);

void App_delay_ms(int time);

#endif
