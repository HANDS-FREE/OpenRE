#include "GUI.h"
#include "malloc.h"

#define GUI_NUMBYTES  (20*1024)
#define GUI_BLOCKSIZE  0X80  //块大小

//GUI_X_Config
//初始化的时候调用,用来设置emwin所使用的内存
void GUI_X_Config(void) {

		U32 *aMemory = mymalloc(SRAMIN,GUI_NUMBYTES); //从内部RAM中分配GUI_NUMBYTES字节的内存
		GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //为存储管理系统分配一个存储块
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //设置存储快的平均尺寸,该区越大,可用的存储快数量越少
		GUI_SetDefaultFont(GUI_FONT_6X8); //设置默认字体

}
