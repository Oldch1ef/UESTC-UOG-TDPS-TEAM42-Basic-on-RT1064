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


//使用本来例程请使用type C数据线连接核心板与电脑
//使用usb虚拟串口请务必注意操作顺序
//1在使用前请务必安装电脑端的驱动程序，驱动程序存放在16-USB CDC Demo文件夹下，右击fsl_ucwxp.inf文件点击安装即可
//2下载程序并运行
//3打开串口助手选择对应的串口并打开即可收到数据
//4如果程序复位之后，则串口助手需要关闭然后在打开
int main(void)
{
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
	
	usb_cdc_init();//初始化USB 虚拟串口
	
	
	
	
	//总中断最后开启
    EnableGlobalIRQ(0);
    while (1)
    {
		
		usb_cdc_send_str("Seekfree USB CDC Test\n");
		systick_delay_ms(500);
        //此处编写需要循环执行的代码
		
    }
}





