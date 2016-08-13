#ifndef __fsmc_lcd_driver_H
#define __fsmc_lcd_driver_H		

#include "bsplib.h"	 
//LCD重要参数集
typedef struct  
{										    
	unsigned short int width;			  //LCD 宽度
	unsigned short int height;		  //LCD 高度
	unsigned short int id;				  //LCD ID
	unsigned char  dir;			        //横屏还是竖屏控制：0，竖屏；1，横屏。	
	unsigned short int	wramcmd;		//开始写gram指令
	unsigned short int  setxcmd;		//设置x坐标指令
	unsigned short int  setycmd;		//设置y坐标指令 
}_lcd_dev; 	  


//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

//LCD的画笔颜色和背景色	   
extern unsigned short int  POINT_COLOR;//默认红色    
extern unsigned short int  BACK_COLOR; //背景颜色.默认为白色


#define LCD_LED_ON()           GPIO_ResetBits(GPIOB , GPIO_Pin_1)
#define LCD_LED_OFF()          GPIO_SetBits(GPIOB , GPIO_Pin_1)


//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LIGHTGRAY      0XEF5B //浅灰色(PANNEL)
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void TFTLCD_Init(void);													   	   //初始化
void LCD_DisplayOn(void);													     //开显示
void LCD_DisplayOff(void);													   //关显示
void LCD_Clear(unsigned short int Color);	 												 //清屏
void LCD_SetCursor(unsigned short int Xpos, unsigned short int Ypos);										//设置光标
void LCD_DrawPoint(unsigned short int x,unsigned short int y);											    //画点
void LCD_Fast_DrawPoint(unsigned short int x,unsigned short int y,unsigned short int color);								//快速画点
unsigned short int  LCD_ReadPoint(unsigned short int x,unsigned short int y); 											//读点 
void LCD_Draw_Circle(unsigned short int x0,unsigned short int y0,unsigned char r);						 			//画圆
void LCD_DrawLine(unsigned short int x1, unsigned short int y1, unsigned short int x2, unsigned short int y2);							//画线
void LCD_DrawRectangle(unsigned short int x1, unsigned short int y1, unsigned short int x2, unsigned short int y2);		   				//画矩形
void LCD_Fill(unsigned short int sx,unsigned short int sy,unsigned short int ex,unsigned short int ey,unsigned short int color);		   				//填充单色
void LCD_Color_Fill(unsigned short int sx,unsigned short int sy,unsigned short int ex,unsigned short int ey,unsigned short int *color);				//填充指定颜色
void LCD_ShowChar(unsigned short int x,unsigned short int y,unsigned char num,unsigned char size,unsigned char mode);						//显示一个字符
void LCD_ShowNum(unsigned short int x,unsigned short int y,u32 num,unsigned char len,unsigned char size);  						//显示一个数字
void LCD_ShowxNum(unsigned short int x,unsigned short int y,u32 num,unsigned char len,unsigned char size,unsigned char mode);				//显示 数字
void LCD_ShowString(unsigned short int x,unsigned short int y,unsigned short int width,unsigned short int height,unsigned char size,unsigned char *p);		//显示一个字符串,12/16字体

void LCD_WriteReg(unsigned short int LCD_Reg, unsigned short int LCD_RegValue);
unsigned short int LCD_ReadReg(unsigned short int LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(unsigned short int RGB_Code);
void LCD_SSD_BackLightSet(unsigned char pwm);							//SSD1963 背光控制
void LCD_Scan_Dir(unsigned char dir);									    //设置屏扫描方向
void LCD_Display_Dir(unsigned char dir);								 //设置屏幕显示方向
void LCD_Set_Window(unsigned short int sx,unsigned short int sy,unsigned short int width,unsigned short int height);	//设置窗口					   						   																			 


//LCD分辨率设置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		1		  //水平脉宽
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		1		  //垂直脉宽
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下几个参数，自动计算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif   //TFTLCD_Driver.h
	 
	 



