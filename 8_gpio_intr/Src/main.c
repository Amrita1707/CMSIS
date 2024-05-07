/*

Author            : Amrita N S
Date              : 07-05-2024
Development board : STM32F407VGT6 Discovery Board
IDE               : STM32CubeIDE

Program to Triggering External Interrupt and LED Blink

*Enables clock signals for GPIOA, GPIOD, and the System Configuration Controller (SYSCFG) to facilitate their operation.

*Disables interrupts globally to prevent interrupt handling during configuration.

*Selects PA0 as the input source for EXTI0, enabling it to respond to external interrupts.

*Enables the falling trigger for EXTI0, indicating that an interrupt will be triggered on a falling edge.

*Enables EXTI0 interrupt and configures NVIC to handle EXTI0 interrupts.

*Globally enables interrupts to allow interrupt processing.

*Configures GPIOA Pin 0 as input and GPIOD Pin 12 as output.

*Handles EXTI0 interrupts by toggling GPIOD Pin 12.

*Clears the interrupt pending bit for EXTI0 after servicing the interrupt.

 */

#include "stm32f407xx.h"
void intr();
void clk_config();
void mode_config();

int main()
{
   clk_config();
   intr();
   mode_config();
}

void clk_config()
{
	// Enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// Enable clock for GPIOD
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// System configuration controller clock enabled
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void intr()
{
	// Disable interrupts globally
	__disable_irq();

	// Select PA0 for EXTI0
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0 ;
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR1_EXTI1 ;
	SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR1_EXTI2 ;
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR1_EXTI3 ;

	//Falling trigger enabled (for Event and Interrupt) for input line.
     EXTI->FTSR |= EXTI_FTSR_TR0;
	 //EXTI->RTSR |= EXTI_RTSR_TR0;

     //Interrupt request from EXTI0 is not masked
     EXTI->IMR |= EXTI_IMR_MR0;

     //Enable EXTI0 line in NVIC
      NVIC_EnableIRQ(EXTI0_IRQn);

      //Enable interrupts globally
     __enable_irq();
}

void mode_config()
{
	// Clear mode bits for GPIOA Pin 0 as input
	GPIOA->MODER &= ~GPIO_MODER_MODE0_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_1;

	// Set GPIOD Pin 12 as output
	GPIOD->MODER |=  GPIO_MODER_MODE12_0;
}

void EXTI0_IRQHandler(void)
{
	// Toggle GPIO pin 12 of GPIOD
	 GPIOD->ODR ^= GPIO_ODR_OD12;

	 //selected trigger request occurred
	 //This bit is set when the selected edge event arrives on the external interrupt line.
	 //This bit is cleared by programming it to ‘1’.
	 EXTI->PR |= EXTI_PR_PR0;
}
