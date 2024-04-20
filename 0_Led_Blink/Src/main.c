/*

 Author            : Amrita N S
 Date              : 18-04-2024
 Development board : STM32F407VGT6 Discovery Board
 IDE               : STM32CubeIDE
 Program t blinks LEDs connected to GPIO pins 12, 13, 14, and 15 in a sequential pattern.
 Steps:
 1. Enable clock access to GPIO Port D by setting bit 3 of the RCC AHB1 peripheral clock enable register (RCC_AHB1ENR).

 2. Configure GPIO pins 12, 13, 14, and 15 of GPIOD as general purpose output mode by setting corresponding bits
    in the GPIO port mode register (GPIOx_MODER) to 01.

 3. Enter an infinite loop to continuously blink the LEDs.

 4. Inside the loop, iterate through LEDs 12 to 15:
    a. Set the corresponding LED pin high using the BSRR register to turn on the LED.
    b. Call a delay function to create a delay, ensuring the LED stays on for a visible duration.
    c. Set the corresponding LED pin low using the BSRR register to turn off the LED.
    d. Call the delay function again to maintain the LED off state for a visible duration.

 */

#include <stdint.h>
#include "stm32f407xx.h"

int main(void)
{
    int i;

    // Enable clock for GPIO Port D
    RCC->AHB1ENR  |= RCC_AHB1ENR_GPIODEN;

    // Set GPIO pins 12, 13, 14, and 15 to general purpose output mode
    GPIOD->MODER  |=  GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_0 | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE15_0;

    // Infinite loop to blink LEDs
    while(1)
    {
        // Loop through LEDs 12 to 15
        for(i = 1; i < 5; i++)
        {
            // Set LED i (12 to 15) ON
            GPIOD->BSRR |= (1 << (i + 11));

            // Call delay function
            delay();

            // Set LED i OFF
            GPIOD->BSRR |= (1 << (i + 27));

            // Call delay function
            delay();
        }
    }
}

// Function to create delay
void delay(void)
{
	// Declare volatile variable to prevent optimization
    volatile int delay = 0;

    // Loop for delay
    for(delay = 0; delay < 100000; delay++);
}
