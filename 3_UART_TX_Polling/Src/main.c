/*

 Author            : Amrita N S
 Date              : 22-04-2024
 Development board : STM32F407VGT6 Discovery Board
 IDE               : STM32CubeIDE

Program to transmit single character and string using UART2 in polling mode.

*Enable clock for GPIOA using RCC_AHB1ENR_GPIOAEN bit in RCC->AHB1ENR.

*Configure PA2 for USART TX by setting the appropriate bits in GPIOA->MODER and GPIOA->AFR[0].

*Enable clock for USART2 using RCC_APB1ENR_USART2EN bit in RCC->APB1ENR.

*Set baud rate to 9600 by writing to USART2->BRR.

*Enable transmitter (TE) and USART (UE) using USART_CR1_TE and USART_CR1_UE bits in USART2->CR1.

*Configure word length and stop bits using bits in USART2->CR1 and USART2->CR2.

*Wait for transmit data register empty flag (USART_SR_TXE) in USART2->SR.

*Write data to transmit buffer by writing to USART2->DR.

*Transmit each character of the string.

*Wait for transmit data register empty flag (USART_SR_TXE) before each transmission in USART2->SR.

*Implement a delay using a simple loop.

 */


#include "stm32f407xx.h"

// Function to initialize UART2 TX pin
void uart2_tx_init(void);

// Function to configure UART2 module
void uart(void);

// Function to transmit a single character over UART
void data_write(char);

// Function to transmit a string over UART
void string_write(char *);

// Function to provide delay
void delay(void);

int main(void)
{
    uart2_tx_init();
    uart();

    while(1)
    {
    	// Transmit character 'A'
        data_write('A');
        data_write('\r'); // Transmit carriage return
        data_write('\n'); // Transmit newline
        delay();
        // Transmit string
        string_write("UART communication");
        delay();
    }
}

// Function to initialize UART2 TX pin
void uart2_tx_init(void)
{
    // Enable clock access to GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set PA2 mode to alternate function mode
    GPIOA->MODER |= GPIO_MODER_MODE2_1;
    GPIOA->MODER &= ~GPIO_MODER_MODE2_0;

    // Set PA2 alternate function type to USART_TX
    GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_2 | GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_0;
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2_3;
}

// Function to configure UART2 module
void uart(void)
{
    // Enable clock access to USART2
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Set UART baud rate to 9600
    USART2->BRR = 0x0683;

    //Enable the  Transmitter by set TE bit in USART_CR1 register.
    USART2->CR1 |= USART_CR1_TE;

    //Enable the USART by set UE bit in USART_CR1 register.
    USART2->CR1 |= USART_CR1_UE;

    // Define the word length by M bit in USART_CR1
    //M=0 : 1 Start bit, 8 Data bits, n Stop bit
    USART2->CR1 &= ~USART_CR1_M;

    //Define number of stop bits in USART_CR2
    //Bits 13:12 STOP: STOP bits
    //00: 1 Stop bit
    USART2->CR2 &= ~USART_CR2_STOP_0;
    USART2->CR2 &= ~USART_CR2_STOP_1;
}

// Function to transmit a single character over UART
void data_write(char data)
{
	// Wait until transmit data register is empty
    while(!(USART2->SR & USART_SR_TXE)){}
    {
    	// Transmit data
        USART2->DR = data;
    }
}

// Function to transmit a string over UART
void string_write(char *ptr)
{
    while(*ptr != '\0')
    {
    	// Wait until transmit data register is empty
        while(!(USART2->SR & USART_SR_TXE)){}
        {
        	// Transmit character by character
            USART2->DR = *ptr++;
        }
    }
}
// Function to provide delay
void delay(void)
{
    int i = 0;
    for (i = 0; i < 500000; i++);
}
