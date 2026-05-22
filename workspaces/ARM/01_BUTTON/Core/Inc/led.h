#ifndef INC_LED_H_
#define INC_LED_H_


//#include "main.h"
#include "stm32f4xx_hal.h"
void ledOn(uint8_t num);
void ledOff(uint8_t num);
void ledShift(uint8_t num);
void ledinit(void);
void led_rev_Shift(uint8_t num);

/*
 * 함수를 줄줄히 만들어서 넣으면 됨
 */



#endif /* INC_LED_H_ */
