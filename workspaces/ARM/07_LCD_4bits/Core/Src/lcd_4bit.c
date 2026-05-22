#include "lcd_4bit.h"



// 4비트 데이터를 출력 -> 상위 4비트
void LCD_Data4bit(uint8_t data)     // 0b 0011 1100
{
    HAL_GPIO_WritePin(LCD_D4_GPIO, LCD_D4_PIN, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D5_GPIO, LCD_D5_PIN, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D6_GPIO, LCD_D6_PIN, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7_PIN, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// LCD Enable핀 신호 출력
void LCD_EnablePin(void)
{
    // Enable Low
    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    // Enable High
    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    // Enable High -> Low 이때..데이터가 LCD로 전달됨
    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
    HAL_Delay(2);
}




// 1바이트를 상/하위로 나눠서 전송 -> 신규로 함수 만들었고
void LCD_SentByte(uint8_t data)
{
    // 상위 4비트 전송
    LCD_Data4bit(data & 0xF0);
    LCD_EnablePin();

    // 하위 4비트 전송
    LCD_Data4bit((data << 4) & 0xF0);
    LCD_EnablePin();
}



// LCD 명령어 전송
void LCD_WriteCommand(uint8_t commandData)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_RESET);     // RS = 0 -> 명령어 모드

    LCD_SentByte(commandData);
}

// LCD 문자전송
void LCD_WriteData(uint8_t charData)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_SET);       // RS = 1 -> 데이터 모드

    LCD_SentByte(charData);
}

// 커서 이동함수 (row : 0~1 / col : 0~15)
void LCD_GotoXY(uint8_t row, uint8_t col)
{
//    col %= 16;
//    row %= 2;
//
//    uint8_t addr = (0x40 * row) + col;
//    uint8_t command = 0x80 + addr;
//    LCD_WriteCommand(command);

    // row 범위 제한(0 또는 1)
    if(row > 1) row = 1;
    // col 범위 제한(0 ~ 15)
    if(col > 15) col = 15;

    uint8_t addr = (row == 0) ? col : (0x40 + col);
    // 커서 이동
    LCD_WriteCommand(0x80 | addr);
}

// 문자열 출력 함수
void LCD_WriteString(char *string)
{
    while(*string)
    {
        LCD_WriteData(*string++);
    }
}

// 좌표 이동후에 문자열 출력
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
    LCD_GotoXY(row, col);
    LCD_WriteString(string);
}

// LCD 초기화 함수
void LCD_Init()
{
    HAL_Delay(50);

    LCD_Data4bit(0x03);
    LCD_EnablePin();
    HAL_Delay(5);

    LCD_Data4bit(0x03);
    LCD_EnablePin();
    HAL_Delay(1);

    LCD_Data4bit(0x03);
    LCD_EnablePin();

    LCD_Data4bit(0x02);
    LCD_EnablePin();

    LCD_WriteCommand(0x28);

    LCD_WriteCommand(0x0C);

    LCD_WriteCommand(0x01);
    HAL_Delay(5); // 명령어 미는 과정에서 타이밍 마춰주는 과정
    LCD_WriteCommand(0x06);
}
