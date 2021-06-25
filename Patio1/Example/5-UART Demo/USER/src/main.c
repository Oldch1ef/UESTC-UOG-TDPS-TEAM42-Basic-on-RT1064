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



uint8 example_rx_buffer;
lpuart_transfer_t   example_receivexfer;
lpuart_handle_t     example_g_lpuartHandle;


uint8 uart_data;

void example_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        //数据已经被写入到了 之前设置的BUFF中
        //本例程使用的BUFF为 example_rx_buffer
        uart_data = example_rx_buffer;//将数据取出
    }
    
    handle->rxDataSize = example_receivexfer.dataSize;  //还原缓冲区长度
    handle->rxData = example_receivexfer.data;          //还原缓冲区地址
}


//实验现象说明：将RX TX短接 然后实现自发自收的功能
//通过在线调试可以看到 uart_data数据在持续加一操作

uint8 uart_send;
int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    
    
    //初始换串口   波特率为115200 TX为D16 RX为D17
    uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17);	
    NVIC_SetPriority(LPUART8_IRQn,15);         //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(USART_8,1);
    
    //配置串口接收的缓冲区及缓冲区长度
    example_receivexfer.dataSize = 1;
    example_receivexfer.data = &example_rx_buffer;
    
    //设置中断函数及其参数
    uart_set_handle(USART_8, &example_g_lpuartHandle, example_uart_callback, NULL, 0, example_receivexfer.data, 1);
    
    EnableGlobalIRQ(0);
    
    
    
    while(1)
    {
        uart_send++;
        
        //串口字节发送
        uart_putchar(USART_8,uart_send);
        //更多功能函数 自行查阅zf_uart文件
        systick_delay_ms(100);

    }

    
}





