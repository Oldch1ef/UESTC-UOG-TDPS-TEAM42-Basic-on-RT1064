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
#include "fsl_ocotp.h"

#define EXAMPLE_OCOTP_FREQ_HZ (CLOCK_GetFreq(kCLOCK_IpgClk))
#define EXAMPLE_OCOTP_FUSE_MAP_ADDRESS 0x06
#define EXAMPLE_OCOTP_FUSE_WRITE_VALUE 0x18

uint8  burn_success;
uint32 fuse_value;

//本例程使用须知   必看  必看  必看

//注意这是不可恢复的操作，请谨慎决定
//注意这是不可恢复的操作，请谨慎决定
//注意这是不可恢复的操作，请谨慎决定


//使用本例程可以直接烧写RT1064的片内保险丝
//通过烧写保险丝之后，核心板启动时不需要使用外部的boot_cfg引脚，直接使用片内的保险丝状态来进行配置
//通过这样的方法，避免出现因为使用了boot_cfg引脚，导致出现内核启动时配置了错误的参数导致不启动的问题。

//可以通过串口助手查看提示信息以此判断是否操作成功
//或者运行后查看burn_success变量     1：烧写成功   0：烧写失败

//烧写失败的原因可能是因为已经烧写过了

int main(void)
{
	uint32 version;
	
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
	
	//此处编写用户代码(例如：外设初始化代码等)
	OCOTP_Init(OCOTP, EXAMPLE_OCOTP_FREQ_HZ);
	
	version = OCOTP_GetVersion(OCOTP);
	
	PRINTF("%x\r\n",version);
	
	fuse_value = OCOTP_ReadFuseShadowRegister(OCOTP, 0x00);//读取当前保险丝的状态
	//总中断最后开启
    EnableGlobalIRQ(0);
    while (1)
    {
        //此处编写需要循环执行的代码
		if (0x00U == (OCOTP_LOCK_BOOT_CFG_MASK & OCOTP_ReadFuseShadowRegister(OCOTP, 0x00)))
		{
			if (kStatus_Success == OCOTP_WriteFuseShadowRegister(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, EXAMPLE_OCOTP_FUSE_WRITE_VALUE))
			{
				PRINTF("OCOTP Write operation success!\r\n");
				burn_success = 1;//烧写成功
			}
			else
			{
				PRINTF("OCOTP write operation failed. Access deny!\r\n");
				burn_success = 0;//烧写失败
			}
		}
		while(1);
    }
}





