//
// Created by 李旭 on 2026/4/5.
//

#include "ov7670.h"

static void SCCB_Delay(void)
{
    uint32_t i = 2000;
    while(i--);
}

void SCCB_Start(void)
{
    SCCB_SDA_H(); SCCB_SCL_H(); SCCB_Delay();
    SCCB_SDA_L(); SCCB_Delay();
    SCCB_SCL_L();
}

void SCCB_Stop(void)
{
    SCCB_SDA_L(); SCCB_Delay();
    SCCB_SCL_H(); SCCB_Delay();
    SCCB_SDA_H(); SCCB_Delay();
}

uint8_t SCCB_Write(uint8_t data)
{
    uint8_t i, res;
    for(i = 0; i < 8; i++) {
        if(data & 0x80) SCCB_SDA_H();
        else SCCB_SDA_L();
        data <<= 1;
        SCCB_Delay();
        SCCB_SCL_H(); SCCB_Delay();
        SCCB_SCL_L();
    }
    SCCB_SDA_H(); SCCB_Delay();
    SCCB_SCL_H(); SCCB_Delay();
    res = SCCB_SDA_READ();
    SCCB_SCL_L();
    return res;
}

uint8_t SCCB_WriteByte(uint16_t reg, uint8_t data)
{
    SCCB_Start();
    if(SCCB_Write(0x42)) return 1;
    SCCB_Delay();
    if(SCCB_Write(reg)) return 2;
    SCCB_Delay();
    if(SCCB_Write(data)) return 3;
    SCCB_Stop();
    return 0;
}
void SCCB_NoAck(void)
{
    SCCB_SDA_H(); SCCB_Delay();
    SCCB_SCL_H(); SCCB_Delay();
    SCCB_SCL_L(); SCCB_Delay();
    SCCB_SDA_L(); SCCB_Delay();
}

uint8_t SCCB_ReadByte(uint16_t reg, uint8_t *data)
{
    uint8_t i;
    SCCB_Start();
    if(SCCB_Write(0x42)) return 1;
    SCCB_Delay();
    if(SCCB_Write(reg)) return 2;
    SCCB_Stop();
    SCCB_Delay();

    SCCB_Start();
    if(SCCB_Write(0x43)) return 3;
    SCCB_Delay();

    *data = 0;
    for(i=0; i<8; i++)
    {
        *data <<= 1;
        SCCB_Delay();
        SCCB_SCL_H(); SCCB_Delay();
        if(SCCB_SDA_READ()) *data |= 0x01;
        SCCB_SCL_L();
    }
    SCCB_NoAck();
    SCCB_Stop();
    return 0;
}

const uint8_t OV7670_Reg_Config[][2] =
{
	/*以下为OV7670 QVGA RGB565参数  */
	{0x3a, 0x04},//dummy
	{0x40, 0xd0},//565
	{0x12, 0x14},//QVGA,RGB输出

	//输出窗口设置
	{0x32, 0x80},//HREF control	bit[2:0] HREF start 3 LSB	 bit[5:3] HSTOP HREF end 3LSB
	{0x17, 0x16},//HSTART start high 8-bit MSB
	{0x18, 0x04},//5 HSTOP end high 8-bit
	{0x19, 0x02},
	{0x1a, 0x7b},//0x7a,
	{0x03, 0x06},//0x0a,帧竖直方向控制

	{0x0c, 0x00},
	{0x15, 0x00},//0x00
	{0x3e, 0x00},//10
	{0x70, 0x3a},
	{0x71, 0x35},
	{0x72, 0x11},
	{0x73, 0x00},//

	{0xa2, 0x02},//15
	{0x11, 0x81},//时钟分频设置,0,不分频.
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},

	{0x7d, 0x3c},//20
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},

	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},

	{0x87, 0xc4},//30
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	{0x00, 0x00},//AGC

	{0x10, 0x00},
	{0x0d, 0x00},//全窗口， 位[5:4]: 01 半窗口，10 1/4窗口，11 1/4窗口
	{0x14, 0x28},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},

	{0x24, 0x75},//40
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},

	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},

	{0xaa, 0x94},//50
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},

	{0x1e, 0x27},//图像输出镜像控制.0x07
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},

	{0x35, 0x0b},//60
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},

	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x00},
	{0x6b, 0x40},//PLL*4=48Mhz
	{0x74, 0x19},
	{0x8d, 0x4f},

	{0x8e, 0x00},//70
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66

	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},

	{0xb3, 0x82},//80
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},

	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},

	{0x5b, 0x44},//90
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},

	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},


	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},

	//{0x54, 0x40},//110


	{0x09, 0x03},//驱动能力最大

	{0x6e, 0x11},//100
	{0x6f, 0x9f},//0x9e for advance AWB
	{0x55, 0x00},//亮度
	{0x56, 0x40},//对比度 0x40
	{0x57, 0x40},//0x40,  change according to Jim's request

};

uint8_t OV7670_Init(void) {
    uint8_t i = 0, res = 0, cam_id = 0;
    HAL_Delay(50);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    res = SCCB_ReadByte(0x0A, &cam_id);
    if(res != 0 || cam_id != 0x76) {
        return 1;
    }

    SCCB_WriteByte(0x12, 0x80);
    HAL_Delay(10);

    while(OV7670_Reg_Config[i][0] != 0xFF) {
        res = SCCB_WriteByte(OV7670_Reg_Config[i][0], OV7670_Reg_Config[i][1]);
        if(res != 0) return 2;
        HAL_Delay(2);
        i++;
    }
    return 0;
}


void OV7670_Capture_To_LCD(void) {
    uint8_t high, low;
    uint16_t color;
    uint32_t timeout;
    LCD_SetWindow(40, 80, 160, 160);
    timeout = 0xFFFFF;
    while(READ_VSYNC() == 0)
    {
	    if(--timeout == 0) return;
    }
    timeout = 0xFFFFF;
    while(READ_VSYNC() == 1)
    {
	    if(--timeout == 0) return;
    }
    for(uint16_t y = 0; y < 180; y++) {
        timeout = 0xFFFFF;
        while(READ_HREF() == 0)
        {
	        if(--timeout == 0) break;
        }
        for(uint16_t x = 0; x < 180; x++)
        {
            while(READ_PCLK() == 0);
            high = READ_D0_D7();
            while(READ_PCLK() == 1);
            while(READ_PCLK() == 0);
            low = READ_D0_D7();
            while(READ_PCLK() == 1);
            color = (low << 8) | high;
            LCD_RAM = color;
        }
    }
}

