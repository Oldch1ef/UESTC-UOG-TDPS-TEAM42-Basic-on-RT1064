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

//���ش���ǰ������Լ�ʹ�õ��������ڹ���������������Ϊ�Լ���ʹ�õ�

#include "headfile.h"


//----------------�ر�ע��----------------
//----------------�ر�ע��----------------
//----------------�ر�ע��----------------

//���������к�ή��ȫ����ʽ������С��ʹ��

//----------------�ر�ע��----------------
//----------------�ر�ע��----------------
//----------------�ر�ע��----------------


#define BUFFER_SIZE (512U)


static FATFS g_fileSystem; //�ļ�ϵͳ�ṹ�����
static FIL g_fileObject;   //�ļ��ṹ�����


//д�뻺����
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferWrite[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)],MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));

//��ȡ������
AT_DTCM_SECTION_ALIGN(uint8_t g_bufferRead[SDK_SIZEALIGN(BUFFER_SIZE, SDMMC_DATA_BUFFER_ALIGN_CACHE)], MAX(SDMMC_DATA_BUFFER_ALIGN_CACHE, SDMMCHOST_DMA_BUFFER_ADDR_ALIGN));



//SD����Ҫʹ�õ������� B23 C30 D4 D12 D13 D14 D15 D16 D17
//������İ���������ϵ���ȷ����Щ�˿���û�������������裨ȷ�ϲ��뿪�ش���OFF ��û�в�  ������˷�ģ�顢2��IPS������Ļ������ת����ģ�飩
//�����п��ܵ��������޷�ʹ��


//��ʹ��ǰ�뽫���İ��J1 J3���ߺ���������




//----------------�ر�ע��----------------
//----------------�ر�ע��----------------
//----------------�ر�ע��----------------

//���������к�ή��ȫ����ʽ������С��ʹ��

//----------------�ر�ע��----------------
//----------------�ر�ע��----------------
//----------------�ر�ע��----------------
int main(void)
{
    FRESULT error;
    DIR directory; //Ŀ¼�ṹ�����
    FILINFO fileInformation;
    UINT bytesWritten;
    UINT bytesRead;
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    volatile bool failedFlag = false;
    char ch = '0';
    BYTE work[FF_MAX_SS];
    
	DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

	
	sdcard_clk_init();//��ʼ��SDHCʱ��

	//���ж������
    EnableGlobalIRQ(0);

    
    PRINTF("\r\nFATFS �ļ�ϵͳʾ������\r\n");

    PRINTF("\r\n�����SD��\r\n");

    
    //�ȴ�SD������
    if (sdcard_wait_card_insert() != kStatus_Success)
    {
        return -1;
    }

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        PRINTF("����ʧ��\r\n");
        return -1;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("�ı�������ʧ��\r\n");
        return -1;
    }
#endif

#if FF_USE_MKFS
    PRINTF("\r\n�����ļ�ϵͳ�С������������Ҫһ���Ƚϳ���ʱ��\r\n");
	//��SD���ļ�ϵͳ�������֮�󣬾Ͳ���Ҫ��ÿ�ζ�������
	//��Ϊÿ�δ������ǻ��SD����ʽ��һ��ģ�ÿ�ζ���ʽ�����׵��¿�����
    if (f_mkfs(driverNumberBuffer, FM_ANY, 0U, work, sizeof work))
    {
        PRINTF("�����ļ�ϵͳʧ��\r\n");
        return -1;
    }
	SD_PowerOffCard(g_sd.host.base, g_sd.usrParam.pwr); //�����ļ�ϵͳ��ر�SD����Դ
    SD_PowerOnCard(g_sd.host.base, g_sd.usrParam.pwr);  //��sd����Դ
#endif /* FF_USE_MKFS */

    PRINTF("\r\n����Ŀ¼��\r\n");
    error = f_mkdir(_T("/dir_1"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("Ŀ¼�Ѵ���\r\n");
        }
        else
        {
            PRINTF("Ŀ¼����ʧ��\r\n");
            return -1;
        }
    }

    PRINTF("\r\n����һ���ļ��ڵ�ǰĿ¼��\r\n");
    error = f_open(&g_fileObject, _T("/dir_1/f_1.dat"), (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("�ļ��Ѵ���\r\n");
        }
        else
        {
            PRINTF("�����ļ�ʧ��\r\n");
            return -1;
        }
    }

    PRINTF("\r\n�ڵ�ǰĿ¼�У��ٴ���һ��Ŀ¼\r\n");
    error = f_mkdir(_T("/dir_1/dir_2"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("Ŀ¼�Դ���\r\n");
        }
        else
        {
            PRINTF("Ŀ¼����ʧ��\r\n");
            return -1;
        }
    }

    PRINTF("\r\n�г���Ŀ¼�е��ļ�\r\n");
    if (f_opendir(&directory, "/dir_1"))
    {
        PRINTF("Ŀ¼��ʧ��\r\n");
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
            PRINTF("�ļ��� : %s.\r\n", fileInformation.fname);
        }
        else
        {
            PRINTF("��ͨ�ļ� : %s.\r\n", fileInformation.fname);
        }
    }

    memset(g_bufferWrite, 'a', sizeof(g_bufferWrite));
    g_bufferWrite[BUFFER_SIZE - 2U] = '\r';
    g_bufferWrite[BUFFER_SIZE - 1U] = '\n';

    PRINTF("\r\nд��/��ȡ�ļ���ֱ����������\r\n");
    while (true)
    {
        if (failedFlag || (ch == 'q'))
        {
            break;
        }

        PRINTF("\r\nд�����ݵ����洴�����ļ�\r\n");
        error = f_write(&g_fileObject, g_bufferWrite, sizeof(g_bufferWrite), &bytesWritten);
        if ((error) || (bytesWritten != sizeof(g_bufferWrite)))
        {
            PRINTF("д���ļ�ʧ�� \r\n");
            failedFlag = true;
            continue;
        }

        /* Move the file pointer */
        if (f_lseek(&g_fileObject, 0U))
        {
            PRINTF("�����ļ�ָ��λ��ʧ��\r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("��ȡ���洴�����ļ�\r\n");
        memset(g_bufferRead, 0U, sizeof(g_bufferRead));
        error = f_read(&g_fileObject, g_bufferRead, sizeof(g_bufferRead), &bytesRead);
        if ((error) || (bytesRead != sizeof(g_bufferRead)))
        {
            PRINTF("��ȡ�ļ�ʧ��\r\n");
            failedFlag = true;
            continue;
        }

        PRINTF("��ʼ�Ƚ�д�����ȡ�����Ƿ�һ��\r\n");
        if (memcmp(g_bufferWrite, g_bufferRead, sizeof(g_bufferWrite)))
        {
            PRINTF("д�����ȡ���ݲ�һ��\r\n");
            failedFlag = true;
            continue;
        }
        PRINTF("д�����ȡ����һ��\r\n");

        PRINTF("\r\n����q�˳����� ���������ظ�ִ��д�����ȡ\r\n");
        ch = GETCHAR();
        PUTCHAR(ch);
    }
    PRINTF("\r\nʾ�����򲻻��ٽ��ж�ȡ����\r\n");

    if (f_close(&g_fileObject))
    {
        PRINTF("\r\n�ر��ļ�ʧ��\r\n");
        return -1;
    }

    while (true)
    {
    }
}





