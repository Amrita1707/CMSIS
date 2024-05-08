/*

Author            : Amrita N S
Date              : 08-05-2024
Development board : STM32F407VGT6 Discovery Board
IDE               : STM32CubeIDE

Program to toggle led in every 1 seconds by using basic timer (Timer7-polling method)

*Initializes the clock configuration for TIM7 and GPIOD peripherals by enabling their respective clock signals in the RCC peripheral.

*Configure GPIOD Pin 12 as an output pin by setting the corresponding mode bits in the MODER register.

*The timer configuration function sets up TIM7. It initializes the counter value (CNT) to 0 and sets the auto-reload value (ARR) to 16000.

*After configuring the timer, the main loop waits until the update interrupt flag (UIF) of TIM7 status register (SR) is set.

*Once the flag is set, it clears the flag, increments a count variable, and checks if the count has reached 1000.

*If the count reaches 1000, it toggles the state of GPIOD Pin 12, effectively toggling the LED connected to it.

*The loop continues indefinitely, ensuring that the LED toggles approximately every second.

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
      //wait until UIF bit of the TIM7 status register is set
	   while(!(TIM7->SR & 1)){}
	   {
		   //clear UIF bit
		   TIM7->SR &= 0;

		   count++;
		   if(count == 1000)
		   {
			   // Toggle GPIOD Pin 12 (LED) for every 1seconds
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
