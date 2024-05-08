/*

Author            : Amrita N S
Date              : 06-05-2024
Development board : STM32F407VGT6 Discovery Board
IDE               : STM32CubeIDE
*/


#include "stm32f407xx.h"

void clk_config();
void timer_config();
void gpio_config();
int count =0;

int main()
{
   clk_config();
   gpio_config();
   timer_config();

   while(1)
   {
   while(!(TIM7->SR & 1)){}
   {
	   TIM7->SR &= 0;
	   count++;
	   if(count == 1000)
	   {
	   // Toggle GPIOD Pin 12 (LED)
	   GPIOD->ODR ^= GPIO_ODR_OD12;

	   count=0;
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
}

void timer_config()
{

	//Counter value
	TIM7->CNT = 0;

	// Auto-reload value
	TIM7->ARR = 16000;

	//Counter enabled
	TIM7->CR1 |= TIM_CR1_CEN;
}
