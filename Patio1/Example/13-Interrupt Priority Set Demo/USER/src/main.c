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


int main(void)
{
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
	
	
    
    //本例程主要展示如何设置各个中断的优先级
    //本库设置的优先级分组为3（在board_init函数中进行的设置） 全为抢占式。
    
    NVIC_SetPriority(DMA0_DMA16_IRQn,1);            //设置DMA中断优先级位1   范围0-15 越小优先级越高
    
    NVIC_SetPriority(PIT_IRQn,3);                   //设置PIT中断的优先级为3 范围0-15 越小优先级越高
    
    NVIC_SetPriority(GPIO2_Combined_0_15_IRQn,4);   //设置C0-C15  GPIO中断的优先级为4 范围0-15 越小优先级越高
    NVIC_SetPriority(GPIO2_Combined_16_31_IRQn,4);  //设置C16-C31 GPIO中断的优先级为4 范围0-15 越小优先级越高
	
    //其他中断优先级设置都是使用这个函数，对于函数的第一个参数填写，可以通过任意选中一个NVIC_SetPriority后面的第一个参数，然后go to过去查看，其他的IRQ号
    //所有的IRQ都定义在 MIMXRT1064.h IRQn_Type枚举中
    
	//总中断最后开启
    EnableGlobalIRQ(0);
    while (1)
    {
        
		
    }
}





