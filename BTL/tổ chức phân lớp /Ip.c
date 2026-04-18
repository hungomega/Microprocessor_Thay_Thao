#include "stm32f10x.h"
#include "stdio.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;

uint16_t Sound_Buffer[128];

void Ip_GPIO_Init()
{ 
	/*B1: Cap clock cho Port A*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/*B2: Cau hinh LED Output, Speed: 50MHz, Push-Pull*/
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void Ip_ADC_Init()
{
	/*B1: Cap clock cho ADC1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/*B2: Cau hinh cho ADC1*/
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_Init( ADC1, &ADC_InitStruct);
	/*B3: Kich hoat ADC1*/
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_ExternalTrigConvCmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
}
void Ip_TIMER_BaseInit()
{
	/*B1: Cap clock cho TIM3*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	/*B2: Cau hinh cho TIM3, tao tan so lay mau 16kHz, dem len*/
	TIM_InitStruct.TIM_Prescaler = 72-1;
	TIM_InitStruct.TIM_Period = 62 - 1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_InitStruct);
	/*B3: Kich hoat TIM3*/
	TIM_Cmd(TIM3, ENABLE);
	
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
}
void DMA_Sound_Config(void) {
    DMA_InitTypeDef DMA_InitStruct;

    /* B1: Cap clock cho DMA1*/
    /* DMA1 nam tren bus  AHB, phai bat clock o day thi cac thanh ghi DMA moi hoat dong */ 
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

		/* B2: Cau hinh cho DMA1*/
    /* Dua Channel 1 ve trang thai mac dinh (Reset) */ 
    DMA_DeInit(DMA1_Channel1); 

    /* Dia chi nguon: Thanh ghi du lieu cua ADC1 */ 
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
    /* Dia chi dich: Dia chi cua mang Sound_Buffer trong RAM */ 
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Sound_Buffer;
    
    /*Huong chuyen: Tu ngoai vi (Peripheral) sang bo nho (Memory)*/ 
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
    
    /*So luong mau can lay (Buffer Size)*/ 
    DMA_InitStruct.DMA_BufferSize = 128;
    
    /*Khong tang dia chi ngoai vi (vi chi doc tu 1 thanh ghi ADC duy nhat)*/ 
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*Tang dia chi bo nho (de luu mau 1 vao index 0, mau 2 vao index 1...)*/ 
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    
    /*Kich thuoc du lieu: 16-bit (HalfWord) vi ADC STM32 la 12-bit*/ 
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    
    /*Che do Circular: Tu dong quay lai dau mang khi day*/  
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
    
    /*Do uu tien: Cao (High) de dam bao khong mat mau am thanh*/ 
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;
    
    /*Tat che do Memory-to-Memory (vi ta dang dang Peripheral-to-Memory)*/ 
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;

    /*Ghi cau hinh vao phan cung*/ 
    DMA_Init(DMA1_Channel1, &DMA_InitStruct);

    /*Kich hoat DMA Channel 1*/ 
    DMA_Cmd(DMA1_Channel1, ENABLE);	
}

void UART1_Init(void)
{
		/*B1: USART1 clock*/ 
    RCC->APB2ENR |= (1 << 14);  
		/*B2: Cau hinh UART truyen va nhan du lieu*/
	
    /*PA9 (TX) - AF Push Pull - Truyen du lieu*/ 
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /*PA10 (RX) - Floating input - Nhan du lieu*/ 
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = 0x271; /*115200 baud (72MHz)*/ 
    USART1->CR1 |= (1 << 13) | (1 << 3); /*UE, TE*/ 
}

void UART1_SendByte(uint8_t b)
{
    while (!(USART1->SR & (1 << 7))); /*Cho cho den khi thanh ghi TXE = 1*/ 
    USART1->DR = b; /*Ghi du lieu vao thanh ghi DR de gui di*/
}

void UART1_SendBuffer_Binary(uint16_t *pBuffer, uint16_t size)
{
    uint16_t i;
    for (i = 0; i < size; i++)
    {
        /*1. Goi byte dong bo (Header) de ESP32 biet bat dau khung du lieu*/ 
        UART1_SendByte(0xAA); 
        
        /*2. Gui byte cao (High byte)*/ 
        UART1_SendByte((uint8_t)(pBuffer[i] >> 8));
        
        /*3. Gui byte thap (Low byte)*/ 
        UART1_SendByte((uint8_t)(pBuffer[i] & 0xFF));
    }
}
void delay_ms(int time)
{
	while(time)
	{
		SysTick -> CTRL = 5;
		SysTick -> VAL = 0;
		SysTick ->LOAD = 72000 - 1;
		while(!(SysTick -> CTRL & (1<<16)));
		--time;
	}
}
