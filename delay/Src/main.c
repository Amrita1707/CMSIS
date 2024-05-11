#include "stm32f407xx.h"

void clk_config();
void timer_config();
void gpio_config();
int count =0, count1=0;

int main()
{
   clk_config();
   gpio_config();
   timer_config();

   while(1)
   {
      //wait until UIF bit of the TIM7 status register is set
	   while(!(TIM7->SR & 1)){}
	   {
		   //clear UIF bit
		   TIM7->SR &= 0;

		   count++;
		   count1++;
		   if(count == 100)
		   {
			   // Toggle GPIOD Pin 12 (LED) for every 100ms
			   GPIOD->ODR ^= GPIO_ODR_OD12;

			   count=0;
		   }
		   if(count1 == 500)
		   {
			   // Toggle GPIOD Pin 12 (LED) for every 500ms
			  	GPIOD->ODR ^= GPIO_ODR_OD13;

			  	count1=0;
		   }
	   }
   }
}

void clk_config()
{
	// TIM7 clock enabled
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	// Enable clock for GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

}

void gpio_config()
{
	// Set GPIOD Pin 12 as output
    GPIOD->MODER |=  GPIO_MODER_MODE12_0;

    GPIOD->MODER |=  GPIO_MODER_MODE13_0;
}

void timer_config()
{

	//Counter value
	TIM7->CNT = 0;

	// Auto-reload value
	TIM7->ARR = 16000-1;

	//Counter enabled
	TIM7->CR1 |= TIM_CR1_CEN;
}
