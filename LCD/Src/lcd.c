//
// Created by 李旭 on 2026/4/5.
//
#include "lcd.h"

void LCD_WriteReg(uint16_t regval) { LCD->LCD_REG = regval; }
void LCD_WriteData(uint16_t data) { LCD->LCD_RAM = data; }


void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height) {
    uint16_t ex = sx + width - 1;
    uint16_t ey = sy + height - 1;

    LCD_WriteReg(0x2A);
    LCD_WriteData(sx >> 8); LCD_WriteData(sx & 0XFF);
    LCD_WriteData(ex >> 8); LCD_WriteData(ex & 0XFF);

    LCD_WriteReg(0x2B);
    LCD_WriteData(sy >> 8); LCD_WriteData(sy & 0XFF);
    LCD_WriteData(ey >> 8); LCD_WriteData(ey & 0XFF);

    LCD_WriteReg(0x2C);
}

void LCD_Init(void) {
    // 复位后的初始化序列
    HAL_Delay(50);
    LCD_WriteReg(0xCF); LCD_WriteData(0x00); LCD_WriteData(0xC1); LCD_WriteData(0X30);
    LCD_WriteReg(0xED); LCD_WriteData(0x64); LCD_WriteData(0x03); LCD_WriteData(0X12); LCD_WriteData(0X81);
    LCD_WriteReg(0xE8); LCD_WriteData(0x85); LCD_WriteData(0x10); LCD_WriteData(0X78);
    LCD_WriteReg(0xCB); LCD_WriteData(0x39); LCD_WriteData(0x2C); LCD_WriteData(0X00); LCD_WriteData(0X34); LCD_WriteData(0X02);
    LCD_WriteReg(0xF7); LCD_WriteData(0x20);
    LCD_WriteReg(0xEA); LCD_WriteData(0x00); LCD_WriteData(0x00);

    LCD_WriteReg(0xC0); LCD_WriteData(0x23);
    LCD_WriteReg(0xC1); LCD_WriteData(0x10);
    LCD_WriteReg(0xC5); LCD_WriteData(0x3E); LCD_WriteData(0x28);
    LCD_WriteReg(0xC7); LCD_WriteData(0x86);

    LCD_WriteReg(0x36); LCD_WriteData(0x48);
    LCD_WriteReg(0x3A); LCD_WriteData(0x55);

    LCD_WriteReg(0xB1); LCD_WriteData(0x00); LCD_WriteData(0x18);
    LCD_WriteReg(0xB6); LCD_WriteData(0x08); LCD_WriteData(0x82); LCD_WriteData(0x27);

    LCD_WriteReg(0x11);
    HAL_Delay(120);
    LCD_WriteReg(0x29);
}

void LCD_Clear(uint16_t color) {
    uint32_t total = LCD_WIDTH * LCD_HEIGHT;
    LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
    while(total--) {
        LCD->LCD_RAM = color;
    }
}




