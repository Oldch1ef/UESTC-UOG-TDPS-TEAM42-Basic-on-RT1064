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


uint8 gpio_status;
int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
    
    //��ʼ��GPIO B9 Ϊ��� Ĭ������͵�ƽ ʹ��Ĭ����������GPIO_PIN_CONFIG
    gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);

    //��ʼ��GPIO D0 D1 Ϊ��������
    gpio_init(D0 ,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(D1 ,GPI,0,GPIO_PIN_CONFIG);
    
    EnableGlobalIRQ(0);
    
    while(1)
    {
        gpio_set(B9,1);//�������ŵ�ƽΪ�ߵ�ƽ
        systick_delay_ms(100);
        gpio_set(B9,0);//�������ŵ�ƽΪ�͵�ƽ
        systick_delay_ms(100);
        gpio_toggle(B9);//��ת���ŵ�ƽ
        systick_delay_ms(100);
        
        
        
        gpio_status = gpio_get(D0);//��ȡ���ŵ�ƽ
        systick_delay_ms(100);
        
    }

    
}




