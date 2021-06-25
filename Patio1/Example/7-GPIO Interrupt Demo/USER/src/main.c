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


uint8 gpio_status;
int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    
    
    //初始化GPIO C17 为输出 默认输出低电平 使用默认引脚配置GPIO_PIN_CONFIG
    gpio_init(C17,GPO,0,GPIO_PIN_CONFIG);
    
    //初始化GPIO C16 中断模式 使用默认引脚配置GPIO_INT_CONFIG
    gpio_interrupt_init(C16,RISING,GPIO_INT_CONFIG);
    
    //GPIO_DisableInterrupts(GPIO2,1<<17);//禁用C17中断   GPIO1：端口B  GPIO2：端口C  GPIO3：端口D  
    //GPIO_DisableInterrupts(GPIO2,1<<16);//禁用C16中断   GPIO1：端口B  GPIO2：端口C  GPIO3：端口D  
    //GPIO_DisableInterrupts(GPIO2,1<<15);//禁用C15中断   GPIO1：端口B  GPIO2：端口C  GPIO3：端口D  
    
    NVIC_SetPriority(GPIO2_Combined_16_31_IRQn,15);         //设置中断优先级 范围0-15 越小优先级越高
    
    EnableGlobalIRQ(0);
    
    
    //将C16 C17使用杜邦线链接起来然后在线调试查看gpio_int_test变量
    //变量会持续增加
    
    //gpio的中断函数名称为GPIO2_Combined_16_31_IRQHandler，定义在isr.c文件内
    //GPIO0表示A端口  RT没有这个端口
    //GPIO1表示B端口
    //GPIO2表示C端口  0_15表示C0-C15 IO口的中断响应都由这个中断函数管理  16_31表示C16-C31 IO口的中断响应都由这个中断函数管理
    //GPIO3表示D端口
    //GPIO4表示E端口  RT1064该端口全部IO被SDRAM占用
    //GPIO5表示F端口  RT仅有三个端口，但是功能特殊核心板并未引出
    
    while(1)
    {
        gpio_toggle(C17);//设置引脚电平为高电平
        systick_delay_ms(100);
        
    }

    
}




