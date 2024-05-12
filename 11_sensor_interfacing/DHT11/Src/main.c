/*



*/

#include "stm32f407xx.h"
void clk_config();
void gpio_config();
void dht_response();
int i,j,k,l,m,n;
int data;
int main()
{
	clk_config();
	gpio_config();
	// Set PA1 high
	GPIOA->ODR |= GPIO_ODR_OD1;
	for(i=0; i<18000; i++)
	{
		// Set PA1 low
	    GPIOA->ODR &= ~GPIO_ODR_OD1;
	}
	for(j=0; j<40; j++)
	{
		// Set PA1 high
		GPIOA->ODR |= GPIO_ODR_OD1;
	}
	dht_response();
	for(k=0; k<54; k++)
	{
		if(GPIOA->IDR & 0x10)
			break;
	}
	for(l=0; l<80; l++)
	{
		if(GPIOA->IDR & 0x00)
			break;
	}

	for(m=0; m<54; m++)
	{
		if(GPIOA->IDR & 0x00)
		{
			for(n=1; n<=40;)
			{
				if(GPIOA->IDR & 0x10)
				{
                   n++;
				}
				else
					n=0;
				if( n == 24)
				{
                	 data = data * 10 + 0;
                	 m=0;
				}
				else if( n > 24)
				{
                	 data = data * 10 + 1;
                	 m=0;
				}

			}

		}
	}
}

void clk_config()
{
	// Enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void gpio_config()
{
	// set mode bits for GPIOA as output
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}

void dht_response()
{
	//Set PA1 pin as input
	GPIOA->MODER &= ~GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}





/*void data_rx()
{
	int i,humidity;
	for(i=0; i<15; i++)
	{
		humidity = ( humidity * 10) + ((GPIOA->IDR)>>1) ;
		TIM7_delay_us(50);
	}
}*/
