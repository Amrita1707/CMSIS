/*



*/

#include "stm32f407xx.h"
void clk_config();
void gpio_config();
void TIM6_delay_us(uint16_t);
void TIM6_delay_ms(uint16_t);

int main()
{
	clk_config();
	gpio_config();


	 while (1)
	    {
	        // Generate 16us delay
	        GPIOA->ODR |= GPIO_ODR_OD5; // Set PA5 high
	        TIM6_delay_us(16);

	        GPIOA->ODR &= ~GPIO_ODR_OD5; // Set PA5 low

	        // Generate 20ms delay
	        TIM6_delay_ms(20);

	        // Generate 80us delay
	        GPIOA->ODR |= GPIO_ODR_OD5; // Set PA5 high
	        TIM6_delay_us(80);
	        GPIOA->ODR &= ~GPIO_ODR_OD5; // Set PA5 low
	    }

}

void clk_config()
{
	// Enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// TIM7 clock enabled
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

}

void gpio_config()
{
	// set mode bits for GPIOA as output
	GPIOA->MODER |= GPIO_MODER_MODE0_0;
	GPIOA->MODER |= GPIO_MODER_MODE0_1;
}

void TIM6_delay_us(uint16_t us)
{
    // Enable TIM6 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    // Reset TIM6
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM6RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;

    // Set the prescaler value
    TIM6->PSC = 16000000 / 1000000 - 1; // Prescaler for 1us

    // Calculate the ARR value
    TIM6->ARR = us;

    // Enable the counter
    TIM6->CR1 |= TIM_CR1_CEN;

    // Wait until the counter reaches the ARR value
    while (!(TIM6->SR & TIM_SR_UIF))
        ;

    // Reset the update event flag
    TIM6->SR &= ~TIM_SR_UIF;
}

void TIM6_delay_ms(uint16_t ms)
{
    // Enable TIM6 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    // Reset TIM6
    RCC->APB1RSTR |= RCC_APB1RSTR_TIM6RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;

    // Set the prescaler value
    TIM6->PSC = 16000000 / 1000 - 1; // Prescaler for 1ms

    // Calculate the ARR value
    TIM6->ARR = ms;

    // Enable the counter
    TIM6->CR1 |= TIM_CR1_CEN;

    // Wait until the counter reaches the ARR value
    while (!(TIM6->SR & TIM_SR_UIF))
        ;

    // Reset the update event flag
    TIM6->SR &= ~TIM_SR_UIF;
}
