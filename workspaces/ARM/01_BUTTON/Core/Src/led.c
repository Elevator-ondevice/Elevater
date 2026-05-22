
#include "led.h"

typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t        pinNumber;
    GPIO_PinState   onState;
    GPIO_PinState   offState;
}LED_CONTROL;


LED_CONTROL led[8] = {
        {GPIOB, GPIO_PIN_3, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_4, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_10, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, GPIO_PIN_8, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, GPIO_PIN_9, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOC, GPIO_PIN_7, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOB, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET}
};

void ledOn(uint8_t num)
{
    for(uint8_t i = 0; i < num; i++)
    {
        HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
    }
}

void ledOff(uint8_t num)
{
    for(uint8_t i = 0; i < num; i++)
    {
        HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
    }
}

void ledinit(void){
    for (uint8_t i = 0; i <8; i ++){
            HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
        }
}
//void ledOn(uint8_t i){
//        HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].onState);
//
//}
//
//void ledOff(uint8_t i){
//        HAL_GPIO_WritePin(led[i].port, led[i].pinNumber, led[i].offState);
//
//}

void ledShift(uint8_t num){
    for (uint8_t i = 0; i <num; i++){
        ledOn(i);
        HAL_Delay(100);
        ledOff(i);
    }
}
void led_rev_Shift(uint8_t num){
    for (uint8_t i = num; i >0; i--){
        ledOn(i);
        HAL_Delay(100);
        ledOff(i);
    }
}
