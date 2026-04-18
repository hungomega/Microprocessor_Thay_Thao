#include "Middle_Layer.h"

void Mid_GPIO_Init()
{
	Ip_GPIO_Init();
}
void Mid_ADC_Init()
{
	Ip_ADC_Init();
}
void Mid_TIMER_BaseInit()
{
	Ip_TIMER_BaseInit();
}
void Mid_DMA_Sound_Config(void)
{
	DMA_Sound_Config();
}
void Mid_UART1_Init(void)
{
	UART1_Init();
}
void Mid_UART1_SendByte(uint8_t b)
{
	if ( b > 255) return;
	UART1_SendByte(b);
}
void Mid_UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size)
{
	UART1_SendBuffer_Binary(pBuffer,size);
}
void Mid_delay_ms(int time)
{
	delay_ms(time);
}
