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
    
    
    //��ʼ��GPIO C17 Ϊ��� Ĭ������͵�ƽ ʹ��Ĭ����������GPIO_PIN_CONFIG
    gpio_init(C17,GPO,0,GPIO_PIN_CONFIG);
    
    //��ʼ��GPIO C16 �ж�ģʽ ʹ��Ĭ����������GPIO_INT_CONFIG
    gpio_interrupt_init(C16,RISING,GPIO_INT_CONFIG);
    
    //GPIO_DisableInterrupts(GPIO2,1<<17);//����C17�ж�   GPIO1���˿�B  GPIO2���˿�C  GPIO3���˿�D  
    //GPIO_DisableInterrupts(GPIO2,1<<16);//����C16�ж�   GPIO1���˿�B  GPIO2���˿�C  GPIO3���˿�D  
    //GPIO_DisableInterrupts(GPIO2,1<<15);//����C15�ж�   GPIO1���˿�B  GPIO2���˿�C  GPIO3���˿�D  
    
    NVIC_SetPriority(GPIO2_Combined_16_31_IRQn,15);         //�����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    
    EnableGlobalIRQ(0);
    
    
    //��C16 C17ʹ�öŰ�����������Ȼ�����ߵ��Բ鿴gpio_int_test����
    //�������������
    
    //gpio���жϺ�������ΪGPIO2_Combined_16_31_IRQHandler��������isr.c�ļ���
    //GPIO0��ʾA�˿�  RTû������˿�
    //GPIO1��ʾB�˿�
    //GPIO2��ʾC�˿�  0_15��ʾC0-C15 IO�ڵ��ж���Ӧ��������жϺ�������  16_31��ʾC16-C31 IO�ڵ��ж���Ӧ��������жϺ�������
    //GPIO3��ʾD�˿�
    //GPIO4��ʾE�˿�  RT1064�ö˿�ȫ��IO��SDRAMռ��
    //GPIO5��ʾF�˿�  RT���������˿ڣ����ǹ���������İ岢δ����
    
    while(1)
    {
        gpio_toggle(C17);//�������ŵ�ƽΪ�ߵ�ƽ
        systick_delay_ms(100);
        
    }

    
}




