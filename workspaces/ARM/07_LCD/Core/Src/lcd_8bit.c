#include "lcd_8bit.h"

// 8비트 데이터를 출력
void LCD_Data(uint8_t data)     // 0b 0011 1100
{
    HAL_GPIO_WritePin(LCD_D0_GPIO, LCD_D0_PIN, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D1_GPIO, LCD_D1_PIN, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D2_GPIO, LCD_D2_PIN, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D3_GPIO, LCD_D3_PIN, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
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
    // Enable high
    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    // Enable high -> Low 이때.. 데이터가 LCD로 전달됨
    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
    HAL_Delay(2);
}

// LCD 명령어 전송
void LCD_WriteCommand(uint8_t commandData)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_RESET);     // RS = 0 -> 명령어 모드
    LCD_Data(commandData);                                          // LCD에 명령어 전송
    LCD_EnablePin();                                                // Enable로 명령어 확정
}

// LCD 문자전송
void LCD_WriteData(uint8_t charData)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_SET);       // RS = 1 -> 데이터 모드
    LCD_Data(charData);                                             // LCD에 명령어 전송
    LCD_EnablePin();                                                // Enable로 데이터 확정
}

// 커서 이동함수 (row : 0~1 / col : 0~15)
void LCD_GotoXY(uint8_t row, uint8_t col)
{
    // row 범위 제한 (0 또는 1)
    if(row > 1) row = 1;
    // col 범위 제한 ( 0 ~ 15)
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

// LCD 초기화 함수 ( datasheet 보고 찾아서 해야함 )
void LCD_Init()
{
    HAL_Delay(50);

    LCD_WriteCommand(0x38);
    HAL_Delay(5);
    LCD_WriteCommand(0x38);
    HAL_Delay(5);
    LCD_WriteCommand(0x38);

    LCD_WriteCommand(0x38);
    LCD_WriteCommand(0x0C);
    LCD_WriteCommand(0x01);
    LCD_WriteCommand(0x06);
}


//#include "lcd_8bit.h"
//
//// 8비트 데이터를 출력
//void LCD_Data(uint8_t data)     // 0b 0011 1100
//{
//    HAL_GPIO_WritePin(LCD_D0_GPIO, LCD_D0_PIN, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D1_GPIO, LCD_D1_PIN, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D2_GPIO, LCD_D2_PIN, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D3_GPIO, LCD_D3_PIN, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D4_GPIO, LCD_D4_PIN, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D5_GPIO, LCD_D5_PIN, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D6_GPIO, LCD_D6_PIN, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7_PIN, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//}
//
//// LCD Enable핀 신호 출력
//void LCD_EnablePin(void)
//{
//    // Enable Low
//    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
//    HAL_Delay(1);
//    // Enable High
//    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_SET);
//    HAL_Delay(1);
//    // Enable High -> Low 이때..데이터가 LCD로 전달됨
//    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
//    HAL_Delay(2);
//}
//
//// LCD 명령어 전송
//void LCD_WriteCommand(uint8_t commandData)
//{
//    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_RESET);     // RS = 0 -> 명령어 모드
//    LCD_Data(commandData);                                          // LCD에 명령어 전송
//    LCD_EnablePin();                                                // Enable로 명령어 확정
//}
//
//// LCD 문자전송
//void LCD_WriteData(uint8_t charData)
//{
//    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_SET);       // RS = 1 -> 데이터 모드
//    LCD_Data(charData);                                             // LCD에 명령어 전송
//    LCD_EnablePin();                                                // Enable로 데이터 확정
//}
//
//// 커서 이동함수 (row : 0~1 / col : 0~15)
//void LCD_GotoXY(uint8_t row, uint8_t col)
//{
////    col %= 16;
////    row %= 2;
////
////    uint8_t addr = (0x40 * row) + col;
////    uint8_t command = 0x80 + addr;
////    LCD_WriteCommand(command);
//
//    // row 범위 제한(0 또는 1)
//    if(row > 1) row = 1;
//    // col 범위 제한(0 ~ 15)
//    if(col > 15) col = 15;
//
//    uint8_t addr = (row == 0) ? col : (0x40 + col);
//    // 커서 이동
//    LCD_WriteCommand(0x80 | addr);
//}
//
//// 문자열 출력 함수
//void LCD_WriteString(char *string)
//{
//    while(*string)
//    {
//        LCD_WriteData(*string++);
//    }
//}
//
//// 좌표 이동후에 문자열 출력
//void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
//{
//    LCD_GotoXY(row, col);
//    LCD_WriteString(string);
//}
//
//// LCD 초기화 함수
//void LCD_Init()
//{
//    HAL_Delay(50);
//
//    LCD_WriteCommand(0x38);
//    HAL_Delay(5);
//    LCD_WriteCommand(0x38);
//    HAL_Delay(5);
//    LCD_WriteCommand(0x38);
//
//    LCD_WriteCommand(0x38);
//    LCD_WriteCommand(0x0C);
//    LCD_WriteCommand(0x01);
//
//    LCD_WriteCommand(0x06);
//}
//
//
//
//
//
//
//
//
//
//
////#include "lcd_8bit.h"
////
////// 8bit data out  0b 0011 1100
////void LCD_data(uint8_t data){
////    HAL_GPIO_WritePin(LCD_D0_GPIO, LCD_D0_PIN, (data & 0x01)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D1_GPIO, LCD_D1_PIN, (data & 0x02)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D2_GPIO, LCD_D2_PIN, (data & 0x04)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D3_GPIO, LCD_D3_PIN, (data & 0x08)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D4_GPIO, LCD_D4_PIN, (data & 0x10)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D5_GPIO, LCD_D5_PIN, (data & 0x20)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D6_GPIO, LCD_D6_PIN, (data & 0x40)? GPIO_PIN_SET : GPIO_PIN_RESET);
////    HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7_PIN, (data & 0x80)? GPIO_PIN_SET : GPIO_PIN_RESET);
////}
////
////// LCD enable pin
////void LCD_EnablePin(void){
////    //Enable low
////    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
////    HAL_Delay(1);
////    // Enable high
////    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_SET);
////    HAL_Delay(1);
////    // Enable high -> low , data send to lcd
////    HAL_GPIO_WritePin(LCD_E_GPIO, LCD_E_PIN, GPIO_PIN_RESET);
////    HAL_Delay(2);
////}
////
////// LCD instruction send
////void LCD_WriteCommand(uint8_t commandData){
////    // instruction mode
////    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_RESET);
////    LCD_data(commandData); // put the command data in LCD_data function
////    LCD_EnablePin();     // Enable for confirming instruction
////}
////
////// LCD string send
////void LCD_WriteData(uint8_t charData){
////    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS_PIN, GPIO_PIN_SET);
////        LCD_data(charData); // put the command data in LCD
////        LCD_EnablePin(); //Enable for confirming instruction
////}
////
////// LCD Cursor moving
////// row : 0~ 1 / col : 0~15
////void LCD_GotoXT( uint8_t row, uint8_t col){
//////    col  %= 16;
//////    row % = 2;
//////
//////    uint8_t addr = (0x40 | row )+ col;
//////    uint8_t command = 0x90 + addr;
//////    LCD_WriteCommand( 0x80|addr);
////    // == same
////
////      //imit row count
////    if(row  > 1 ){
////        row  = 1;
////    }
////    //limit col count
////    if(col  > 15){
////        col =  15;
////    }
////
////    uint8_t addr = (row == 0)  ? col   : (0x40 + col) ;
////    // move the cursor
////    LCD_WriteCommand( 0x80|addr);
////
////}
////
//////LCD string out
////void LCD_WriteString(char * string){
////
////    while(*string){
////        LCD_WriteData(*string++);// 배열의 끝인 null로 가면 끝
////    }
////}
////
////// moved and string out
////void LCD_WriteStringXY(uint8_t row, uint8_t col, char * string){
////
////    LCD_GotoXT(row, col);
////    LCD_WriteString(string);
////}
////
////// init
////void LCD_init(void){
////    HAL_Delay(500);
////
////    LCD_WriteCommand(0x38);
////    HAL_Delay(5);
////    LCD_WriteCommand(0x38);
////    HAL_Delay(5);
////    LCD_WriteCommand(0x38);
////
////    LCD_WriteCommand(0x38);
////    LCD_WriteCommand(0x0C);
////    LCD_WriteCommand(0x01);
////
////    LCD_WriteCommand(0x06);
////
////}
////
