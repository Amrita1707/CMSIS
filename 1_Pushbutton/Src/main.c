/*
 Author            : Amrita N S
 Date              : 19-04-2024
 Development board : STM32F407VGT6 Discovery Board
 IDE               : STM32CubeIDE

 Program to interface inbuilt pushbutton with the inbuilt led on the stm32f407vgt6 discovery board.
 GPIOD -> PIN 12 -> Green LED
 GPIOA -> PIN 0  -> Pushbutton

 Steps:

1.Enable clock access to GPIOD by setting bit 3 of the RCC AHB1 peripheral clock enable register (RCC_AHB1ENR).

2. Enable clock access to GPIOA by setting bit 0 of the RCC AHB1 peripheral clock enable register (RCC_AHB1ENR).

3. Configure PA0 (MODER0) as an input by clearing bits MODE0_0 and MODE0_1 of the GPIO port mode register (GPIOx_MODER).
   Mode 00: General purpose input mode.

4. Configure PD12 (MODER12) as an output by setting bit MODE12_0 of the GPIO port mode register (GPIOx_MODER).
   Mode 01: General purpose output mode.

5. Check if the button is pressed or not, and accordingly, toggle the LED

*/

#include <stdint.h>
#include "stm32f407xx.h"

// Function prototypes
void clock_config();
void gpio_mode_config();

int main(void)
{
	// Configure system clock
    clock_config();

    // Configure GPIO modes
    gpio_mode_config();

    while(1)
    {
    	// Check if GPIOA Pin 0(inbuilt pushbutton) is high
        if(GPIOA->IDR & 0x01)
        {
        	// Set PD12 high (led)
            GPIOD->BSRR |= GPIO_BSRR_BS12;
        }
        else
        {
        	// Reset PD12 (led)
            GPIOD->BSRR |= GPIO_BSRR_BR12;
        }
    }
}

// Function to configure system clock
void clock_config()
{
	// Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Enable clock for GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}

// Function to configure GPIO modes
void gpio_mode_config()
{
	// Clear mode bits for GPIOA Pin 0
    GPIOA->MODER &= ~GPIO_MODER_MODE0_0;
    GPIOA->MODER &= ~GPIO_MODER_MODE0_1;

    // Set GPIOD Pin 12 as output
    GPIOD->MODER |=  GPIO_MODER_MODE12_0;
}
