#include "OLED.h"
#include "main.h"

// 引脚初始化
void OLED_SPI_Init(void)
{
    OLED_W_D0(1);
    OLED_W_D1(1);
    OLED_W_RES(1);
    OLED_W_DC(1);
    OLED_W_CS(1);
}

// SPI发送一个字节
void OLED_SPI_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        OLED_W_D0(0);
        OLED_W_D1(Byte & (0x80 >> i));
        OLED_W_D0(1);
    }
}

// OLED写命令
void OLED_WriteCommand(uint8_t Command)
{
    OLED_W_CS(0);
    OLED_W_DC(0);
    OLED_SPI_SendByte(Command);
    OLED_W_CS(1);
}

//OLED写数据,Mode显示方式
void OLED_WriteData(uint8_t data, uint8_t Mode)
{
    if (!Mode)data = ~data;
    OLED_W_CS(0);
    OLED_W_DC(1);
    OLED_SPI_SendByte(data);
    OLED_W_CS(1);
}


/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));
    OLED_WriteCommand(0x00 | (X & 0x0F));
}

/**
  * @brief  OLED全屏填充或清屏
  * @param  填充的数据：0x00为清屏
  * @retval 无
  */
void OLED_Fill(uint8_t DAT)
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for(i = 0; i < 128; i++)
        {
            OLED_WriteData(DAT, 1);
        }
    }
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
    uint32_t i, j;

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++);
    }

    OLED_SPI_Init();
    
    OLED_WriteCommand(0xAE);

    OLED_WriteCommand(0xD5);
    OLED_WriteCommand(0x80);

    OLED_WriteCommand(0xA8);
    OLED_WriteCommand(0x3F);

    OLED_WriteCommand(0xD3);
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0x40);

    OLED_WriteCommand(0xA1);

    OLED_WriteCommand(0xC8);

    OLED_WriteCommand(0xDA);
    OLED_WriteCommand(0x12);

    OLED_WriteCommand(0x81);
    OLED_WriteCommand(0xCF);

    OLED_WriteCommand(0xD9);
    OLED_WriteCommand(0xF1);

    OLED_WriteCommand(0xDB);
    OLED_WriteCommand(0x30);

    OLED_WriteCommand(0xA4);

    OLED_WriteCommand(0xA6);

    OLED_WriteCommand(0x8D);
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0xAF);
    OLED_Fill(0x00);
}













