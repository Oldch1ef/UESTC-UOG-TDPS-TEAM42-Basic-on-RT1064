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


int main(void)
{
    DisableGlobalIRQ();
    board_init();   //务必保留，本函数用于初始化MPU 时钟 调试串口
    
    //初始化PWM1 MODULE3 的通道B 引脚为D1 频率50hz 占空比为 百分之100*5000/PWM_DUTY_MAX   PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000
    //每一个通道只能有一个引脚输出PWM
    pwm_init(PWM1_MODULE3_CHB_D1 , 50, 5000);
	
	
    pwm_init(PWM1_MODULE3_CHA_D0 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHB_D3 , 50, 5000);
    pwm_init(PWM2_MODULE3_CHA_D2 , 50, 5000);
    pwm_init(PWM1_MODULE0_CHB_D13, 50, 5000);
    pwm_init(PWM1_MODULE0_CHA_D12, 50, 5000);
    pwm_init(PWM1_MODULE1_CHB_D15, 50, 5000);
    pwm_init(PWM1_MODULE1_CHA_D14, 50, 5000);

    EnableGlobalIRQ(0);
    
    //使用示波器查看波形，D1引脚输出频率为50HZ，占空比为4%
	//其余引脚输出波形为50HZ，占空比为10%
    
    while(1)
    {
        //更改占空比为  百分之100*2000/PWM_DUTY_MAX  PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000
        pwm_duty(PWM1_MODULE3_CHB_D1,2000);
        
        systick_delay_ms(100);
        
    }

    
}




