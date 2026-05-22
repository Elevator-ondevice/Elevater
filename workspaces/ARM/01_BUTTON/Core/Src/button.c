#include "button.h"

//pull up이라 onState = 0;
BUTTON_CONTROL button[3] = {
            {GPIOC, GPIO_PIN_9, 0},
            {GPIOB, GPIO_PIN_8, 0},
            {GPIOB, GPIO_PIN_9, 0}
};


bool buttonGetPressed(uint8_t num){

        bool ret = false;

        if (HAL_GPIO_ReadPin(button[num].port,  button[num].pinNumber) == button[num].onState){

            HAL_Delay(10); // debounce
            if (HAL_GPIO_ReadPin(button[num].port,  button[num].pinNumber) == button[num].onState){

                       ret = true;

                   }
        }
       return ret;
}
