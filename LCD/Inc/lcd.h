//
// Created by 李旭 on 2026/4/5.
//

#ifndef CAMERA_LCD_H
#define CAMERA_LCD_H
#include "main.h"

typedef struct {
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//窗口尺寸
#define LCD_WIDTH   240
#define LCD_HEIGHT  320

void LCD_Init(void);
void LCD_Clear(uint16_t color);
void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);
void LCD_WriteRAM_Prepare(void);
void LCD_Test_Run(void);

#define LCD_DMA_MEM_ADDR   ((uint32_t)&LCD->LCD_RAM)  // LCD数据地址
#define LCD_WIDTH_MAX      240
#define LCD_LINE_BUF_SIZE  LCD_WIDTH_MAX               // 一行像素数

// 函数声明
void LCD_DMA_Send_Line(uint16_t *line_buf, uint16_t line_len);
void LCD_DMA_Fill_Color(uint16_t color, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);
#endif //CAMERA_LCD_H
