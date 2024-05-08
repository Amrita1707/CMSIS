/*

Author            : Amrita N S
Date              : 06-05-2024
Development board : STM32F407VGT6 Discovery Board
IDE               : STM32CubeIDE

Program to toggle led in every 1 seconds by using basic timer (Timer7) interrupt

*Initializes the clock configuration for TIM7 and GPIOD peripherals by enabling their respective clock signals in the RCC peripheral.

*It configures GPIOD Pin 12 as an output pin by setting the corresponding mode bits in the MODER register.

*The timer configuration function sets up TIM7. It initializes the counter value (CNT) to 0 and sets the auto-reload value (ARR) to 16000.

*It enables the update interrupt (UIE) for TIM7 by setting the corresponding bit in the DIER register to allow interrupt generation when the timer's update event occurs.

*The prescaler value is set to 1000, which divides the timer clock frequency by 1000.

*The code enables the TIM7 interrupt in the NVIC (Nested Vector Interrupt Controller) to handle the timer interrupt.

*Finally, the timer is enabled by setting the counter enable (CEN) bit in the CR1 register.

*Upon the timer's update event, the TIM7_IRQHandler function is executed.

*Inside the interrupt handler, it clears the update interrupt flag (UIF) of TIM7 by writing 0 to the corresponding bit in the status register (SR).

*It toggles the state of GPIOD Pin 12 by XORing the output data register (ODR) with the corresponding pin bit, effectively toggling the LED connected to it.

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

	//Update interrupt enabled
	TIM7->DIER |= TIM_DIER_UIE;

	//Prescaler value as 1000
	TIM7->PSC = 1000;

	//Enable Timer7 IRQ
	NVIC_EnableIRQ(TIM7_IRQn);

	//Counter enabled
	TIM7->CR1 |= TIM_CR1_CEN;
}

void TIM7_IRQHandler()
{
	//clear the UIF bit of the TIM7 status register
	TIM7->SR &= 0;

	// Toggle GPIOD Pin 12 (LED) for every 1seconds
	GPIOD->ODR ^= GPIO_ODR_OD12;
}
