#ifndef INC_LCD_4BIT_H_
#define INC_LCD_4BIT_H_


#include "main.h"

// RS핀 설정
#define LCD_RS_GPIO     GPIOA
#define LCD_RS_PIN      GPIO_PIN_5

// E핀 설정
#define LCD_E_GPIO      GPIOA
#define LCD_E_PIN       GPIO_PIN_7

// DATA 핀 설정
#define LCD_D4_GPIO     GPIOB
#define LCD_D4_PIN      GPIO_PIN_12
#define LCD_D5_GPIO     GPIOB
#define LCD_D5_PIN      GPIO_PIN_13
#define LCD_D6_GPIO     GPIOB
#define LCD_D6_PIN      GPIO_PIN_14
#define LCD_D7_GPIO     GPIOB             // MSB
#define LCD_D7_PIN      GPIO_PIN_15


// 4비트 데이터를 출력 -> 조금 수정
void LCD_Data4bit(uint8_t data);

// LCD Enable핀 신호 출력
void LCD_EnablePin(void);


// 1바이트를 상/하위로 나눠서 전송 -> 신규로 함수 만들었고
void LCD_SentByte(uint8_t data);


// LCD 명령어 전송
void LCD_WriteCommand(uint8_t commandData);

// LCD 문자전송
void LCD_WriteData(uint8_t charData);

// 커서 이동함수 (row : 0~1 / col : 0~15)
void LCD_GotoXY(uint8_t row, uint8_t col);

// 문자열 출력 함수
void LCD_WriteString(char *string);

// 좌표 이동후에 문자열 출력
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);

// LCD 초기화 함수
void LCD_Init();


#endif /* INC_LCD_4BIT_H_ */
