/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		pwm
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


#include "zf_iomuxc.h"
#include "zf_pwm.h"
#include "zf_gpio.h"
#define PI 3.1415926;
#define PWM_SRC_CLK_FREQ    CLOCK_GetFreq(kCLOCK_IpgClk)        //定义PWM输入时钟源频率
#define PWM_PIN_CONF        SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置PWM引脚默认配置   

static PWM_Type * PWMPTR[] = PWM_BASE_PTRS;


void pwm_iomuxc(PWMCH_enum pwmch)
{
    switch(pwmch)
    {
        case PWM1_MODULE0_CHA_D12:  iomuxc_pinconf(D12,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE0_CHA_E23:  iomuxc_pinconf(E23,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE0_CHB_D13:  iomuxc_pinconf(D13,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE0_CHB_E24:  iomuxc_pinconf(E24,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE1_CHA_D14:  iomuxc_pinconf(D14,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE1_CHA_E25:  iomuxc_pinconf(E25,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE1_CHB_D15:  iomuxc_pinconf(D15,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE1_CHB_E26:  iomuxc_pinconf(E26,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE2_CHA_D16:  iomuxc_pinconf(D16,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE2_CHA_E27:  iomuxc_pinconf(E27,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE2_CHB_D17:  iomuxc_pinconf(D17,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE2_CHB_E28:  iomuxc_pinconf(E28,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM1_MODULE3_CHA_B10:  iomuxc_pinconf(B10,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_C16:  iomuxc_pinconf(C16,ALT6,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_D0 :  iomuxc_pinconf(D0 ,ALT2,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_D24:  iomuxc_pinconf(D24,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_E12:  iomuxc_pinconf(E12,ALT4,PWM_PIN_CONF); break;
                                                   
                                                   
        case PWM1_MODULE3_CHB_B11:  iomuxc_pinconf(B11,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_C17:  iomuxc_pinconf(C17,ALT6,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_D1 :  iomuxc_pinconf(D1 ,ALT2,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_D25:  iomuxc_pinconf(D25,ALT1,PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_E13:  iomuxc_pinconf(E13,ALT4,PWM_PIN_CONF); break;
                                                   
                                                   
                                                   
        case PWM2_MODULE0_CHA_C6 :  iomuxc_pinconf(C6 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE0_CHA_E6 :  iomuxc_pinconf(E6 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE0_CHB_C7 :  iomuxc_pinconf(C7 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE0_CHB_E7 :  iomuxc_pinconf(E7 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE1_CHA_C8 :  iomuxc_pinconf(C8 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE1_CHA_E8 :  iomuxc_pinconf(E8 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE1_CHB_C9 :  iomuxc_pinconf(C9 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE1_CHB_E9 :  iomuxc_pinconf(E9 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE2_CHA_C10:  iomuxc_pinconf(C10,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE2_CHA_E10:  iomuxc_pinconf(E10,ALT1,PWM_PIN_CONF); break;

        case PWM2_MODULE2_CHB_C11:  iomuxc_pinconf(C11,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE2_CHB_E11:  iomuxc_pinconf(E11,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE3_CHA_B0 :  iomuxc_pinconf(B0 ,ALT1,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_C18:  iomuxc_pinconf(C18,ALT6,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_D2 :  iomuxc_pinconf(D2 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_E19:  iomuxc_pinconf(E19,ALT1,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_B9 :  iomuxc_pinconf(B9 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE3_CHB_B1 :  iomuxc_pinconf(B1 ,ALT1,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_C19:  iomuxc_pinconf(C19,ALT6,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_D3 :  iomuxc_pinconf(D3 ,ALT2,PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_E20:  iomuxc_pinconf(E20,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE0_CHA_E29:  iomuxc_pinconf(E29,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE0_CHB_E30:  iomuxc_pinconf(E30,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE1_CHA_E31:  iomuxc_pinconf(E31,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE1_CHB_D18:  iomuxc_pinconf(D18,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE2_CHA_D19:  iomuxc_pinconf(D19,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE2_CHB_D20:  iomuxc_pinconf(D20,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE3_CHA_E21:  iomuxc_pinconf(E21,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM3_MODULE3_CHB_E22:  iomuxc_pinconf(E22,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE0_CHA_B24:  iomuxc_pinconf(B24,ALT1,PWM_PIN_CONF); break;
        case PWM4_MODULE0_CHA_E0 :  iomuxc_pinconf(E0 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE0_CHB_E1 :  iomuxc_pinconf(E1 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE1_CHA_B25:  iomuxc_pinconf(B25,ALT1,PWM_PIN_CONF); break;
        case PWM4_MODULE1_CHA_E2 :  iomuxc_pinconf(E2 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE1_CHB_E3 :  iomuxc_pinconf(E3 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE2_CHA_C30:  iomuxc_pinconf(C30,ALT1,PWM_PIN_CONF); break;
        case PWM4_MODULE2_CHA_E4 :  iomuxc_pinconf(E4 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE2_CHB_E5 :  iomuxc_pinconf(E5 ,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE3_CHA_C31:  iomuxc_pinconf(C31,ALT1,PWM_PIN_CONF); break;
        case PWM4_MODULE3_CHA_E17:  iomuxc_pinconf(E17,ALT1,PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE3_CHB_E18:  iomuxc_pinconf(E18,ALT1,PWM_PIN_CONF); break;

        default :assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM初始化
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_init(PWM1_MODULE0_CHB_D13, 50, 5000);     //初始化PWM1  子模块0 通道B 使用引脚D13  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000 
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWMCH_enum pwmch, uint32 freq, uint32 duty)
{
    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;
    uint32 temp_prsc;
    pwm_config_t pwmConfig;
    
    pwm_iomuxc(pwmch);

    //pwmConfig.enableDebugMode = false;
    //pwmConfig.enableWait = false;
    //pwmConfig.reloadSelect = kPWM_LocalReload;
    //pwmConfig.faultFilterCount = 0;
    //pwmConfig.faultFilterPeriod = 0;
    //pwmConfig.clockSource = kPWM_BusClock;
    //pwmConfig.prescale = kPWM_Prescale_Divide_1;
    //pwmConfig.initializationControl = kPWM_Initialize_LocalSync;
    //pwmConfig.forceTrigger = kPWM_Force_Local;
    //pwmConfig.reloadFrequency = kPWM_LoadEveryOportunity;
    //pwmConfig.reloadLogic = kPWM_ReloadImmediate;
    //pwmConfig.pairOperation = kPWM_Independent;

    PWM_GetDefaultConfig(&pwmConfig);

    pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;
    pwmConfig.pairOperation = kPWM_Independent;
    pwmConfig.enableDebugMode = true;
    

    //计算分频系数
    temp_prsc = (PWM_SRC_CLK_FREQ/freq)>>16;
	if(PWM_SRC_CLK_FREQ%(freq<<16))	temp_prsc++;

    if      (1   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_1;
    else if (2   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_2;
    else if (4   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_4;
    else if (8   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_8;
    else if (16  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_16;
    else if (32  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_32;
    else if (64  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_64;
    else if (128 >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_128;
    else
    {
        assert(0) ;//频率过小 或者IPG频率过高
    }

    pwm_num = pwmch/40;             //计算模块编号
    pwm_module = pwmch%40/10;       //计算子模块编号
    pwm_module_ch = pwmch%40%10/5;  //计算子模块的通道
    //初始化PWM模块 
    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)//第一次初始化便于打开时钟
    {
        assert(0) ;//初始化失败
    }
    PWM_Deinit(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module);
    
    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)//重新初始化设置正确的参数
    {
        assert(0) ;//初始化失败
    }

    //设置频率占空比等参数
    pwm_signal_param_t pwmSignal;

    pwmSignal.pwmChannel = (pwm_channels_t)(pwm_module_ch); 
    pwmSignal.level = kPWM_HighTrue;
    pwmSignal.dutyCyclePercent = duty;  //PWM_DUTY_MAX
    pwmSignal.deadtimeValue = 0;//((uint64_t)PWM_SRC_CLK_FREQ * 650) / 1000000000;

    //清除LOAD OKAY位  以设置新的参数
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_SetupPwm(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmSignal, 1, kPWM_EdgeAligned, freq, PWM_SRC_CLK_FREQ);     
    //设置LOAD OKAY位  以更新设置
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);

    //启动定时器
    PWM_StartTimer(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)));
    
    PWMPTR[pwm_num]->SM[pwm_module].DISMAP[0]=0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM占空比设置
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           +     //设置占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWMCH_enum pwmch, uint32 duty)
{
    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;
    
    pwm_num = pwmch/40;             //计算模块编号
    pwm_module = pwmch%40/10;       //计算子模块编号
    pwm_module_ch = pwmch%40%10/5;  //计算子模块的通道
    
    //清除LOAD OKAY位  以设置新的参数
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_UpdatePwmDutycycle(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, (pwm_channels_t)(pwm_module_ch), kPWM_EdgeAligned, duty);
    //设置LOAD OKAY位  以更新设置
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM频率设置
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_freq(PWM1_MODULE0_CHB_D13, 50);     //设置频率为50HZ   
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint32 duty)
{
    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;

    uint16 temp_prsc;
    pwm_config_t pwmConfig;

    PWM_GetDefaultConfig(&pwmConfig);

    pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;
    pwmConfig.pairOperation = kPWM_Independent;
    pwmConfig.enableDebugMode = true;
    
    //计算分频系数
    temp_prsc = (PWM_SRC_CLK_FREQ/freq)>>16;
    if      (1   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_1;
    else if (2   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_2;
    else if (4   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_4;
    else if (8   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_8;
    else if (16  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_16;
    else if (32  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_32;
    else if (64  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_64;
    else if (128 >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_128;
    else
    {
        assert(0) ;//频率过小 或者IPG频率过高
    }
    
    pwm_num = pwmch/40;             //计算模块编号
    pwm_module = pwmch%40/10;       //计算子模块编号
    pwm_module_ch = pwmch%40%10/5;  //计算子模块的通道
    
    //初始化PWM模块 
    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)
    {
        assert(0) ;//初始化失败
    }

    //设置频率占空比等参数
    pwm_signal_param_t pwmSignal;

    pwmSignal.pwmChannel = (pwm_channels_t)(pwm_module_ch); 
    pwmSignal.level = kPWM_HighTrue;
    pwmSignal.dutyCyclePercent = duty;  //PWM_DUTY_MAX
    pwmSignal.deadtimeValue = 0;//((uint64_t)PWM_SRC_CLK_FREQ * 650) / 1000000000;
    
    //清除LOAD OKAY位  以设置新的参数
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_SetupPwm(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmSignal, 1, kPWM_EdgeAligned, freq, PWM_SRC_CLK_FREQ);     
    //设置LOAD OKAY位  以更新设置
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);

    //启动定时器
    PWM_StartTimer(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)));
    
    PWMPTR[pwm_num]->SM[pwm_module].DISMAP[0]=0;
}

int32 motor1,motor2;
void leftforward(){
    gpio_set(D0,1);
	  gpio_set(D1,0);
}
void rightforward(){
    gpio_set(D12,1);
	  gpio_set(D13,0);
}
void leftbackward(){
    gpio_set(D0,0);
	  gpio_set(D1,1);
}
void rightbackward(){
    gpio_set(D12,0);
	  gpio_set(D13,1);
}
void leftbrake(){
    gpio_set(D0,0);
	  gpio_set(D1,0);
}
void rightbrake(){
    gpio_set(D12,0);
	  gpio_set(D13,0);
}

void motor_ctr(motor1,motor2)// set the speed to motor group 1&2
{
if(motor1>0){
				 pwm_duty(PWM2_MODULE3_CHA_D2, motor1);
				 leftforward();
}
else if (motor1==0){
         pwm_duty(PWM2_MODULE3_CHA_D2, motor1);
				 leftbrake();
}
else if (motor1<0){
         pwm_duty(PWM2_MODULE3_CHA_D2, -motor1);
				 leftbackward();
}
if(motor2>0){
         pwm_duty(PWM2_MODULE3_CHB_D3, motor2);
				 rightforward();
}
else if(motor2==0){
pwm_duty(PWM2_MODULE3_CHB_D3, motor2);
				 rightbrake();
}
else if(motor2<0){
pwm_duty(PWM2_MODULE3_CHB_D3, -motor2);
				 rightbackward();
}
}
//turn left part
void motor_TL1(speed){                          
     motor1=375*speed;
	   motor2=500*speed;
	   motor_ctr(motor1,motor2);
}
void motor_TL2(speed){
	   motor1=250*speed;
	   motor2=500*speed;
	   motor_ctr(motor1,motor2);
}
void motor_TL3(speed){
	   motor1=125*speed;
	   motor2=500*speed;
		 motor_ctr(motor1,motor2);
}
void motor_TL4(speed){
	   motor1=0;
	   motor2=500*speed;
		 motor_ctr(motor1,motor2);
}
void motor_TL5(speed){
	   motor1=-500*speed;
	   motor2=500*speed;
		 motor_ctr(motor1,motor2);
}
void motor_TL6(speed){
	   motor1=-250*speed;
	   motor2=500*speed;
		 motor_ctr(motor1,motor2);
}
//move forward & backward
void motor_MF(speed){
     motor1=500*speed;
	   motor2=500*speed;
	   motor_ctr(motor1,motor2);
}
void motor_MB(speed){
	   motor1=-500*speed;
	   motor2=-500*speed;
	   motor_ctr(motor1,motor2);
}
// turn right part
void motor_TR1(speed){
     motor1=500*speed;
	   motor2=375*speed;
	   motor_ctr(motor1,motor2);
}
void motor_TR2(speed){
     motor1=500*speed;
	   motor2=250*speed;
	   motor_ctr(motor1,motor2);
	 
}
void motor_TR3(speed){
     motor1=500*speed;
	   motor2=125*speed;
	   motor_ctr(motor1,motor2);
}
void motor_TR4(speed){
     motor1=500*speed;
	   motor2=0;
	   motor_ctr(motor1,motor2);
}
void motor_TR5(speed){
     motor1=500*speed;
	   motor2=-500*speed;
	   motor_ctr(motor1,motor2);
}
void motor_STP(){
	   motor1=0;
	   motor2=0;
	   motor_ctr(motor1,motor2);
}




//multi-state
// midpoint solution
/*
void automotor(speed,Xmidpoint,Ymidpoint,degree){



	   float turningparameter,multi;                           //16region ,ABCDEF direction w=160 h=120
	   float Xparameter,Dparameter;
	   int n;
	   //Y axis multi;
	   if(90<Ymidpoint&&Ymidpoint<=120){
		   multi=0.75;
		 }
		 else if(60<Ymidpoint&&Ymidpoint<=90){
		   multi=1;
		 }
		 else if(30<Ymidpoint&&Ymidpoint<=60){
		   multi=1.5;
		 }
		 else if(0<=Ymidpoint&&Ymidpoint<=30){
		   multi=2;
		 }
		 //X axis parameter;
	   if(120<Xmidpoint&&Xmidpoint<=160){
		   Xparameter=16;
		 }
		 else if(90<Xmidpoint&&Xmidpoint<=120){
		   Xparameter=1;
		 }
		 else if(70<=Xmidpoint&&Xmidpoint<=90){
		   Xparameter=0;
		 }
		 else if(40<Xmidpoint&&Xmidpoint<70){
		   Xparameter=-1;
		 }
		 else if(0<=Xmidpoint&&Xmidpoint<=40){
		   Xparameter=-16;
		 }
		 //degree parameter;
		 if(82<degree&&degree<=90){
		   Dparameter=0;
		 }
		 else if(60<degree&&degree<=82){
			 Dparameter=16;
		 }
		 else if(30<degree&&degree<=60){
			 Dparameter=30;
		 }
		 else if(0<degree&&degree<=30){
			 Dparameter=60;
		 }
		 else if(150<degree&&degree<=180){
			 Dparameter=-60;
		 }
		 else if(120<degree&&degree<=150){
			 Dparameter=-30;
		 }
		 else if(98<=degree&&degree<=120){
			 Dparameter=-16;
		 }
		 else if(90<=degree&&degree<98){
			 Dparameter=0;
		 }
		 //final equation
		 turningparameter=multi*Xparameter+Dparameter;
		 
		 //motor control -100~10
		 if(-100<=turningparameter&&turningparameter<=-50){
		   motor_TL5(25);
		 }
		 else if(-50<=turningparameter&&turningparameter<-40){
		   motor_TL4(50);
		 }
		 else if(-40<=turningparameter&&turningparameter<-30){
		   motor_TL3(70);
		 }
		 else if(-30<=turningparameter&&turningparameter<-20){
		   motor_TL2(80);
		 }
		 else if(-20<=turningparameter&&turningparameter<-10){
		   motor_TL1(90);
		 }
		 else if(-10<=turningparameter&&turningparameter<10){
		   motor_MF(100);
		 }
		 //motor control 10~100
		 else if(10<=turningparameter&&turningparameter<20){
		   motor_TR1(90);
		 }
		 else if(20<=turningparameter&&turningparameter<30){
		   motor_TR2(80);
		 }
		 else if(30<=turningparameter&&turningparameter<40){
		   motor_TR3(70);
		 }	 
		 else if(40<=turningparameter&&turningparameter<50){
		   motor_TR4(50);
		 } 
		 else if(50<=turningparameter&&turningparameter<=100){
		   motor_TR5(25);
		 }		 
	  	
	*/	 
		 
		 
		 

		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
		 
//		 
		 


//switch case solution
     /*for(n=1;n<9;n++){                           // midpoint on the x-axis
		 if(((Xmidpoint>=(25*(n-5)))&&((25*(n-4))>=Xmidpoint))){
			 region=n;
		 }

     switch(region){
			 case 1: //-100~-75
				 if(60<=degree&&degree<90){
					 leftmotor=25;
					 rightmotor=75;
				 }
				 else if(30<=degree&&degree<60){      //not exist
					 leftmotor=50;
					 rightmotor=50;
         }
				 else if(0<=degree&&degree<30){      //not exist
					 leftmotor=100;
					 rightmotor=25;
				 }
				 else if(-30<=degree&&degree<0){     //not exist
					 leftmotor=-50;
					 rightmotor=50;
         }
				 else if(-60<=degree&&degree<-30){   //not exist
					 leftmotor=0;
					 rightmotor=100;
				 }
				 else if(-90<=degree&&degree<-60){
					 leftmotor=0;
					 rightmotor=100;
				 }
			 break;
			 case 2:  //-75~-50
				 if(60<=degree&&degree<90){
					 leftmotor=50;
					 rightmotor=50;
				 }
				 else if(30<=degree&&degree<60){     //not exist

         }
				 else if(0<=degree&&degree<30){      //not exist

				 }
				 else if(-30<=degree&&degree<0){     //not exist
         }
				 else if(-60<=degree&&degree<-30){   //not exist
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 3:  //-50~-25
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 4:  //-25~0
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 5:  //0~25
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 6:  //25~50
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 7:  //50~75
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 case 8:  //75~100
				 if(60<=degree&&degree<90){
				 }
				 else if(30<=degree&&degree<60){
         }
				 else if(0<=degree&&degree<30){
				 }
				 else if(-30<=degree&&degree<0){
         }
				 else if(-60<=degree&&degree<-30){
				 }
				 else if(-90<=degree&&degree<-60){
				 }
			 break;
			 default:
				 
			 break;
		 }

		 
 		 if(leftmotor<0){
		 motor1=5*leftmotor*(0.3*speed-70);
		 }
		 else if(leftmotor==0){
		 motor1=0;
		 }
		 else if(leftmotor>0){
		 motor1=5*leftmotor*(0.3*speed+70);
		 }
     if(rightmotor<0){
		 motor2=5*rightmotor*(0.3*speed-70);
		 }
		 else if(rightmotor==0){
		 motor2=0;
		 }
		 else if(rightmotor>0){
		 motor2=5*rightmotor*(0.3*speed+70);
		 }
     motor_ctr(motor1,motor2);
		 */
//



//averagerow solution
/*
void automotor1(line1,line2,line3,line4,line5,line6,line7,line8){
     float leftthreshold=0.75;
	   float rightthreshold=0.6;
	   int leftparameter;
     int rightparameter;
	   leftparameter=0,rightparameter=0;
	   //left part
	   if((line1/line2)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line3)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line4)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line5)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line6)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line1/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line3)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line4)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line5)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line6)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line2/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line3/line4)<leftthreshold)
			 leftparameter+=1;
		 if((line3/line5)<leftthreshold)
			 leftparameter+=1;
		 if((line3/line6)<leftthreshold)
			 leftparameter+=1;
		 if((line3/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line3/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line4/line5)<leftthreshold)
			 leftparameter+=1;
		 if((line4/line6)<leftthreshold)
			 leftparameter+=1;
		 if((line4/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line4/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line5/line6)<leftthreshold)
			 leftparameter+=1;
		 if((line5/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line5/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line6/line7)<leftthreshold)
			 leftparameter+=1;
		 if((line6/line8)<leftthreshold)
			 leftparameter+=1;
		 if((line7/line8)<leftthreshold)
			 leftparameter+=1;
		 
		 
		 //right part
		 if((line8/line7)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line6)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line5)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line4)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line3)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line2)>rightthreshold)
			 rightparameter+=1;
		 if((line8/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line6)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line5)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line4)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line3)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line2)>rightthreshold)
			 rightparameter+=1;
		 if((line7/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line6/line5)>rightthreshold)
			 rightparameter+=1;
		 if((line6/line4)>rightthreshold)
			 rightparameter+=1;
		 if((line6/line3)>rightthreshold)
			 rightparameter+=1;
		 if((line6/line2)>rightthreshold)
			 rightparameter+=1;
		 if((line6/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line5/line4)>rightthreshold)
			 rightparameter+=1;
		 if((line5/line3)>rightthreshold)
			 rightparameter+=1;
		 if((line5/line2)>rightthreshold)
			 rightparameter+=1;
		 if((line5/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line4/line3)>rightthreshold)
			 rightparameter+=1;
     if((line4/line2)>rightthreshold)
			 rightparameter+=1;
     if((line4/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line3/line2)>rightthreshold)
			 rightparameter+=1;
		 if((line3/line1)>rightthreshold)
			 rightparameter+=1;
		 if((line2/line1)>rightthreshold)
			 rightparameter+=1;

		 
		 //control part
		 if(leftparameter<=4&&rightparameter<=4){
			 motor_MF(0);
			 systick_delay_ms(100);
			 motor_STP();
			 systick_delay_ms(100);
		 }
		 else{
		   if(4<leftparameter&&leftparameter<=10){
			 motor_TR2(-20);
		   systick_delay_ms(50);
		   motor_TR2(0);
		   systick_delay_ms(50);
       motor_STP();
       systick_delay_ms(100);			 
 		   }
		   else if(leftparameter>10){
			 motor_TR5(50);
		   systick_delay_ms(100);
       motor_STP();
       systick_delay_ms(100);
		 }
		 if(4<rightparameter&&rightparameter<=10){
			 motor_TL2(-20);
		   systick_delay_ms(50);
		   motor_TL2(0);
		   systick_delay_ms(50);
		   motor_STP();
			 systick_delay_ms(100);
		 }
		 else if(rightparameter>10){
			 motor_TR5(50);
		   systick_delay_ms(100);
       motor_STP();
       systick_delay_ms(100);
	 } 
}
}
*/
//



//avoid out of int range
int	 abs_minus(a,b){
	int result;
    if(a>b){
		result=a-b;
		}
		else if(b>=a){
		result=0;
		}
		return result;
}
	 
	 
	 
	 
	 
int automotor3(line1,line2,line3,line4,line5,line6,line7,line8){
   /*  //int leftthreshold=75;
	   //int rightthreshold=60;
	   //int leftparameter;
	   //int rightparameter;
		 //float av,fangcha;
		 //int fc;
	   //leftparameter=0;
	   //rightparameter=0;
		 //av=0.125*(line1+line2+line3+line4+line5+line6+line7+line8);
     //fangcha=(1/pow(av,2))*(pow(line1-av,2)+pow(line2-av,2)+pow(line3-av,2)+pow(line4-av,2)+pow(line5-av,2)+pow(line6-av,2)+pow(line7-av,2)+pow(line8-av,2));
		 //fc=fangcha;
		*/
		 //
		 int beacondetected=0;
	   int n;
		 int leftav,rightav;
		 leftav=0.25*(line1+line2+line3+line4);
		 rightav=0.25*(line5+line6+line7+line8);
if(beacondetected==0){
//add******************************************************************************************************************
	
	   //detect beacon
	   //then 'beacondetected=1;'
//add****************************************************************************************************************** 
/*	   if((abs_minus(rightav,line1))>12||(abs_minus(rightav,line2))>12)    //line1 line2 small
		 {
			 motor1=20000;
			 motor2=-20000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00001000;			 
		 }
		 else if((abs_minus(rightav,line3))>12||(abs_minus(rightav,line4))>12) //line3,line4 small
		 {		  
			 motor1=30000;
			 motor2=-30000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
		 if((abs_minus(leftav,line8))>18||(abs_minus(leftav,line7))>18){            //line7,line8 small
		   motor1=-20000;
			 motor2=50000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
		 else if((abs_minus(leftav,line5))>18||(abs_minus(leftav,line6)>18)){
		   motor1=-30000;
			 motor2=30000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);  
			 n=0x00000001;
		 }
		 else{
			 motor_MF(20);
			 systick_delay_ms(10);
			 n=0x00000000;
		 }
	 }
	 */		 
	 if(leftav>9+line5||leftav>9+line6){
		   motor1=-42000;
			 motor2=47000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);

		   
			 n=0x00000001;
		}
		 else if(leftav>9+line7||leftav>9+line8){            //line7,line8 small
		   motor1=-41000;
			 motor2=45000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
	 else if(rightav>12+line3||rightav>12+line4) //line3,line4 small
		 {		  
			 motor1=47000;
			 motor2=-42000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);

       n=0x00001000;			 
		 }
	 else if(rightav>12+line1||rightav>12+line2)    //line1 line2 small
		 {
			 motor1=45000;
			 motor2=-41000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
    
		 
		 else{
			 motor_MF(71);
			 systick_delay_ms(160);
			 motor_STP();
			 systick_delay_ms(120);
			 
			 n=0x00000000;
		 }
 }
	 
		 return n;
	 //return beacondetected;
	 } 
//
	 
	 
	 
// 
int automotor4(line1,line2,line3,line4,line5,line6,line7,line8){
   /*  //int leftthreshold=75;
	   //int rightthreshold=60;
	   //int leftparameter;
	   //int rightparameter;
		 //float av,fangcha;
		 //int fc;
	   //leftparameter=0;
	   //rightparameter=0;
		 //av=0.125*(line1+line2+line3+line4+line5+line6+line7+line8);
     //fangcha=(1/pow(av,2))*(pow(line1-av,2)+pow(line2-av,2)+pow(line3-av,2)+pow(line4-av,2)+pow(line5-av,2)+pow(line6-av,2)+pow(line7-av,2)+pow(line8-av,2));
		 //fc=fangcha;
		*/
		 //
		 int beacondetected=0;
	   int n;
		 int leftav,rightav;
		 leftav=0.25*(line1+line2+line3+line4);
		 rightav=0.25*(line5+line6+line7+line8);
if(beacondetected==0){
//add******************************************************************************************************************
	
	   //detect beacon
	   //then 'beacondetected=1;'
//add****************************************************************************************************************** 
/*	   if((abs_minus(rightav,line1))>12||(abs_minus(rightav,line2))>12)    //line1 line2 small
		 {
			 motor1=20000;
			 motor2=-20000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00001000;			 
		 }
		 else if((abs_minus(rightav,line3))>12||(abs_minus(rightav,line4))>12) //line3,line4 small
		 {		  
			 motor1=30000;
			 motor2=-30000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
		 if((abs_minus(leftav,line8))>18||(abs_minus(leftav,line7))>18){            //line7,line8 small
		   motor1=-20000;
			 motor2=50000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
		 else if((abs_minus(leftav,line5))>18||(abs_minus(leftav,line6)>18)){
		   motor1=-30000;
			 motor2=30000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);  
			 n=0x00000001;
		 }
		 else{
			 motor_MF(20);
			 systick_delay_ms(10);
			 n=0x00000000;
		 }
	 }
	 */		 
	 if(line5<10||line6<10){
		   motor1=-42000;
			 motor2=47000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);

		   
			 n=0x00000001;
		}
		 else if(line7<10||line8<10){            //line7,line8 small
		   motor1=-41000;
			 motor2=45000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
	 else if(line3<8||line4<8) //line3,line4 small
		 {		  
			 motor1=47000;
			 motor2=-42000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);

       n=0x00001000;			 
		 }
	 else if(line1<8||line2<8)    //line1 line2 small
		 {
			 motor1=45000;
			 motor2=-41000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
    
		 
		 else{
			 motor_MF(71);
			 systick_delay_ms(160);
			 motor_STP();
			 systick_delay_ms(120);
			 
			 n=0x00000000;
		 }
 }
	 
		 return n;
	 //return beacondetected;
	 } 
//
	 
	 void motor(x,y){
		  motor1=x;
			motor2=y;
			motor_ctr(motor1,motor2);			
		}

		
		
	int automotor5(line1,line2,line3,line4,line5,line6,line7,line8){
   /*  //int leftthreshold=75;
	   //int rightthreshold=60;
	   //int leftparameter;
	   //int rightparameter;
		 //float av,fangcha;
		 //int fc;
	   //leftparameter=0;
	   //rightparameter=0;
		 //av=0.125*(line1+line2+line3+line4+line5+line6+line7+line8);
     //fangcha=(1/pow(av,2))*(pow(line1-av,2)+pow(line2-av,2)+pow(line3-av,2)+pow(line4-av,2)+pow(line5-av,2)+pow(line6-av,2)+pow(line7-av,2)+pow(line8-av,2));
		 //fc=fangcha;
		*/
		 //
		 int beacondetected=0;
	   int n;
		 int leftav,rightav;
		 leftav=0.25*(line1+line2+line3+line4);
		 rightav=0.25*(line5+line6+line7+line8);
if(beacondetected==0){
//add******************************************************************************************************************
	
	   //detect beacon
	   //then 'beacondetected=1;'
//add****************************************************************************************************************** 
/*	   if((abs_minus(rightav,line1))>12||(abs_minus(rightav,line2))>12)    //line1 line2 small
		 {
			 motor1=20000;
			 motor2=-20000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00001000;			 
		 }
		 else if((abs_minus(rightav,line3))>12||(abs_minus(rightav,line4))>12) //line3,line4 small
		 {		  
			 motor1=30000;
			 motor2=-30000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
		 if((abs_minus(leftav,line8))>18||(abs_minus(leftav,line7))>18){            //line7,line8 small
		   motor1=-20000;
			 motor2=50000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
		 else if((abs_minus(leftav,line5))>18||(abs_minus(leftav,line6)>18)){
		   motor1=-30000;
			 motor2=30000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);  
			 n=0x00000001;
		 }
		 else{
			 motor_MF(20);
			 systick_delay_ms(10);
			 n=0x00000000;
		 }
	 }
	 */		 
	 if(leftav>6+line5||leftav>6+line6){
		   motor1=-42000;
			 motor2=47000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);

		   
			 n=0x00000001;
		}
		 else if(leftav>6+line7||leftav>6+line8){            //line7,line8 small
		   motor1=-41000;
			 motor2=45000;
			 motor_ctr(motor1,motor2);
			 systick_delay_ms(10);
       n=0x00000010;			 
		 }
	 else if(rightav>6+line3||rightav>6+line4) //line3,line4 small
		 {		  
			 motor1=47000;
			 motor2=-42000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);

       n=0x00001000;			 
		 }
	 else if(rightav>6+line1||rightav>6+line2)    //line1 line2 small
		 {
			 motor1=45000;
			 motor2=-41000;
			 motor_ctr(motor1,motor2);
       systick_delay_ms(10);
       n=0x00000100;			 
		 }
    
		 
		 else{
			 motor_MF(71);
			 systick_delay_ms(160);
			 motor_STP();
			 systick_delay_ms(120);
			 
			 n=0x00000000;
		 }
 }
	 
		 return n;
	 //return beacondetected;
	 } 
//
		
		
		
		
		
		
		
	