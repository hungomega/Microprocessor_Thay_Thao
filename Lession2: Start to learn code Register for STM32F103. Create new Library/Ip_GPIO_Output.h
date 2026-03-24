#ifndef __IP_GPIO_OUTPUT_H
#define __IP_GPIO_OUTPUT_H
#include "stm32f10x.h"

void Ip_GPIO_Output_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin_Select);
#endif
