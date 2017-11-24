
#include "timer.h"


void TIM17_IRQHandler(void){	//CAN

	static uint8_t can_cnt;
	uint8_t tmp, i, out;

	TIM17->SR &= ~TIM_SR_UIF;	//сброс флага

	IWDG_ReloadCounter();

//анализ CAN
	can_cnt++;
	if (can_cnt == 9) { //интервал 1,27 с
		can_cnt = 0;
		if (can_on == 0) { //CAN сообщений не было
			GPIOA->ODR ^= 0x400;
		}
		can_on = 0;
	}
}


void Init_Timer(){

	//таймер CAN
	TIM17->PSC = 239;
	TIM17->ARR = 16000;		//период 160 мс
	TIM17->DIER |= TIM_DIER_UIE;
	TIM17->CR1 |= TIM_CR1_CEN;


	//вектор
	NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

