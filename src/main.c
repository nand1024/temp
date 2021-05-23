/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
#define NUM_OF_LEDS 16

uint16_t pwmH_High = 22;
uint16_t pwmH_Low = 19;

uint16_t pwmL_High = 11;
uint16_t pwmL_Low = 26;

uint16_t pwmH_period = 22 + 19;
uint16_t pwmL_period = 11 + 26;

uint8_t data_send;


struct {
	uint8_t green;
	uint8_t red;
	uint8_t blue;
}neoPixel[NUM_OF_LEDS]={0};

void init_rcc()
{
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR&RCC_CR_HSERDY));
	RCC->CFGR|=RCC_CFGR_PLLMULL4;
	RCC->CFGR|=RCC_CFGR_PLLSRC;
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR&RCC_CR_PLLRDY));
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR&RCC_CFGR_SWS_PLL));
}

void init_gpio()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL |= GPIO_CRL_MODE6;
	GPIOA->CRL &= ~GPIO_CRL_CNF6_Msk;
	GPIOA->CRL |= GPIO_CRL_CNF6_1;

	GPIOA->CRL |= GPIO_CRL_MODE5_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF5_Msk;
}

void init_timer_pwm()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->CR1 |= (TIM_CR1_ARPE | TIM_CR1_CEN);
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M;
	TIM3->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC1P);
	TIM3->CCR1 = 0;
	TIM3->PSC = 1;
	TIM3->ARR = 41;

	NVIC_EnableIRQ(TIM3_IRQn);
}

void setPwm(uint8_t val){
	TIM3->ARR = val ? pwmH_period : pwmL_period;
	TIM3->CCR1 = val ? pwmH_High : pwmL_High;
}

int main(void)
{
	init_rcc();
	init_gpio();
	init_timer_pwm();
	neoPixel[0].red = 0;
	neoPixel[1].green = 0;
	neoPixel[2].blue = 0;
	for(;;){

	}
}

void TIM3_IRQHandler(){
	static uint8_t x = 23;
	static uint8_t switcher = 1;
	static uint8_t rgb_select = 0;
	static uint8_t ind = 0;
	if(TIM3->SR & TIM_SR_UIF){
		TIM3->SR &= ~TIM_SR_UIF;
		/*
		if(x == 0){
			switch(rgb_select){
			case 0:
				data_send = neoPixel[0].green;
				rgb_select = 1;
				break;
			case 1:
				data_send = neoPixel[0].red;
				rgb_select = 2;
				break;
			case 2:
				data_send = neoPixel[0].blue;
				rgb_select = 0;
				if(++ind >= 4){
					ind=0;
					TIM3->CCR1 = 0;
					for(volatile uint32_t x = 0; x < 90; x++);
				}
				break;
			}
			x = 7;
		}else{
			x--;
		}
		*/
		if(switcher){
			setPwm(65536 & (((uint32_t)1) << x));
		}else{
			setPwm(0);
		}
		if(x == 0){
			if(switcher == 1){
				switcher = 0;
				x =100;
			}else{
				switcher = 1;
				x = 23;
			}
		}else{
			x--;
		}
	}
}
