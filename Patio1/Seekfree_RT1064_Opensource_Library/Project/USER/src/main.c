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
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本


//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的

#include "headfile.h"
#include "SEEKFREE_ICM20602.h"
#include "gyroscope.h"

#ifndef M_PI 
#define M_PI 3.14159265358979323846264338327950288f 
#endif 
extern eulerianAngles_t eulerAngle;
float *turneddegree;
float motor_TLdegree(degree){                       //must be 45
     float tempdegree,startdegree;                      
	   int n1;
	   clearEuler();
	   gpio_set(B21,1);
		 icm20602_init_hardware();
	   systick_delay_ms(200);
	   get_direction();
	   startdegree=eulerAngle.yaw;
	   tempdegree=eulerAngle.yaw;  
	   *turneddegree=tempdegree-startdegree;    //turned=temp-start  positive is turnleft, negative is turnright 
	   systick_delay_us(4500);
	   while(degree-*turneddegree>3||degree-*turneddegree<3){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	     *turneddegree=tempdegree-startdegree;
	       if(degree-*turneddegree>3||*turneddegree-degree>=3){
					 if(degree-*turneddegree>3){
				   motor_TL5(100);
	         systick_delay_us(4500);
		       }
		       else if(degree-*turneddegree<3){
		       motor_TR5(100);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (degree-*turneddegree<3&&*turneddegree-degree<3){
					 motor_STP();
					 systick_delay_us(4500);
					 n1+=1;
					 if(n1>400){
					 break;
					 }
				 }
				 
		 }
	
		 motor_STP();
		 gpio_set(B21,0);
		 systick_delay_ms(50);
		 clearEuler();
		 return *turneddegree;
	 }
float motor_TRdegree(degree){                       //must be -45
     float tempdegree,startdegree;                      
	   int n2;
	   clearEuler();
	   gpio_set(B21,1);
		 icm20602_init_hardware();
	   systick_delay_ms(200);
	   get_direction();
	   startdegree=eulerAngle.yaw;
	   tempdegree=eulerAngle.yaw;  
	   *turneddegree=tempdegree-startdegree;    //turned=temp-start  positive is turnleft, negative is turnright 
	   systick_delay_us(4500);
	   while(degree-*turneddegree<-3||degree-*turneddegree>-3){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	     *turneddegree=tempdegree-startdegree;
	       if(degree-*turneddegree<-3||degree-*turneddegree >3){
					 if(degree-*turneddegree<-3){
				   motor_TR5(100);
	         systick_delay_us(4500);
		       }
		       else if(degree-*turneddegree>3){
		       motor_TL5(100);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (degree-*turneddegree>=-3&&degree-*turneddegree <=3){
					 motor_STP();
					 systick_delay_us(4500);
					 n2+=1;
					 if(n2>400){
					 break;
					 }
				 }
				 
		 }
	
		 motor_STP();
		 gpio_set(B21,0);
		 systick_delay_ms(50);
		 clearEuler();
		 return *turneddegree;
	 }
float motor_GOstraight(gotime){                       // unit of gotime is ms;
     float tempdegree,startdegree;
     int steps,n3;
     steps=gotime/4.5;
	   clearEuler();
	   gpio_set(B21,1);
		 icm20602_init_hardware();
	   systick_delay_ms(2000);
	   get_direction();
	   startdegree=0;
	   tempdegree=0;  
	   *turneddegree=tempdegree-startdegree;    //turned=temp-start  positive is turnleft, negative is turnright 
	   systick_delay_us(4500);
	   for(n3=0;n3<steps;n3++){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	     *turneddegree=tempdegree-startdegree;
	       if(*turneddegree>3||*turneddegree<-3)
				 {
					 if(*turneddegree>3)
					 {
				   motor_TR3(100);
	         systick_delay_us(4500);
		       }
		       else if(*turneddegree<-3)
					 {
		       motor_TL3(100);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (*turneddegree<3&&*turneddegree>-3)
				 {
					 motor_MF(75);
					 systick_delay_us(4500);
				 }
				 
		 }
	
		 motor_STP();
		 gpio_set(B21,0);
		 systick_delay_ms(50);
		 clearEuler();
		 return *turneddegree;
	 }


uint8 example_rx_buffer;
lpuart_transfer_t   openmv_state;
lpuart_handle_t     openmv_handle;
//uint8 Xmidpoint,Ymidpoint,degree;
uint8 uart_data,openmv_data;
int line1,line2,line3,line4,line5,line6,line7,line8;
uint8 digit1,digit2,digit3,digit4,digit5,digit6,digit7,digit8,digit9,digit10,digit11,digit12,digit13,digit14,digit15,digit16;
uint8 *globalstatus;
uint8 callbackcounter=0;
int testleft;
int pp;

void example_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
     
        //数据已经被写入到了 之前设置的BUFF中
        //本例程使用的BUFF为 example_rx_buffer
        openmv_data = example_rx_buffer;//将数据取出
			//globalstatus 1 find line   ASCII (int)=(char)-48
			
			if(callbackcounter<16){
        if(callbackcounter==0)
					digit1=openmv_data;
				if(callbackcounter==1){
					digit2=openmv_data;
				line1=10*(digit1-48)+(digit2-48);}
				if(callbackcounter==2)
					digit3=openmv_data;
				if(callbackcounter==3){
					digit4=openmv_data;
				line2=10*(digit3-48)+(digit4-48);}
				if(callbackcounter==4)
					digit5=openmv_data;
        if(callbackcounter==5){
					digit6=openmv_data;
      line3=10*(digit5-48)+(digit6-48);}
				if(callbackcounter==6)
					digit7=openmv_data;
				if(callbackcounter==7){
					digit8=openmv_data;
				line4=10*(digit7-48)+(digit8-48);}
        if(callbackcounter==8)
					digit9=openmv_data;
				if(callbackcounter==9){
					digit10=openmv_data;
				line5=10*(digit9-48)+(digit10-48);}
				if(callbackcounter==10)
					digit11=openmv_data;
				if(callbackcounter==11){
					digit12=openmv_data;
				line6=10*(digit11-48)+(digit12-48);}
				if(callbackcounter==12)
					digit13=openmv_data;
				if(callbackcounter==13){
					digit14=openmv_data;
				line7=10*(digit13-48)+(digit14-48);}
				if(callbackcounter==14)
					digit15=openmv_data;
				if(callbackcounter==15){
					digit16=openmv_data;
				line8=10*(digit15-48)+(digit16-48);}
				
			  callbackcounter+=1;}
			else{ 
				callbackcounter=0;
				digit1=openmv_data;
				callbackcounter+=1;
			}
			
			
			
			
			
			
		}
    
    handle->rxDataSize = openmv_state.dataSize;  //还原缓冲区长度
    handle->rxData = openmv_state.data;          //还原缓冲区地址
}


char uart_send;
			

/////////////ultra
#define trig_front B13              
#define echo_front B15
#define trig_right B2             
#define echo_right B3

#define trig_left1 B0      
#define echo_left1 B1
#define trig_left2 B12          
#define echo_left2 B14

int dis1=0;  
int dis2=0;  
int dis3=0;  
int dis4=0; 
float dif=0;

long wait_time1 = 0;   
long wait_time2 = 0;  
long wait_time3 = 0; 
long wait_time4 = 0; 
uint32 distance_time1 = 0; 
uint32 distance_time2 = 0;
uint32 distance_time3 = 0;
uint32 distance_time4 = 0;
int good_dir=0;
int good_direction=0;
		
int state=9;                        //////////////
int dist[5];
int iii;int sum; int avg;

int dis_front(){
			pit_init(); 
			gpio_set(trig_front,1);                           
      systick_delay_us(10);                           
      gpio_set(trig_front,0);          
      while(!gpio_get(echo_front));                     
      pit_start(PIT_CH0); 
      wait_time1 = 0;  
      while(gpio_get(echo_front))   
      {  
          wait_time1++;                                 
          systick_delay(5);  
          if(wait_time1>200000) break;                 
      }  				
      if(wait_time1<200000)  distance_time1 = pit_get_us(PIT_CH0); 
      else                  distance_time1 = 200000;  
      pit_close(PIT_CH0); 
			systick_delay_ms(10);
      return distance_time1/58;    //cm				  
	}

int dis_right(){ 
			pit_init(); 
			gpio_set(trig_right,1);                           
      systick_delay_us(10);                           
      gpio_set(trig_right,0);          
      while(!gpio_get(echo_right));                     
      pit_start(PIT_CH1); 
      wait_time2 = 0;  
      while(gpio_get(echo_right))   
      {  
          wait_time2++;                                 
          systick_delay(5);  
          if(wait_time2>200000) break;                 
      }  				
      if(wait_time2<200000)  distance_time2 = pit_get_us(PIT_CH1); 
      else                   distance_time2 = 200000;  
      pit_close(PIT_CH1); 
			systick_delay_ms(10);
      return distance_time2/58;    //cm				  
	}

float dis_left1(){
			pit_init(); 
			gpio_set(trig_left1,1);                           
      systick_delay_us(10);                           
      gpio_set(trig_left1,0);          
      while(!gpio_get(echo_left1));                     
      pit_start(PIT_CH2); 
      wait_time3 = 0;  
      while(gpio_get(echo_left1))   
      {  
          wait_time3++;                                 
          systick_delay(5);  
          if(wait_time3>200000) break;                 
      }  				
      if(wait_time3<200000)  distance_time3 = pit_get_us(PIT_CH2); 
      else                   distance_time3 = 200000;  
      pit_close(PIT_CH2); 
			systick_delay_ms(10);
      return distance_time3/58;    //cm				  
	}

float dis_left2(){
			pit_init(); 
			gpio_set(trig_left2,1);                           
      systick_delay_us(10);                           
      gpio_set(trig_left2,0);          
      while(!gpio_get(echo_left2));                     
      pit_start(PIT_CH3); 
      wait_time4 = 0;  
      while(gpio_get(echo_left2))   
      {  
          wait_time4++;                                 
          systick_delay(5);  
          if(wait_time4>200000) break;                 
      }  				
      if(wait_time4<200000)  distance_time4 = pit_get_us(PIT_CH3); 
      else                   distance_time4 = 200000;  
      pit_close(PIT_CH3); 
			systick_delay_ms(10);
      return distance_time4/58;    //cm				  
	}


int ave(distance){
	iii=0;
	int dist[5]={0,0,0,0,0};
	sum=0;avg=0;
	while(iii<5){
		dist[iii]=distance;
		sum=sum+dist[iii];
		iii+=1;
	}
	avg=sum/5;
	return avg;
}
	
int main(void)
{
	  DisableGlobalIRQ();
    board_init(); //Initializing 
    systick_delay_ms(300);
		gpio_init( B21 , GPO, 0, GPIO_PIN_CONFIG);  //gyroscope init

// Motor group
	  gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);	       //IN1   positive
	  gpio_init(D1, GPO, 1, GPIO_PIN_CONFIG);        //IN2   negative
    gpio_init(D12, GPO, 1, GPIO_PIN_CONFIG);       //IN3   positive
	  gpio_init(D13, GPO, 1, GPIO_PIN_CONFIG);       //IN4   negative                                                
		pwm_init(PWM2_MODULE3_CHA_D2,17000,0); //D2 motor1(left) //enalbe a    maximum duty cycle is defined as 50000                                            
		pwm_init(PWM2_MODULE3_CHB_D3,17000,0); //D3 motor2(right)   //enable b                                      
	  systick_delay_ms(500);	
		
	  //ultrasonic
	  gpio_init(trig_front, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_front, GPI, 0, GPIO_PIN_CONFIG); 
	  gpio_init(trig_right, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_right, GPI, 0, GPIO_PIN_CONFIG); 
		gpio_init(trig_left1, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_left1, GPI, 0, GPIO_PIN_CONFIG); 
		gpio_init(trig_left2, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_left2, GPI, 0, GPIO_PIN_CONFIG);
		pit_init();
	
		//初始换串口   波特率为115200 TX为D16 RX为D17
		uart_init(USART_8,115200,UART8_TX_D16,UART8_RX_D17);
		NVIC_SetPriority(LPUART8_IRQn,2);  //设置串口中断优先级 范围0-15 越小优先级越高
    uart_rx_irq(USART_8,1);
		//配置串口接收的缓冲区及缓冲区长度
		openmv_state.dataSize = 1;
    openmv_state.data = &example_rx_buffer;
    
    //设置中断函数及其参数
    uart_set_handle(USART_8, &openmv_handle, example_uart_callback, NULL, 0, openmv_state.data, 1);
    
    EnableGlobalIRQ(0);
		*globalstatus=3;
    while(1){
			
			
			systick_delay_ms(100);
			
			
      while(*globalstatus==1){
			dis1=ave(dis_front());
				if(dis1>30){
			pp=automotor3(line3,line3,line3,line4,line5,line6,line6,line6);  //leftaverage rightaverage;
      //pp=automotor4(line1,line2,line3,line4,line5,line6,line7,line8);     //simple left two , midleft two, midright two, right two
			//if(qian mian de chao sheng bo==1){*globalstatus=2};
				}
				else if (dis1<30){
					*globalstatus = 2;					
				}
				
			}
					
			
		   while (*globalstatus==2){
				  dis1=ave(dis_front());
					
			  if(dis1<25){
				motor_STP();systick_delay_ms(1000);
				motor_TRdegree(-45);				systick_delay_ms(500);
				motor_TRdegree(-45);				systick_delay_ms(500);
				
				dif=dis_left1()-dis_left2();
				
				while(good_dir==0){                          //adjust dirction
					dif=dis_left1()-dis_left2();
					
					if(dif>3){
						motor_TL5(85);systick_delay_ms(50);
					}
					else if(dif<-3){
						motor_TR5(85);systick_delay_ms(50);
					}
					else if(dif>0.5&&dif<3){
						motor_TL5(85);systick_delay_ms(12);
					}
					else if(dif>-3&&dif<-0.5){
						motor_TR5(85);systick_delay_ms(10);
					}
					else if(abs(dif)<0.5){
						good_dir=1;systick_delay_ms(10);
					}
					else{
						motor_MF(70); systick_delay_ms(50);
						motor_STP(); systick_delay_ms(50);
					}
				}
				motor_STP();systick_delay_ms(1000);    
				motor_GOstraight(10000);          //cross the bridge
				motor_STP();systick_delay_ms(100);
				*globalstatus=3;
				good_dir=1;
			}
			else{
				motor_MF(75); systick_delay_ms(100);
				motor_STP(); systick_delay_ms(50);
				
			}	
				systick_delay_ms(100);
		}
			 
		while(*globalstatus==3){                         // after bridge stop before beacon/wall and turn left   (patio1)
			dis1=ave(dis_front());
					
			if(dis1<25){
				systick_delay_ms(1000);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				motor_TLdegree(60);
				motor_MF(75); systick_delay_ms(500);
				*globalstatus=4;
			}
			else{
				motor_MF(75); systick_delay_ms(200);
				motor_STP();	systick_delay_ms(50);
			}	
				systick_delay_ms(100);
		}
		
		while(*globalstatus==4){
			dis2=ave(dis_right());
			dis3=ave(dis_left1());
				if(dis2>20&&dis3>20){
			pp=automotor5(line2,line2,line3,line4,line5,line6,line7,line7);  //leftaverage rightaverage;
      //pp=automotor4(line1,line2,line3,line4,line5,line6,line7,line8);     //simple left two , midleft two, midright two, right two
			//if(qian mian de chao sheng bo==1){*globalstatus=2};
				}
				else  {
				  motor_MF(75); systick_delay_ms(1500);
				  motor_STP();	systick_delay_ms(50);		
					*globalstatus=5;
				}
				
			}
		motor_STP();
				 
				 
				 
				 
				 
				 
			 }








			
    }

  
	
	