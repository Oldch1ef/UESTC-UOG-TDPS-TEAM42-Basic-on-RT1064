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


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
    //��ʼ��PWM1 MODULE3 ��ͨ��B ����ΪD1 Ƶ��50hz ռ�ձ�Ϊ �ٷ�֮100*5000/PWM_DUTY_MAX   PWM_DUTY_MAX��fsl_pwm.h�ļ��� Ĭ��Ϊ50000
    //ÿһ��ͨ��ֻ����һ���������PWM
    pwm_init(PWM1_MODULE3_CHB_D1 , 50, 5000);
	
	
    pwm_init(PWM1_MODULE3_CHA_D0 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHB_D3 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHA_D2 , 50, 5000);
    pwm_init(PWM1_MODULE0_CHB_D13, 50, 5000);
    pwm_init(PWM1_MODULE0_CHA_D12, 50, 5000);
    pwm_init(PWM1_MODULE1_CHB_D15, 50, 5000);
    pwm_init(PWM1_MODULE1_CHA_D14, 50, 5000);

    EnableGlobalIRQ(0);
    
    //ʹ��ʾ�����鿴���Σ�D1�������Ƶ��Ϊ50HZ��ռ�ձ�Ϊ4%
	//���������������Ϊ50HZ��ռ�ձ�Ϊ10%
    
    while(1)
    {
        //����ռ�ձ�Ϊ  �ٷ�֮100*2000/PWM_DUTY_MAX  PWM_DUTY_MAX��fsl_pwm.h�ļ��� Ĭ��Ϊ50000
        pwm_duty(PWM1_MODULE3_CHB_D1,2000);
        
        systick_delay_ms(100);
        
    }

    
}




