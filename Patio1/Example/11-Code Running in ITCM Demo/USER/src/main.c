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



//ͨ��ʹ��AT_ITCM_SECTION_ALIGN_INIT(��������) ����������ITCM������
//����ʹ�÷����ο�����ʾ��
//����ITCM�ڵĴ��벻�ܵ���û�з���ITCM�ڵĴ���
AT_ITCM_SECTION_INIT(void test(long t))
{
    while(t--);
}

//ʹ��AT_DTCM_SECTION_INIT���Խ������ŵ�DTCM������
//����DTCM�ڵĴ��벻�ܵ���û�з���DTCM�ڵĴ���
//AT_DTCM_SECTION_INIT(void test(long t))
//{
//    while(t--);
//}

//ʹ��AT_OCRAM_SECTION_INIT���Խ������ŵ�OCRAM������
//����OCRAM�ڵĴ��벻�ܵ���û�з���OCRAM�ڵĴ���
//AT_OCRAM_SECTION_INIT(void test(long t))
//{
//    while(t--);
//}

//ͨ�����Ϸ������Խ�test�����ŵ�ITCM������
//�������С��ʱ����ܸ��ܲ����ŵ�ITCM�ĺô�����Ϊ��cache���٣�������ϴ��ʱ��ͻᷢ�������Ե��ٶ�����
//��ʾ�����������ʾ���ʹ�ã����ȥ����ʱ�����ʱ���������ͬ��



int main(void)
{
    //����һ��ѡ�����ITCM����  �����õ�DTCM��448KB��С  ITCM 64KB  OCRAM 512KB
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);
    EnableGlobalIRQ(0);
    while(1)
    {
        gpio_toggle(B9);
        test(100);
        
    }
}




