#include "main.h"
#include "i2c.h"

#ifndef __MYOLED_H__
#define __MYOLED_H__

void MY_OLED_Command(uint8_t Command);
void MY_OLED_CommandM(uint8_t Command[], int Num);
void MY_OLED_Data(uint8_t Data);
void MY_OLED_DataM(uint8_t Data[], int Num);
void MY_OLED_SetCursor(uint8_t x, uint8_t y);
void MY_OLED_Full(uint8_t data);
void MY_OLED_ShowP(uint8_t data[], int _Long, int _Hight, int _X, int _Y);
void MY_OLED_Clear(void);
void MY_OLED_Init(void);

extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_Chinese1[][32];
extern const uint8_t OLED_Genshin[];

#endif
