#include "delay_us.h"

void delay_us(uint16_t us){

	// start the timer 11

	// make a delay

	//HAL_TIM_Base_Start(&htim11);
	__HAL_TIM_SET_COUNTER(&htim11,0);
	while((__HAL_TIM_GET_COUNTER(&htim11)) < us );
	//HAL_TIM_Base_Stop(&htim11);

}


