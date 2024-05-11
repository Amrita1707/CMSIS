/*



*/

#include "stm32f407xx.h"
void clk_config();
void gpio_config();
void timer();
void dht_response();
void start_signal();
int count=0, count1;
int main()
{
	clk_config();
	gpio_config();
	// Set PA1 high
	GPIOA->ODR |= GPIO_ODR_OD1;
	start_signal();
	 while (1)
	 {
		   //wait until UIF bit of the TIM7 status register is set
		   while(!(TIM7->SR & 1)){}
		   {
		 	  //clear UIF bit
		 	  TIM7->SR &= 0;
		 	  while(++count <= 450)
		 	  {
		 		if(count == 450)
		 		{
		 			count1 = 1;
		 			// Set PA1 high
		 		    GPIOA->ODR |= GPIO_ODR_OD1;
		 		    break;
		 		}
		 	  }
		 	  if(count1 == 1)
		 	    dht_response();
		   }
	  }
}

void clk_config()
{
	// Enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// TIM7 clock enabled
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

}

void gpio_config()
{
	// set mode bits for GPIOA as output
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}

void timer()
{
	// Enable TIM6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	//Counter value
	TIM7->CNT = 0;

	// Auto-reload value
	TIM7->ARR = 640;

	//Counter enabled
	TIM7->CR1 |= TIM_CR1_CEN;
}

void start_signal()
{
	// Set PA1 low
	GPIOA->ODR &= ~GPIO_ODR_OD1;
}


void dht_response()
{

	//Set PA1 pin as input
	GPIOA->MODER &= ~GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}

	/*	// Check if GPIOA Pin 1 is low or not
		if(GPIOA->IDR & 0x00)
		{
			count1 =1 ;
		}

		if(GPIOA->IDR & 0x10)
		{
			data_rx();
		}
	}*/

/*void data_rx()
{
	int i,humidity;
	for(i=0; i<15; i++)
	{
		humidity = ( humidity * 10) + ((GPIOA->IDR)>>1) ;
		TIM7_delay_us(50);
	}
}*/
