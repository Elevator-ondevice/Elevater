#include "dht11.h"



void dht11_Init(DHT11 *dht, GPIO_TypeDef *port, uint16_t pin){

	dht->port	=	port;
	dht->pin	=	pin;

}
void dht11_Gpio_mode(DHT11 *dht, uint8_t mode){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// mode
	if(mode == OUTPUT){

		GPIO_InitStruct.Pin = dht->pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		HAL_GPIO_Init(dht->port, &GPIO_InitStruct);


	}

	else if(mode == INPUT){
		GPIO_InitStruct.Pin = dht->pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		HAL_GPIO_Init(dht->port, &GPIO_InitStruct);

	}

}


uint8_t dht11_read(DHT11 *dht){

	bool ret =	true; // 반환값 기본

	uint16_t timeTick = 0; // 시간측정 변수
	uint8_t pulse [40] = {0}; // 40비트 데이터를 저장할 변수

	// 온습도 변수 초기화
	uint8_t humValue1 = 0, humValue2 = 0; // 1 = 정수, 2 = 소수(실수)
	uint8_t tempValue1 = 0, tempValue2 = 0;
	uint8_t parityValue = 0;

	HAL_TIM_Base_Start(&htim11); //타이머 동작

	// 통신 신호 동작
	dht11_Gpio_mode(dht, OUTPUT); // 출력으로 설정
	HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(dht->port, dht->pin, GPIO_PIN_SET);
	delay_us(20);

	dht11_Gpio_mode(dht, INPUT);
	// 응답신호 대기
	__HAL_TIM_SET_COUNTER(&htim11,0);
	while(HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET){ // low 신호동안 대기
		if(__HAL_TIM_GET_COUNTER(&htim11) > 100){
			printf("Low Signal Timeout \r\n");
			break;
		}
	}
	__HAL_TIM_SET_COUNTER(&htim11,0); // high 시그널용
	while(HAL_GPIO_ReadPin(dht->port, dht->pin)== GPIO_PIN_SET){ // high 신호동안 대기
		if(__HAL_TIM_GET_COUNTER(&htim11) > 100){
			printf("High Signal Timeout \r\n");
			break;
		}
	}

	// 데이터 수신
	for (uint8_t i = 0; i < 40; i++){

		while(HAL_GPIO_ReadPin(dht->port, dht->pin)== GPIO_PIN_RESET){ // 50us 대기 for low

		}
		__HAL_TIM_SET_COUNTER(&htim11, 0);
		while(HAL_GPIO_ReadPin(dht->port, dht->pin)== GPIO_PIN_SET){ // 26~28us 대기 for high
			timeTick = __HAL_TIM_GET_COUNTER(&htim11);

			//신호 길이를 구별
			if(timeTick >20 && timeTick < 30){
				pulse[i] = 0;
			}
			else if(timeTick > 65 && timeTick < 85){
				pulse[i] = 1;
			}
		}
	}

	HAL_TIM_Base_Stop(&htim11); // timer stop

	// 온습도 데이터 처리

	for(uint8_t i =0; i < 8; i ++){ humValue1 = (humValue1 << 1) + pulse[i];}
	for(uint8_t i =8; i < 16; i ++){ humValue2 = (humValue2 << 1) + pulse[i];}
	for(uint8_t i =16; i <24; i ++){ tempValue1 = (tempValue1 << 1) + pulse[i];}
	for(uint8_t i =24; i <32; i ++){ tempValue2 = (tempValue2 << 1) + pulse[i];}
	for(uint8_t i =32; i <40; i ++){ parityValue = (parityValue << 1) + pulse[i];}

	// 구조체에 값 저장
	dht->temperature = tempValue1;
	dht->humidity = humValue1;

	// 데이터 무결성 검증
	uint8_t checkSum = humValue1 + humValue2 + tempValue1 + tempValue2;
	if(checkSum != parityValue){
		printf("checkSum error \r\n");
		ret = false;
	}

	return ret;
}
