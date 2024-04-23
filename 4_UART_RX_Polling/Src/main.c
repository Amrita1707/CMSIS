/*

 Author            : Amrita N S
 Date              : 23-04-2024
 Development board : STM32F407VGT6 Discovery Board
 IDE               : STM32CubeIDE

Program to transmit single character and string using UART2 in polling mode.

*Enable clock for GPIOA using RCC_AHB1ENR_GPIOAEN bit in RCC->AHB1ENR.

*Configure PA2 for USART TX by setting the appropriate bits in GPIOA->MODER and GPIOA->AFR[0].

 *Configure PA3 for USART RX by setting the appropriate bits in GPIOA->MODER and GPIOA->AFR[0].

*Enable clock for USART2 using RCC_APB1ENR_USART2EN bit in RCC->APB1ENR.

*Set baud rate to 9600 by writing to USART2->BRR.

*Enable transmitter (TE) and USART (UE) using USART_CR1_TE and USART_CR1_UE bits in USART2->CR1.

*Enable Receiver (RE) using USART_CR1_RE bit in USART2->CR1.

*Configure word length and stop bits using bits in USART2->CR1 and USART2->CR2.

*Wait for transmit data register empty flag (USART_SR_TXE) in USART2->SR.

*Wait for receive data register empty flag (USART_SR_RXNE) in USART2->SR.

*Write data to transmit buffer by writing to USART2->DR.

*Receive data from USART2->DR.

 */


#include "stm32f407xx.h"

// Function to initialize UART2 TX pin
void uart2_tx_init(void);

void uart2_rx_init(void);
// Function to configure UART2 module
void uart(void);

// Function to transmit a single character over UART
void data_write(char);

// Function to receive character over UART
char data_read();

// Function to transmit a string over UART
void string_write(char *);

int main(void)
{
	char ch;
    uart2_tx_init();
    uart();
    uart2_rx_init();
    while(1)
    {
    	ch = data_read();
    	data_write(ch);
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

void uart2_rx_init(void)
{
	 //Enable the Receiver by set RE bit in USART_CR1 register.
	  USART2->CR1 |= USART_CR1_RE;

	  // Set PA3 mode to alternate function mode
	  GPIOA->MODER |=  GPIO_MODER_MODE3_1;
	  GPIOA->MODER &= ~GPIO_MODER_MODE3_0;

	  // Set PA3 alternate function type to USART_RX
	  GPIOA->AFR[0] |= GPIO_AFRL_AFRL3_2 | GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_0;
	  GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL3_3;
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

// Function to receive data
char data_read()
{
	while(!(USART2->SR & USART_SR_RXNE)){}
	        {
	        	//Receive data
	            return USART2->DR;
	        }
}
