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
#include "fsl_ocotp.h"

#define EXAMPLE_OCOTP_FREQ_HZ (CLOCK_GetFreq(kCLOCK_IpgClk))
#define EXAMPLE_OCOTP_FUSE_MAP_ADDRESS 0x06
#define EXAMPLE_OCOTP_FUSE_WRITE_VALUE 0x18

uint8  burn_success;
uint32 fuse_value;

//������ʹ����֪   �ؿ�  �ؿ�  �ؿ�

//ע�����ǲ��ɻָ��Ĳ��������������
//ע�����ǲ��ɻָ��Ĳ��������������
//ע�����ǲ��ɻָ��Ĳ��������������


//ʹ�ñ����̿���ֱ����дRT1064��Ƭ�ڱ���˿
//ͨ����д����˿֮�󣬺��İ�����ʱ����Ҫʹ���ⲿ��boot_cfg���ţ�ֱ��ʹ��Ƭ�ڵı���˿״̬����������
//ͨ�������ķ��������������Ϊʹ����boot_cfg���ţ����³����ں�����ʱ�����˴���Ĳ������²����������⡣

//����ͨ���������ֲ鿴��ʾ��Ϣ�Դ��ж��Ƿ�����ɹ�
//�������к�鿴burn_success����     1����д�ɹ�   0����дʧ��

//��дʧ�ܵ�ԭ���������Ϊ�Ѿ���д����

int main(void)
{
	uint32 version;
	
	DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
	
	//�˴���д�û�����(���磺�����ʼ�������)
	OCOTP_Init(OCOTP, EXAMPLE_OCOTP_FREQ_HZ);
	
	version = OCOTP_GetVersion(OCOTP);
	
	PRINTF("%x\r\n",version);
	
	fuse_value = OCOTP_ReadFuseShadowRegister(OCOTP, 0x00);//��ȡ��ǰ����˿��״̬
	//���ж������
    EnableGlobalIRQ(0);
    while (1)
    {
        //�˴���д��Ҫѭ��ִ�еĴ���
		if (0x00U == (OCOTP_LOCK_BOOT_CFG_MASK & OCOTP_ReadFuseShadowRegister(OCOTP, 0x00)))
		{
			if (kStatus_Success == OCOTP_WriteFuseShadowRegister(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, EXAMPLE_OCOTP_FUSE_WRITE_VALUE))
			{
				PRINTF("OCOTP Write operation success!\r\n");
				burn_success = 1;//��д�ɹ�
			}
			else
			{
				PRINTF("OCOTP write operation failed. Access deny!\r\n");
				burn_success = 0;//��дʧ��
			}
		}
		while(1);
    }
}





