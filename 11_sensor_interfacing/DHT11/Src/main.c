/*



*/

#include "stm32f407xx.h"
void clk_config();
void gpio_config();
void dht_response();
void delay(int);
//void rc_data();
int data;

int main()
{
	clk_config();
	gpio_config();
	// Set PA1 high
	GPIOA->ODR |= GPIO_ODR_OD1;

	while(1)
	{
		// Set PA1 low
		GPIOA->ODR &= ~GPIO_ODR_OD1;
		delay(18000);

		// Set PA1 high
		GPIOA->ODR |= GPIO_ODR_OD1;
		delay(40);

		dht_response();

	    if(GPIOA->IDR & 0x00){}
	    delay(54);

	    if(GPIOA->IDR & 0x10){}
	    delay(80);

	    //rc_data();
    }
}

void delay(int d)
{
	volatile int i;
	for(i=0; i<d; i++){}
}

/*void rc_data()
{

  if(GPIOA->IDR & 0x00){}
     delay(54);
			for(n=1; n<=40;)
			{
				if(GPIOA->IDR & 0x10)
				{
                   n++;
				}
				else
					n=0;
				if( n == 24)
				{
                	 data = data * 10 + 0;
                	 m=0;
				}
				else if( n > 24)
				{
                	 data = data * 10 + 1;
                	 m=0;
				}

			}

}
*/

void clk_config()
{
	// Enable clock for GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void gpio_config()
{
	// set mode bits for GPIOA as output
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}

void dht_response()
{
	//Set PA1 pin as input
	GPIOA->MODER &= ~GPIO_MODER_MODE1_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_1;
}




/*void data_rx()
{
	int i,humidity;
	for(i=0; i<15; i++)
	{
		humidity = ( humidity * 10) + ((GPIOA->IDR)>>1) ;
		TIM7_delay_us(50);
	}
}*/
