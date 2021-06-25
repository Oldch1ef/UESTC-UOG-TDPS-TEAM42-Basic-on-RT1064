/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本



//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的

#include "headfile.h"



uint8 test[50];

int main(void)
{
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
	
	
    
    //本例程主要展示如何对缓存进行操作
    //关于缓存的刷新，很多人问为什么要刷新缓存？这里进举例一个情况，例如我们使用DMA对一个数组进行了写入操作，
    //然后我在去读取数组的数据的话，你会发现读取的数据还是以前的并不是DMA刚写入的数据，因为数据写入是通过DMA操作的，
    //因此CPU是不知道数据已经变更了，如果去读取数据的话其实还是读取的缓存数据，这个时候我们就需要去刷新一下缓存，
    //然后在去读取数据。
    
    
    L1CACHE_DisableDCache();        //禁用cache
    L1CACHE_EnableDCache();         //启用cache
    L1CACHE_CleanInvalidateDCache();//对所有的缓存清除并无效
    L1CACHE_CleanInvalidateDCacheByRange((uint32)test[0],50);//对test数组的缓存 清除并无效（即刷新）
    
	
	//总中断最后开启
    EnableGlobalIRQ(0);
    while (1)
    {
        
		
    }
}





