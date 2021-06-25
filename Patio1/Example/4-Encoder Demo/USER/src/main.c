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



int16 encoder1;
int16 encoder2;
int16 encoder3;
int16 encoder4;

int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
    
    pwm_init(PWM1_MODULE3_CHB_D1 , 50, 5000);
    pwm_init(PWM1_MODULE3_CHA_D0 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHB_D3 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHA_D2 , 50, 5000);
    
    
    
    //һ��QTIMER���� ����������������
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER0_C0 B��ʹ��QTIMER1_TIMER1_C1
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER2_C2 B��ʹ��QTIMER1_TIMER3_C24
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);

    
    qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);
    qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);
    
    //���Է���һ 
	//����Ĭ��ʹ��D0 D1 D2 D3���PWM ��ģ��������������ź�
    //��C0�� D0ʹ�öŰ�����������
    //��C2�� D1ʹ�öŰ�����������
    //��C3�� D2ʹ�öŰ�����������
    //��B18�� D3ʹ�öŰ�����������
    //��C1 C3 C24 B19 �ӵأ����Կ����ɼ���������Ϊ5.
    
	
	//���Է�ʽ��
    //���ֱ�����ӱ�������A B�࣬��ô�����ֱ�Ӳɼ�����������
    
    EnableGlobalIRQ(0);
    
    
    
    while(1)
    {
        //��ȡ����������ֵ
        encoder1 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 );
        encoder2 = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2 );
        encoder3 = qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );
        encoder4 = qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);
        
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
        qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );
        qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
        qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
        
        systick_delay_ms(100);
        
    }
}




