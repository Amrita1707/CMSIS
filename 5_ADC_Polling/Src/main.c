/*
 Author            : Amrita N S
 Date              : 03-04-2024
 Development board : STM32F407VGT6 Discovery Board
 IDE               : STM32CubeIDE

 Interfacing a Potentiometer with an ADC

 1. Activate the ADC clock by setting the corresponding bit in the RCC_APB2ENR register.

 2. Configure the ADC for right alignment of results (ALIGN) and continuous conversion mode (CONT) using the ADC_CR2 register.

 3. Utilize the ADC_CR1 register to set the desired resolution and select the analog input channel.

 4. Configure the input pin for the analog input channel using the GPIOx_MODER register.

 5. Enable the ADC and initiate the conversion process by setting the appropriate bits in the ADC_CR2 register (ADON and SWSTART).

 6. Continuously monitor the end-of-conversion (EOC) flag in the ADC_SR register.

 7. Upon detection of the EOC flag being set, retrieve the ADC data result from the ADC_DR register and store it.

 8. Repeat steps 6 and 7 for subsequent conversions.


*/

#include "stm32f407xx.h"

// Function prototypes
void adc_init(void);
void gpio_config(void);

// Global variable to store ADC conversion result
unsigned int result;

int main(void)
{
    // Initialize ADC and GPIO
    adc_init();
    gpio_config();

    // Infinite loop for continuous ADC conversion
    while(1)
    {
        // Start the conversion
        ADC1->CR2 |= ADC_CR2_SWSTART;

        // Wait until conversion is complete
        while(!(ADC1->SR & ADC_SR_EOC)){}

        // Read the conversion result
        result = ADC1->DR;
    }
}

void gpio_config()
{
    // Enable the clock access to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA0 pin as analog mode
    GPIOA->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1;
}

void adc_init(void)
{
    // Enable the clock access to ADC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Select the resolution of conversion
    //00: 12-bit (15 ADCCLK cycles)
    ADC1->CR1 &= ~ADC_CR1_RES_0 & ~ADC_CR1_RES_1 ;

    // Set alignment to right (result in DR register)
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    // Enable continuous conversion mode
    ADC1->CR2 |= ADC_CR2_CONT;

    // Enable ADC
    ADC1->CR2 |= ADC_CR2_ADON;
}
