
#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "delay_us.h"


#define	DHT11_GPIO_PORT		GPIOC
#define DHT11_GPIO_PIN		GPIO_PIN_4

#define DHT11_INPUT_GPIO_PORT	GPIOA
#define DHT11_INPUT_GPIO_PIN	GPIO_PIN_7


enum {
	INPUT,
	OUTPUT
};

typedef struct {

	GPIO_TypeDef	*port;
	uint16_t		pin;
	uint8_t			temperature;
	uint8_t			humidity;
}DHT11;


void dht11_Init(DHT11 *dht, GPIO_TypeDef *port, uint16_t pin);
void dht11_Gpio_mode(DHT11 *dht, uint8_t mode);
uint8_t dht11_read(DHT11 *dht);

#endif /* INC_DHT11_H_ */
