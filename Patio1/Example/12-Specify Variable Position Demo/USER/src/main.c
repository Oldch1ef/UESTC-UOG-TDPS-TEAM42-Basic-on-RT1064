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



//�����̽���ϸ���ͱ����Ĵ��λ���Լ����ָ����������������Ҫ��RAM��


uint8 a;        //δ��ֵ��ȫ�ֱ��� �����DTCM����
uint8 b=1;      //��ֵ��ȫ�ֱ���   ����DTCM����



AT_DTCM_SECTION(uint8 c);          		        //ָ�����������DTCM����
AT_DTCM_SECTION_ALIGN(uint8 d,4);  		        //ָ�����������DTCM����  ����4�ֽڶ���

AT_OCRAM_SECTION(uint8 e);                      //ָ�����������OCRAM����
AT_OCRAM_SECTION_ALIGN(uint8 f,4);              //ָ�����������OCRAM����  ����4�ֽڶ���

AT_SDRAM_SECTION(uint8 g);                      //ָ�����������SDRAM����
AT_SDRAM_SECTION_ALIGN(uint8 h,4);              //ָ�����������SDRAM����  ����4�ֽڶ���

AT_SDRAM_NONCACHE_SECTION(uint8 i);             //ָ�����������SDRAM noncache����
AT_SDRAM_NONCACHE_SECTION_ALIGN(uint8 j,4);     //ָ�����������SDRAM noncache����  ����4�ֽڶ���

int main(void)
{
    //�ں����ڲ�����ı����Լ� �����Ĳ������Ǵ���ջ����ģ�ջ�Ƿ�����DTCM��
    //�����Щ�������Ƿ���DTCM��
    uint8 x;    //�˱��������DTCM����

    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    x=0;
    while(1)
    {
        c++;
        d++;
        e++;
        f++;
        g++;
        h++;
        i++;
        j++;
        x++;
    }
}





