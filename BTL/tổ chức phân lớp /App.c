#include "App_Layer.h"

void App_GPIO_Init()
{
	Mid_GPIO_Init();
}
void App_ADC_Init()
{
	Mid_ADC_Init();
}
void App_TIMER_BaseInit()
{
	Mid_TIMER_BaseInit();
}
void App_DMA_Sound_Config(void)
{
	Mid_DMA_Sound_Config();
}
void App_UART1_Init(void)
{
	Mid_UART1_Init();
}
void App_UART1_SendByte(uint8_t b)
{
	Mid_UART1_SendByte(b);
}
void App_UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size)
{
	Mid_UART1_SendBuffer_Binary(pBuffer,size);
}
void App_delay_ms(int time)
{
	Mid_delay_ms(time);
}
