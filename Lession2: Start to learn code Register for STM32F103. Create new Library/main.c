#include "Ip_GPIO_Output.h"

// NGUYEN HUU HUNG B23DCDT109

// Lap nhay led voi PA5
void GPIOA_Configure() // cau hinh thanh ghi
{
	// B1 : Cap Enable cho port A hoat dong 
	  RCC -> APB2ENR |= 0x00000004;
	/*cau hinh reset chan minh muon ve 0 truoc*/
	GPIOA -> CRL &= 0xFF0FFFFF; // luu ý thanh ghi CRL chi quan ly các chân bin tu 0 -> 7 thôi 
	/*Cau hinh cho chan pin va toc do*/
	GPIOA -> CRL |= 0x00300000;
}


void delay_ms(uint16_t time)
{
	int i , j ;
	for(i = 0 ; i < time ; i++)
	{
		// 0x2AFF tuong duong 1 ms
		for(j = 0 ; j < 0x2AFF ; j++);
	}
}
int main()
{
	//GPIOA_Configure(); // cau hinh thanh ghi
	Ip_GPIO_Output_Init(GPIOA,3); // PA3
	while(1)
	{
		GPIOA -> ODR |= 0x08;
		delay_ms(100);
		GPIOA -> ODR &=~(0x08);
		delay_ms(100);
	}
}
