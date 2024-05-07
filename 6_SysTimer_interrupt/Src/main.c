/*

Author            : Amrita N S
Date              : 06-05-2024
Development board : STM32F407VGT6 Discovery Board
IDE               : STM32CubeIDE

Program to generate 1s delay using SysTick timer with interrupt method

*Set the reload value for the SysTick timer to achieve a 1-second period.

*Initialize the current value of the SysTick timer to 0.

*Enable the SysTick timer with the processor clock and enable SysTick interrupt

*Enable clock for GPIOD.

*Configure GPIOD Pin 12 as an output.

*Enter an infinite loop.

*Interrupt will be generated every one seconds

*Led will toggle when SysTick interrupt occurs

 */

#include "stm32f407xx.h"

void reload_val();
void curr_val();
void sys_timer();
void gpio_pin_config();
void SysTick_Handler();

int main()
{
	reload_val();
	curr_val();
	sys_timer();
	gpio_pin_config();
    SysTick_Handler();
}

void reload_val()
{
	// Set the reload value to achieve a 1 second period (16 MHz clock)
	SysTick->LOAD = 16000000-1;
}

void curr_val()
{
	// Set the current value to 0
	SysTick->VAL = 0;
}

void sys_timer()
{
	// Enable SysTick timer with processor clock and enable SysTick interrupt
	SysTick->CTRL |= 0x65;
}

// SysTick interrupt handler
void SysTick_Handler()
{
	 // Toggle GPIO pin 12 of GPIOD when SysTick interrupt occurs
	 GPIOD->ODR ^= GPIO_ODR_OD12;
}

void gpio_pin_config()
{
	// Enable clock for GPIOD
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Set GPIOD Pin 12 as output
	GPIOD->MODER |=  GPIO_MODER_MODE12_0;
}
