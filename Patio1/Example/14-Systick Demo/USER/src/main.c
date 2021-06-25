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

//可以修改zf_systick.h中DELAY_TIMER_TYPE宏定义的值来选择使用systick还是gpt定时器 
//完成延时与计时相关的功能
//默认设置为1，因为库加入了文件系统相关的驱动，文件系统需要占用systick定时器


uint32 use_time;
int main(void)
{
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
	
	
    
    //本例程主要展示如何使用systick 完成延时  计时等功能
    systick_delay_ms(500);//延时500毫秒
    
    
    systick_start();
    
    //将需要测试运行时间的代码放置在这里
    
    
    use_time = systick_getval_ms();//得到的时间单位为毫秒
    
    
    //更多的功能请查看zf_systick.h文件
    
	//总中断最后开启
    EnableGlobalIRQ(0);
    while (1)
    {
        
		
    }
}





