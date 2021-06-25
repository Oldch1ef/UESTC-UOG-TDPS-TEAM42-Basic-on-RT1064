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



//通过使用AT_ITCM_SECTION_ALIGN_INIT(函数定义) 将函数放入ITCM内运行
//具体使用方法参考以下示例
//放在ITCM内的代码不能调用没有放在ITCM内的代码
AT_ITCM_SECTION_INIT(void test(long t))
{
    while(t--);
}

//使用AT_DTCM_SECTION_INIT可以将函数放到DTCM内运行
//放在DTCM内的代码不能调用没有放在DTCM内的代码
//AT_DTCM_SECTION_INIT(void test(long t))
//{
//    while(t--);
//}

//使用AT_OCRAM_SECTION_INIT可以将函数放到OCRAM内运行
//放在OCRAM内的代码不能调用没有放在OCRAM内的代码
//AT_OCRAM_SECTION_INIT(void test(long t))
//{
//    while(t--);
//}

//通过以上方法可以将test函数放到ITCM内运行
//当程序较小的时候可能感受不到放到ITCM的好处，因为有cache加速，当代码较大的时候就会发现有明显的速度优势
//本示例程序仅仅演示如何使用，如果去测试时间可能时间基本是相同的



int main(void)
{
    //建议一般选择放入ITCM区域  库设置的DTCM有448KB大小  ITCM 64KB  OCRAM 512KB
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);
    EnableGlobalIRQ(0);
    while(1)
    {
        gpio_toggle(B9);
        test(100);
        
    }
}




