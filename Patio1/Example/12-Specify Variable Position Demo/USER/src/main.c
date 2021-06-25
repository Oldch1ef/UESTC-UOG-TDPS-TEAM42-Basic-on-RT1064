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



#include "headfile.h"



//本例程将详细解释变量的存放位置以及如何指定变量存在我们想要的RAM中


uint8 a;        //未赋值的全局变量 存放在DTCM里面
uint8 b=1;      //赋值的全局变量   放在DTCM里面



AT_DTCM_SECTION(uint8 c);          		        //指定变量存放在DTCM区域
AT_DTCM_SECTION_ALIGN(uint8 d,4);  		        //指定变量存放在DTCM区域  并且4字节对齐

AT_OCRAM_SECTION(uint8 e);                      //指定变量存放在OCRAM区域
AT_OCRAM_SECTION_ALIGN(uint8 f,4);              //指定变量存放在OCRAM区域  并且4字节对齐

AT_SDRAM_SECTION(uint8 g);                      //指定变量存放在SDRAM区域
AT_SDRAM_SECTION_ALIGN(uint8 h,4);              //指定变量存放在SDRAM区域  并且4字节对齐

AT_SDRAM_NONCACHE_SECTION(uint8 i);             //指定变量存放在SDRAM noncache区域
AT_SDRAM_NONCACHE_SECTION_ALIGN(uint8 j,4);     //指定变量存放在SDRAM noncache区域  并且4字节对齐

int main(void)
{
    //在函数内部定义的变量以及 函数的参数都是存在栈区域的，栈是放在了DTCM里
    //因此这些变量都是放在DTCM的
    uint8 x;    //此变量存放在DTCM里面

    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    x=0;
    while(1)
    {
        c++;
        d++;
        e++;
        f++;
        g++;
        h++;
        i++;
        j++;
        x++;
    }
}





