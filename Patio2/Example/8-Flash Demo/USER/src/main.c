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
#include "fsl_cache.h"

//定义flash最后一个扇区，避免与程序冲突
//存储参数最好从最后一个扇区开始使用
#define EXAMPLE_FLASH_SECTOR        (FLASH_SECTOR_NUM-1)

//定义所在扇区的页编号
#define EXAMPLE_FLASH_SECTOR_PAGE   (0)

uint8  write_data1;
uint16 write_data2;
uint32 write_data3;
float  write_data4;


uint8  read_data1;
uint16 read_data2;
uint32 read_data3;
float  read_data4;

uint8  read_data11;
uint16 read_data22;
uint32 read_data33;
float  read_data44;

uint8 status;


#define FLASH_SAVE_NUM  4//宏定义需要存储参数的个数    一个页最多为256字节，一个参数需要占4个字节，因此最多这里为256/4=64

uint32 write_buf[FLASH_SAVE_NUM];

uint32 read_buf[FLASH_SAVE_NUM];


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    flash_init();   //初始化flash
    

    //设置需要写入的数据
    write_data1 = 66;
    write_data2 = 6666;
    write_data3 = 666666;
    write_data4 = 6666.66;
	
    
    if(flash_check(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE))//校验当前 扇区所在页是否有数据，如果有数据则擦除整个扇区
    {
        status = flash_erase_sector(EXAMPLE_FLASH_SECTOR);//擦除扇区，如果扇区已经有数据则必须擦除扇区之后才能再次写入新的数据
        if(status)  while(1);//擦除失败
    }
    
    write_buf[0] = write_data1;
    write_buf[1] = write_data2;
    write_buf[2] = write_data3;
    
    //存储浮点时，首先取变量地址然后以uint32 *来访问变量获取数据。
    //write_buf[3] = *(uint32 *)&write_data4; 
    //不能使用此类格式write_buf[3] = (uint32)write_data4;这样会导致强制转换为整型，导致小数部分丢失
    //也可以使用库提供的宏定义 读取float类型的二进制数据
    write_buf[3] = float_conversion_uint32(write_data4);
    
    status = flash_page_program(EXAMPLE_FLASH_SECTOR, EXAMPLE_FLASH_SECTOR_PAGE, write_buf, FLASH_SAVE_NUM);
    if(status)  while(1);//写入失败

    //读取数据有两个方式
    //第一种方式为全部读取出来放在数组里，然后自行分配
    flash_read_page(EXAMPLE_FLASH_SECTOR, EXAMPLE_FLASH_SECTOR_PAGE, read_buf, FLASH_SAVE_NUM);
    //分别读取对应数据
    read_data1 = read_buf[0];
    read_data2 = read_buf[1];
    read_data3 = read_buf[2];
    read_data4 = uint32_conversion_float(read_buf[3]);      //读取浮点数时，应该使用宏函数将uint32类型转换为float
    
    //第二种方式，与以前的flash读取方式比较接近
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + EXAMPLE_FLASH_SECTOR * FLASH_SECTOR_SIZE, FLASH_SAVE_NUM*4);//读取flash前，最好先清空缓存
    read_data11 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+0,uint8);
    read_data22 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+1,uint16);
    read_data33 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+2,uint32);
    read_data44 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+3,float);

    
    
    EnableGlobalIRQ(0);
	
	
    //通过在线调试直接查看 read_data1 - read_data3 和 read_data11 - read_data33 变量的内容即可
	//观察写入的数据与读出的数据是否一致
    while(1)
    {

    }

    
}




