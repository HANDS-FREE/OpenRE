/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: hf_bootloader.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license. 
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2016.1.28   V1.6           creat this file
* Description:this is a bootloader code of handsfree
* we refer to ALIENTEK's code and Improved it
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "hf_bootloader.h"
#include <stdlib.h>

unsigned int  USART_RX_CNT=0;		    	//the number of receive byte
//read byte from USARTx->SR could avoid some  error
unsigned char USART_RX_BUF[USART_REC_LEN]__attribute__ ((at(0X20001000)));

void HF_BootLoader_Init(void)
{

    BootLoader_Usart_Init;

}

#if Hardware_Platform==1

unsigned short int  IAP_BUF[1024];      //2K byte buffer
void IAP_Write_Flash_APP(unsigned int Flash_APP_Adress , unsigned char *APP_Buf ,unsigned int APP_Size)
{
    unsigned short int  t;
    unsigned short int  i=0;
    unsigned short int  temp;
    unsigned int  fwaddr=Flash_APP_Adress;        //current write address
    unsigned char *dfu=APP_Buf;
    for(t=0 ;t < APP_Size ; t+=2 )
    {
        temp=( unsigned short int )dfu[1]<<8;
        temp+=( unsigned short int )dfu[0];
        dfu+=2;                                   //Offset 2 byte
        IAP_BUF[i++]=temp;
        if(i==1024)
        {
            i=0;
            STMFLASH_Write(fwaddr,IAP_BUF,1024);
            fwaddr+=2048;                         //Offset 2048 byte 1024*2=2048
        }
    }
    if(i)STMFLASH_Write(fwaddr,IAP_BUF,i);        //write The rest of byte
}

#endif

#if Hardware_Platform == 4

unsigned int IAP_BUF[512]; 	         //2K byte buffer
void IAP_Write_Flash_APP(unsigned int Flash_APP_Adress , unsigned char *APP_Buf ,unsigned int APP_Size)
{
    unsigned int t;
    unsigned short int i=0;
    unsigned int temp;
    unsigned int fwaddr=Flash_APP_Adress;     //current write address
    unsigned char *dfu=APP_Buf;
    for(t=0;t<APP_Size;t+=4)
    {
        temp=(unsigned int)dfu[3]<<24;
        temp|=(unsigned int)dfu[2]<<16;
        temp|=(unsigned int)dfu[1]<<8;
        temp|=(unsigned int)dfu[0];
        dfu+=4;                               //Offset 4 byte
        IAP_BUF[i++]=temp;
        if(i==512)
        {
            i=0;
            STMFLASH_Write(fwaddr,IAP_BUF,512);
            fwaddr+=2048;                    //Offset 2048 byte 512*4=2048
        }
    }
    if(i)STMFLASH_Write(fwaddr,IAP_BUF,i);   //write The rest of byte
}

#endif

/***********************************************************************************************************************
* Function:     void Load_Flash_APP(u32 appxaddr)
*
* Scope:        public
*
* Description:  jump to app code
*
* Arguments:
* ppxaddr:the app's first address
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2016.1.28
***********************************************************************************************************************/
typedef  void (*Function)(void); //define a Parameter of function
Function Jump_App;
unsigned char Load_Flash_APP(unsigned int  Flash_APP_Adress)
{
    //0X08XXXXXX is right
    if(((*(volatile unsigned int *)(Flash_APP_Adress+4))&0xFF000000)==0x08000000)
    {
        if(((*(volatile unsigned int *)Flash_APP_Adress)&0x2FFE0000)==0x20000000)
        {
            Jump_App=(Function)*(volatile unsigned int *)(Flash_APP_Adress+4);
            MSR_MSP(*(volatile unsigned int *)Flash_APP_Adress);
            Jump_App();		//jump to app
        }
    }
    return 0;
}

/***********************************************************************************************************************
* Function:     void Load_Flash_APP(u32 appxaddr)
*
* Scope:        public
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
* by   mawenke   2016.1.28
***********************************************************************************************************************/
void Boot_Loader_Call(void)
{
    static unsigned int last_count=0;		 //last receive count
    static unsigned int  app_size=0;		 //the app's size
    int i;
    if(USART_RX_CNT)
    {
        /****if not receive new data in a new cycle****/
        if(last_count==USART_RX_CNT)
        {
            app_size=USART_RX_CNT;
            last_count=0;
            USART_RX_CNT=0;
            printf("receive firmware finish , size:%d bytes \r\n", app_size);
            printf("checking firmware  \r\n");
            if(((*(vu32*)(USART_RX_BUF+4))&0xFF000000)==0x08000000)
            {
                printf("check success and updating the firmwar... \r\n");
                for(i=0;i<0x8fff;i++);
                IAP_Write_Flash_APP(FLASH_APP1_ADDR,USART_RX_BUF,app_size);
                for(i=0;i<0x8fff;i++);
                printf("update finish and start the new firmware \r\n");
                for(i=0;i<0x8fff;i++);
                if(Load_Flash_APP(FLASH_APP1_ADDR)){   //execute APP code

                }
                else {
                    printf("start new firmware failed! \r\n");
                }
            }else
            {
                printf("check error!\r\n");
            }
        }
        else last_count=USART_RX_CNT;
    }
}

#ifdef __cplusplus
}
#endif 
