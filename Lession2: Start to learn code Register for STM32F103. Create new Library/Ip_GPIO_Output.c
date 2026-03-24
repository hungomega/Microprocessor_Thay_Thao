 #include "Ip_GPIO_Output.h"

void Ip_GPIO_Output_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin_Select)
{
	// b1 : cap clock cho portA
	if(GPIOx == GPIOA) 
	{
		RCC -> APB2ENR |= 0x04;
	}
	else if(GPIOx == GPIOB)  
	{
		RCC -> APB2ENR |= 0x08;	
		// RCC -> APB2ENR |= (1 << 3);
	}
	else if(GPIOx == GPIOC)  
	{
		RCC -> APB2ENR |= 0x10;	
		// RCC -> APB2ENR |= (1 << 4);
	}
	// b2 : configure Mode[1:0] = 11 : speed 50Mhz , CNF[1:0] = 00 output mode
	if(GPIO_Pin_Select < 8)
	{
		 GPIOx -> CRL |= ( 3 << GPIO_Pin_Select*4 ); // PA0 <-> bit0 = 3 , PA5 <-> bit20 = 3
	}
	else 
	{
		GPIOx -> CRH |= ( 3 << (GPIO_Pin_Select - 8) * 4 ); // PA8 <-> bit0 = 3  , PA9 <-> bit4 = 3, PA10 <-> bit8 = 3 
	}
}







 
