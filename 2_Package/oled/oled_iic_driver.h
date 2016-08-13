#ifndef __oled_iic_driver_H
#define	__oled_iic_driver_H

#include "bsplib.h"
#include "codetab.h"

#define OLED_ADDRESS	0x78     //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

class OLED
{
public:
    OLED();
    void OLED_Init(void);
    void OLED_Fill_all(unsigned char fill_Data);
    void OLED_CLS(void);
    void OLED_ON(void);
    void OLED_OFF(void);
    void OLED_Show_Str(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
    void OLED_Show_CN(unsigned char x, unsigned char y, unsigned char N);
    void OLED_Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
    void OLED_Fill_area(unsigned char x1, unsigned char y1,unsigned char x2, unsigned char y2, unsigned char fill_Data);//填充一个区域

private:
    void OLED_iic_delay_ms(unsigned int t);
    void OLED_WriteByte(uint8_t addr,uint8_t data);
    void OLED_WriteCmd(unsigned char I2C_Command);
    void OLED_WriteDat(unsigned char I2C_Data);
    void OLED_Set_Pos(unsigned char x, unsigned char y);

};





#endif   //__oled_iic_driver_H
