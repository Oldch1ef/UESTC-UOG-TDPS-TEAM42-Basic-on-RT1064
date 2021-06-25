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


//----------------特别注意----------------
//----------------特别注意----------------
//----------------特别注意----------------

//本例程运行后会降卡全部格式化，请小心使用

//----------------特别注意----------------
//----------------特别注意----------------
//----------------特别注意----------------


#define BUFFER_SIZE (512U)


static FATFS g_fileSystem; //文件系统结构体变量
static FIL g_fileObject;   //文件结构体变量


//写入缓冲区
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));

//读取缓冲区
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)], MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));



//SD卡需要使用的引脚有 B23 C30 D4 D12 D13 D14 D15 D16 D17
//如果核心板插在主板上的请确认这些端口是没有连接其他外设（确认拨码开关处于OFF 且没有插  舵机、运放模块、2寸IPS并口屏幕、无线转串口模块）
//否则有可能导致例程无法使用


//在使用前请将核心板的J1 J3跳线焊接起来。




//----------------特别注意----------------
//----------------特别注意----------------
//----------------特别注意----------------

//本例程运行后会降卡全部格式化，请小心使用

//----------------特别注意----------------
//----------------特别注意----------------
//----------------特别注意----------------
int main(void)
{
    FRESULT error;
    DIR directory; //目录结构体变量
    FILINFO fileInformation;
    UINT bytesWritten;
    UINT bytesRead;
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    volatile bool failedFlag = false;
    char ch = '0';
    BYTE work[FF_MAX_SS];
    
	DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口

	
	sdcard_clk_init();//初始化SDHC时钟

	//总中断最后开启
    EnableGlobalIRQ(0);

    
    PRINTF("\r\nFATFS 文件系统示例程序\r\n");

    PRINTF("\r\n请插入SD卡\r\n");

    
    //等待SD卡插入
    if (sdcard_wait_card_insert() != kStatus_Success)
    {
        return -1;
    }

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        PRINTF("挂载失败\r\n");
        return -1;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("改变驱动器失败\r\n");
        return -1;
    }
#endif

#if FF_USE_MKFS
    PRINTF("\r\n创建文件系统中。。。这可能需要一个比较长的时间\r\n");
	//当SD卡文件系统创建完毕之后，就不需要在每次都创建了
	//因为每次创建都是会把SD卡格式化一遍的，每次都格式化容易导致卡报废
    if (f_mkfs(driverNumberBuffer, FM_ANY, 0U, work, sizeof work))
    {
        PRINTF("创建文件系统失败\r\n");
        return -1;
    }
	SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr); //创建文件系统后关闭SD卡电源
    SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);  //打开sd卡电源
#endif /* FF_USE_MKFS */

    PRINTF("\r\n创建目录中\r\n");
    error = f_mkdir(_T("/dir_1"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("目录已存在\r\n");
        }
        else
        {
            PRINTF("目录创建失败\r\n");
            return -1;
        }
    }

    PRINTF("\r\n创建一个文件在当前目录下\r\n");
    error = f_open(&g_fileObject, _T("/dir_1/f_1.dat"), (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("文件已存在\r\n");
        }
        else
        {
            PRINTF("创建文件失败\r\n");
            return -1;
        }
    }

    PRINTF("\r\n在当前目录中，再创建一个目录\r\n");
    error = f_mkdir(_T("/dir_1/dir_2"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("目录以存在\r\n");
        }
        else
        {
            PRINTF("目录创建失败\r\n");
            return -1;
        }
    }

    PRINTF("\r\n列出该目录中的文件\r\n");
    if (f_opendir(&directory, "/dir_1"))
    {
        PRINTF("目录打开失败\r\n");
        return -1;
    }

    for (;;)
    {
        error = f_readdir(&directory, &fileInformation);

        /* To the end. */
        if ((error != FR_OK) || (fileInformation.fname[0U] == 0U))
        {
            break;
        }
        if (fileInformation.fname[0] == '.')
        {
            continue;
        }
        if (fileInformation.fattrib & AM_DIR)
        {
            PRINTF("文件夹 : %s.\r\n", fileInformation.fname);
        }
        else
        {
            PRINTF("普通文件 : %s.\r\n", fileInformation.fname);
        }
    }

    memset(g_bufferWrite, 'a', sizeof(g_bufferWrite));
    g_bufferWrite[BUFFER_SIZE - 2U] = '\r';
    g_bufferWrite[BUFFER_SIZE - 1U] = '\n';

    PRINTF("\r\n写入/读取文件，直到遇到错误\r\n");
    while (true)
    {
        if (failedFlag || (ch == 'q'))
        {
            break;
        }

        PRINTF("\r\n写入数据到上面创建的文件\r\n");
        error = f_write(&g_fileObject, g_bufferWrite, sizeof(g_bufferWrite), &bytesWritten);
        if ((error) || (bytesWritten != sizeof(g_bufferWrite)))
        {
            PRINTF("写入文件失败 \r\n");
            failedFlag = true;
            continue;
        }

        /* Move the file pointer */
        if (f_lseek(&g_fileObject, 0U))
        {
            PRINTF("设置文件指针位置失败\r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("读取上面创建的文件\r\n");
        memset(g_bufferRead, 0U, sizeof(g_bufferRead));
        error = f_read(&g_fileObject, g_bufferRead, sizeof(g_bufferRead), &bytesRead);
        if ((error) || (bytesRead != sizeof(g_bufferRead)))
        {
            PRINTF("读取文件失败\r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("开始比较写入与读取数据是否一致\r\n");
        if (memcmp(g_bufferWrite, g_bufferRead, sizeof(g_bufferWrite)))
        {
            PRINTF("写入与读取数据不一致\r\n");
            failedFlag = true;
            continue;
        }
        PRINTF("写入与读取数据一致\r\n");

        PRINTF("\r\n输入q退出程序 输入其他重复执行写入与读取\r\n");
        ch = GETCHAR();
        PUTCHAR(ch);
    }
    PRINTF("\r\n示例程序不会再进行读取操作\r\n");

    if (f_close(&g_fileObject))
    {
        PRINTF("\r\n关闭文件失败\r\n");
        return -1;
    }

    while (true)
    {
    }
}





