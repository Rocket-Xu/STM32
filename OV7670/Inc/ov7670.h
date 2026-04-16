//
// Created by 李旭 on 2026/4/5.
//

#ifndef CAMERA_OV7670_H
#define CAMERA_OV7670_H
#include "main.h"
#include "lcd.h"

#define SCCB_SCL_H()    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define SCCB_SCL_L()    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
#define SCCB_SDA_H()    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET)
#define SCCB_SDA_L()    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET)
#define SCCB_SDA_READ() HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_13)
#define READ_D0_D7()    (GPIOC->IDR & 0xFF)       // D0~D7 -> PC0~PC7
#define READ_PCLK()     ((GPIOB->IDR & GPIO_PIN_4) != 0) // PCLK -> PB4
#define READ_HREF()     ((GPIOB->IDR & GPIO_PIN_3) != 0) // HREF -> PB3
#define READ_VSYNC()    ((GPIOA->IDR & GPIO_PIN_8) != 0) // VSYNC -> PA8
#define LCD_RAM         LCD->LCD_RAM

uint8_t OV7670_Init(void);
void OV7670_Capture_To_LCD(void);
uint8_t SCCB_WriteByte(uint16_t reg, uint8_t data);
uint8_t SCCB_ReadByte(uint16_t reg, uint8_t *data);
void OV7670_Capture_Safe(void);
void OV7670_Capture_Slow(void);
#endif