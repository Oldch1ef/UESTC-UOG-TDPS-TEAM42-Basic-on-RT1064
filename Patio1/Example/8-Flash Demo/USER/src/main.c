/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.24
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�



//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������



#include "headfile.h"
#include "fsl_cache.h"

//����flash���һ������������������ͻ
//�洢������ô����һ��������ʼʹ��
#define EXAMPLE_FLASH_SECTOR        (FLASH_SECTOR_NUM-1)

//��������������ҳ���
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


#define FLASH_SAVE_NUM  4//�궨����Ҫ�洢�����ĸ���    һ��ҳ���Ϊ256�ֽڣ�һ��������Ҫռ4���ֽڣ�����������Ϊ256/4=64

uint32 write_buf[FLASH_SAVE_NUM];

uint32 read_buf[FLASH_SAVE_NUM];


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    flash_init();   //��ʼ��flash
    

    //������Ҫд�������
    write_data1 = 66;
    write_data2 = 6666;
    write_data3 = 666666;
    write_data4 = 6666.66;
	
    
    if(flash_check(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE))//У�鵱ǰ ��������ҳ�Ƿ������ݣ�����������������������
    {
        status = flash_erase_sector(EXAMPLE_FLASH_SECTOR);//������������������Ѿ�������������������֮������ٴ�д���µ�����
        if(status)  while(1);//����ʧ��
    }
    
    write_buf[0] = write_data1;
    write_buf[1] = write_data2;
    write_buf[2] = write_data3;
    
    //�洢����ʱ������ȡ������ַȻ����uint32 *�����ʱ�����ȡ���ݡ�
    //write_buf[3] = *(uint32 *)&write_data4; 
    //����ʹ�ô����ʽwrite_buf[3] = (uint32)write_data4;�����ᵼ��ǿ��ת��Ϊ���ͣ�����С�����ֶ�ʧ
    //Ҳ����ʹ�ÿ��ṩ�ĺ궨�� ��ȡfloat���͵Ķ���������
    write_buf[3] = float_conversion_uint32(write_data4);
    
    status = flash_page_program(EXAMPLE_FLASH_SECTOR, EXAMPLE_FLASH_SECTOR_PAGE, write_buf, FLASH_SAVE_NUM);
    if(status)  while(1);//д��ʧ��

    //��ȡ������������ʽ
    //��һ�ַ�ʽΪȫ����ȡ�������������Ȼ�����з���
    flash_read_page(EXAMPLE_FLASH_SECTOR, EXAMPLE_FLASH_SECTOR_PAGE, read_buf, FLASH_SAVE_NUM);
    //�ֱ��ȡ��Ӧ����
    read_data1 = read_buf[0];
    read_data2 = read_buf[1];
    read_data3 = read_buf[2];
    read_data4 = uint32_conversion_float(read_buf[3]);      //��ȡ������ʱ��Ӧ��ʹ�ú꺯����uint32����ת��Ϊfloat
    
    //�ڶ��ַ�ʽ������ǰ��flash��ȡ��ʽ�ȽϽӽ�
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + EXAMPLE_FLASH_SECTOR * FLASH_SECTOR_SIZE, FLASH_SAVE_NUM*4);//��ȡflashǰ���������ջ���
    read_data11 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+0,uint8);
    read_data22 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+1,uint16);
    read_data33 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+2,uint32);
    read_data44 = flash_read(EXAMPLE_FLASH_SECTOR,EXAMPLE_FLASH_SECTOR_PAGE*FLASH_PAGE_SIZE+3,float);

    
    
    EnableGlobalIRQ(0);
	
	
    //ͨ�����ߵ���ֱ�Ӳ鿴 read_data1 - read_data3 �� read_data11 - read_data33 ���������ݼ���
	//�۲�д�������������������Ƿ�һ��
    while(1)
    {

    }

    
}




