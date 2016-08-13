/************************************************************************************
* Copyright (C), MAWENKE
*
* FileName:   ff_top.c
*
* Author:     MAWENKE
*
* Version :  
*
* Date: 2015-11-3
*
* Description: 
*
* Function List: 
*
* 1. -------
*
* History: 
*
* <author> <time> <version > <desc>
* 

***********************************************************************************/

#include "ff_top.h"

#if FatFS_TEST_ENABLE > 0u    //使能SD卡文件系统测试


int res;  
int a;
FIL fdst;
FATFS fs;   
UINT br, bw;            // File R/W count
BYTE buffer[512];       // file copy buffer
BYTE textFileBuffer[] = " HANDS FREE ！^_^ \r\n " ;

void FatFS_Test(void)
{	

 	printf("\r\n 这是一个MicroSD卡文件系统实验(FATFS R0.09)\n");
	printf ( "\r\n disk_initialize starting......\n " );

	f_mount(0,&fs);		    //挂载0磁盘

	res = f_open(&fdst,"0:/Demo.TXT",FA_CREATE_NEW | FA_WRITE);
	 
	if ( res == FR_OK )
 	 { 
    /* 将缓冲区的数据写到文件中 */
		res = f_write(&fdst, textFileBuffer, sizeof(textFileBuffer), &bw); 
	  printf( "\r\n 文件创建成功 \n" );        
    f_close(&fdst);   /*关闭文件 */      
   }
   else if ( res == FR_EXIST )
 	 { 
		printf( "\r\n 文件已经存在 \n" );
 	 }

   /*---------------- 将刚刚新建的文件里面的内容打印到超级终端 -----------------------*/
  /* 以只读的方式打开刚刚创建的文件 */
	res = f_open(&fdst, "0:/Demo.TXT", FA_OPEN_EXISTING | FA_READ); /* 打开文件 */		
	br = 1;
	a = 0;	
  for (;;) 
	{
		for ( a=0; a<512; a++ ) 	                          /* 清缓冲区 */
			buffer[a]=0;
			 
  	res = f_read( &fdst, buffer, sizeof(buffer), &br ); /* 将文件里面的内容读到缓冲区 */
		printf("\r\n %s ", buffer);						
  	if (res || br == 0) break;                          /* 错误或者到了文件尾 */        	    	
  }
	
	f_close(&fdst);	                                      /* 关闭打开的文件 */	

 
}


#endif

	  
