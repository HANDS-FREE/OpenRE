/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED_I2C.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : 小林
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动IIC通信方式显示屏
*
* Others: none;
*
* Function List:
*	1. void I2C_Configuration(void) -- 配置CPU的硬件I2C
* 2. void I2C_WriteByte(unsigned char addr,unsigned char data) -- 向寄存器地址写一个byte的数据
* 3. void OLED_WriteCmd(unsigned char I2C_Command) -- 写命令
* 4. void OLED_WriteDat(unsigned char I2C_Data) -- 写数据
* 5. void OLED_Init(void) -- OLED屏初始化
* 6. void OLED_Set_Pos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 7. void OLED_Fill(unsigned char fill_Data) -- 全屏填充
* 8. void OLED_CLS(void) -- 清屏
* 9. void OLED_ON(void) -- 唤醒
* 10. void OLED_OFF(void) -- 睡眠
* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- 显示字符串(字体大小有6*8和8*16两种)
* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- 显示中文(中文需要先取模，然后放到codetab.h中)
* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMP图片
*
* History: none;
*
*****************************************************************************************/

#include "oled_iic_driver.h"

/************************************************************************************************************************
***                                                                                                                   ***
***                                           以下为底层接口函数                                                      ***
***                                                                                                                   ***
*************************************************************************************************************************/

OLED::OLED()
{

}

void OLED::OLED_iic_delay_ms(unsigned int t)
{
    delay_ms(t);
}

void OLED::OLED_WriteByte(unsigned char addr,unsigned char data)
{
    //my_i2c.I2C_Write_Byte(OLED_ADDRESS ,addr,data);
}

void OLED::OLED_WriteCmd(unsigned char I2C_Command)//写命令
{
    OLED_WriteByte(0x00, I2C_Command);
}

void OLED::OLED_WriteDat(unsigned char I2C_Data)  //写数据
{
    OLED_WriteByte(0x40, I2C_Data);
}


/************************************************************************************************************************
***                                                                                                                   ***
***                                           以下为驱动函数                                                          ***
***                                                                                                                   ***
*************************************************************************************************************************/

void OLED::OLED_Set_Pos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
    OLED_WriteCmd(0xb0+y);
    OLED_WriteCmd(((x&0xf0)>>4)|0x10);
    OLED_WriteCmd((x&0x0f)|0x01);
}


/*******************************************************************************
***                                                                                                                   ***
***                       以下为对外接口代码                                    ***
***                                                                                                                   ***
*******************************************************************************/
void OLED::OLED_Init(void)
{
    OLED_iic_delay_ms(100); //这里的延时很重要

    OLED_WriteCmd(0xAE); //display off
    OLED_WriteCmd(0x20);	//Set Memory Addressing Mode
    OLED_WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    OLED_WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
    OLED_WriteCmd(0xc8);	//Set COM Output Scan Direction
    OLED_WriteCmd(0x00); //---set low column address
    OLED_WriteCmd(0x10); //---set high column address
    OLED_WriteCmd(0x40); //--set start line address
    OLED_WriteCmd(0x81); //--set contrast control register
    OLED_WriteCmd(0xff); //亮度调节 0x00~0xff
    OLED_WriteCmd(0xa1); //--set segment re-map 0 to 127
    OLED_WriteCmd(0xa6); //--set normal display
    OLED_WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
    OLED_WriteCmd(0x3F); //
    OLED_WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    OLED_WriteCmd(0xd3); //-set display offset
    OLED_WriteCmd(0x00); //-not offset
    OLED_WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
    OLED_WriteCmd(0xf0); //--set divide ratio
    OLED_WriteCmd(0xd9); //--set pre-charge period
    OLED_WriteCmd(0x22); //
    OLED_WriteCmd(0xda); //--set com pins hardware configuration
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0xdb); //--set vcomh
    OLED_WriteCmd(0x20); //0x20,0.77xVcc
    OLED_WriteCmd(0x8d); //--set DC-DC enable
    OLED_WriteCmd(0x14); //
    OLED_WriteCmd(0xaf); //--turn on oled panel
}

void OLED::OLED_Fill_all(unsigned char fill_Data)//全屏填充
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WriteCmd(0xb0+m);		//page0-page1
        OLED_WriteCmd(0x00);		  //low column start address
        OLED_WriteCmd(0x10);		  //high column start address
        for(n=0;n<128;n++)
        {
            OLED_WriteDat(fill_Data);
        }
    }
}

//(x:0~127, y:0~7)  起始坐标(x1,y1)   终点坐标(x2,y2)   x2>x1  y2>y1
void OLED::OLED_Fill_area(unsigned char x1, unsigned char y1,
                          unsigned char x2, unsigned char y2,
                          unsigned char fill_Data)//填充一个区域
{
    unsigned char m,n;
    OLED_Set_Pos(x2,y2);
    for(m=y1;m<y2;m++)
    {
        OLED_WriteCmd(0xb0+m);		//page0-page1
        OLED_WriteCmd(0x00);		//low column start address
        OLED_WriteCmd(0x10);		//high column start address
        for(n=x1;n<x2;n++)
        {
            OLED_WriteDat(fill_Data);
        }
    }
}

void OLED::OLED_CLS(void)//清屏
{
    OLED_Fill_all(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED::OLED_ON(void)
{
    OLED_WriteCmd(0X8D);  //设置电荷泵
    OLED_WriteCmd(0X14);  //开启电荷泵
    OLED_WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED::OLED_OFF(void)
{
    OLED_WriteCmd(0X8D);  //设置电荷泵
    OLED_WriteCmd(0X10);  //关闭电荷泵
    OLED_WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED::OLED_Show_Str(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
    switch(TextSize)
    {
    case 1:
    {
        while(ch[j] != '\0')
        {
            c = ch[j] - 32;
            if(x > 126)
            {
                x = 0;
                y++;
            }
            OLED_Set_Pos(x,y);
            for(i=0;i<6;i++)
                OLED_WriteDat(F6x8[c][i]);
            x += 6;
            j++;
        }
    }break;
    case 2:
    {
        while(ch[j] != '\0')
        {
            c = ch[j] - 32;
            if(x > 120)
            {
                x = 0;
                y++;
            }
            OLED_Set_Pos(x,y);
            for(i=0;i<8;i++)
                OLED_WriteDat(F8X16[c*16+i]);
            OLED_Set_Pos(x,y+1);
            for(i=0;i<8;i++)
                OLED_WriteDat(F8X16[c*16+i+8]);
            x += 8;
            j++;
        }
    }break;
    }
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED::OLED_Show_CN(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm=0;
    unsigned int  adder=32*N;
    OLED_Set_Pos(x , y);
    for(wm = 0;wm < 16;wm++)
    {
        OLED_WriteDat(F16x16[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x,y + 1);
    for(wm = 0;wm < 16;wm++)
    {
        OLED_WriteDat(F16x16[adder]);
        adder += 1;
    }
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED::OLED_Draw_BMP(unsigned char x0,unsigned char y0, unsigned char x1
                         ,unsigned char y1,unsigned char BMP[] )
{
    unsigned int j=0;
    unsigned char x,y;

    if(y1%8==0)
        y = y1/8;
    else
        y = y1/8 + 1;
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0;x<x1;x++)
        {
            OLED_WriteDat(BMP[j++]);
        }
    }
}
