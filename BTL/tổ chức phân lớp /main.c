#include "stm32f10x.h"
#include "App_layer.h"


int main()
{
	
	App_GPIO_Init();
	
	App_DMA_Sound_Config();
	
	App_ADC_Init();
	
	App_TIMER_BaseInit();
	
	App_UART1_Init();
	
	while(1)
	{
		volatile uint32_t i;
  
       if (DMA_GetFlagStatus(DMA1_FLAG_TC1)) 
        {
            /**/
            DMA_ClearFlag(DMA1_FLAG_TC1);
            
            /*Tat TIM3*/ 
            TIM_Cmd(TIM3, DISABLE); 

            /*Thuc hien truyen Binary qua ESP32 bang UART*/ 
            App_UART1_SendBuffer_Binary(Sound_Buffer, 128);

            /*Bat lai TIM3*/ 
            TIM_Cmd(TIM3, ENABLE);
            
            /**/
            App_delay_ms(200);
        }
	
	}
}
