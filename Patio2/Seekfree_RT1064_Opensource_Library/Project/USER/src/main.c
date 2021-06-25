
#include "DS1302.h"
#include "stdio.h"
#include "headfile.h"
#include "gyroscope.h"

#ifndef M_PI 
#define M_PI 3.14159265358979323846264338327950288f 
#endif 
extern eulerianAngles_t eulerAngle;
float *turneddegree;
int *stop;

uint8 global_status=4;   ////5//////////////////////////////////////////////

DS1302_Time ds1302_time = {2021, 6, 20, 9, 44, 0, 0}; // Year, Month, Date, Hour, Minute, Second, Day
DS1302 ds1302 = {
		C5, // SCL_PIN
		C6, // SDA_PIN
		C7, // RST_PIN
};


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
	   systick_delay_ms(500);
	   get_direction();
	   startdegree=0;
	   tempdegree=0;  
	   *turneddegree=tempdegree-startdegree;    //turned=temp-start  positive is turnleft, negative is turnright 
	   systick_delay_us(4500);
	   for(n3=0;n3<steps;n3++){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	     *turneddegree=tempdegree-startdegree;
	       if(*turneddegree>2||*turneddegree<-2)
				 {
					 if(*turneddegree>2)
					 {
				   motor_TR3(100);
	         systick_delay_us(4500);
		       }
		       else if(*turneddegree<-2)
					 {
		       motor_TL3(90);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (*turneddegree<2&&*turneddegree>-2)
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



float motor_abTLdegree(){                       // turn left 90 degree
     float tempdegree,startdegree;                      
	   int n1;
	   gpio_set(B21,1);
		 icm20602_init_hardware();
	   systick_delay_ms(200);
	   get_direction();
	   startdegree=eulerAngle.yaw;
	   tempdegree=eulerAngle.yaw;  
	   systick_delay_us(4500);
	   while(tempdegree<93){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	       if(tempdegree<87||tempdegree>93){
					 if(tempdegree<87){
				   motor_TL5(100);
	         systick_delay_us(4500);
		       }
		       else if(tempdegree>93){
		       motor_TR5(100);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (tempdegree>=87&&tempdegree<=93){
					 motor_STP();
					 systick_delay_us(4500);
					 n1+=1;
					 if(n1>400){
					 break;
					 }
				 }
				 
		 }
	
		 motor_STP();
		 systick_delay_ms(50);
		 return 0;
	 }

float motor_abGOstraight(gotime){                       // unit of gotime is ms; using absolute degree 90 
     float tempdegree,startdegree;
     int steps,n3;
     steps=gotime/4.5;
	   systick_delay_ms(1000);
	   get_direction();
	   systick_delay_us(4500);
	   for(n3=0;n3<steps;n3++){
			 get_direction();
			 tempdegree=eulerAngle.yaw;
	       if(tempdegree>93|tempdegree<87)
				 {
					 if(tempdegree>93)
					 {
				   motor_TR3(100);
	         systick_delay_us(4500);
		       }
		       else if(tempdegree<87)
					 {
		       motor_TL3(100);
	         systick_delay_us(4500);
		       }
			   }	 
				 else if (tempdegree<=93&&tempdegree>=87)
				 {
					 motor_MF(75);
					 systick_delay_us(4500);
				 }
				 
		 }
	
		 motor_STP();
		 gpio_set(B21,0);
		 systick_delay_ms(50);
		 clearEuler();
		 return 0;
	 }
	 uint8 example_rx_buffer;
lpuart_transfer_t   openmv_state;
lpuart_handle_t     openmv_handle;
uint8 Xmidpoint,Ymidpoint,degree;
int line1,line2,line3,line4,line5,line6,line7,line8;
uint8 digit1,digit2,digit3,digit4,digit5,digit6,digit7,digit8,digit9,digit10,digit11,digit12,digit13,digit14,digit15,digit16;
uint8 openmv_data;
uint8 callbackcounter=0;	 
int temp_color=0;
int temp_xyz=0;
int MODE;


void example_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
     
        //Êý¾ÝÒÑ¾­±»Ð´Èëµ½ÁË Ö®Ç°ÉèÖÃµÄBUFFÖÐ
        //±¾Àý³ÌÊ¹ÓÃµÄBUFFÎª example_rx_buffer
        openmv_data = example_rx_buffer;//½«Êý¾ÝÈ¡³ö
	
			
    
    handle->rxDataSize = openmv_state.dataSize;  //»¹Ô­»º³åÇø³¤¶È
    handle->rxData = openmv_state.data;          //»¹Ô­»º³åÇøµØÖ·
}}



int color_recognition_a(int mode) //2 red,1 green, 4 blue
	{
		while(mode==2)//red
			{
				motor_STP();
				systick_delay_ms(200);
				motor_TLdegree(45);
				systick_delay_ms(500);
			 
								
				return 0;
					
					}
		while(mode==1)//green
			{
				motor_STP();	
        systick_delay_ms(200);				
				motor_TLdegree(45);
				systick_delay_ms(1000);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				
				
					return 0;
			}
		while(mode==4)//blue
			{
				motor_STP();
				systick_delay_ms(200);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				
					
					return 0;
			}
		}

		void color_recognition_b(int mode)
	{
		if(mode==2)//red
			{
				motor_STP();
				systick_delay_ms(200);
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				
			}
		if(mode==1)//green
			{
				motor_STP();
				systick_delay_ms(200);
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				motor_GOstraight(4000);
			}
		if(mode==4)//blue
			{
				motor_STP();
				systick_delay_ms(200);
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				
				motor_GOstraight(6000);
				
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				motor_TRdegree(-45);       ///////////////
				systick_delay_ms(500);
				
				motor_GOstraight(7000);
				
			}
		}
char uart_send;
		
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
	  //ultrasonic
	  gpio_init(trig_front, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_front, GPI, 0, GPIO_PIN_CONFIG); 
	  gpio_init(trig_right, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_right, GPI, 0, GPIO_PIN_CONFIG); 
		gpio_init(trig_left1, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_left1, GPI, 0, GPIO_PIN_CONFIG); 
		gpio_init(trig_left2, GPO, 0, GPIO_PIN_CONFIG);  
    gpio_init(echo_left2, GPI, 0, GPIO_PIN_CONFIG);
	  gpio_init(B21, GPO, 0, GPIO_PIN_CONFIG);
	  
	  // Motor group
	  gpio_init(D0, GPO, 1, GPIO_PIN_CONFIG);	       //IN1   positive
	  gpio_init(D1, GPO, 1, GPIO_PIN_CONFIG);        //IN2   negative
    gpio_init(D12, GPO, 1, GPIO_PIN_CONFIG);       //IN3   positive
	  gpio_init(D13, GPO, 1, GPIO_PIN_CONFIG);       //IN4   negative                                                
		pwm_init(PWM2_MODULE3_CHA_D2,17000,0); //D2 motor1(left) //enalbe a    maximum duty cycle is defined as 50000                                            
		pwm_init(PWM2_MODULE3_CHB_D3,17000,0); //D3 motor2(right)   //enable b                                      
	  systick_delay_ms(500);	
		
		//steering machine
	  pwm_init(PWM1_MODULE1_CHA_D14, 50, 1250);
	  systick_delay_ms(1000);
	
	   pit_init();
      //main function
			EnableGlobalIRQ(0);
			
				
		//³õÊ¼»»´®¿Ú   ²¨ÌØÂÊÎª115200 TXÎªD16 RXÎªD17
		uart_init(USART_8,115200,UART8_TX_D16,UART8_RX_D17);
		NVIC_SetPriority(LPUART8_IRQn,2);  //ÉèÖÃ´®¿ÚÖÐ¶ÏÓÅÏÈ¼¶ ·¶Î§0-15 Ô½Ð¡ÓÅÏÈ¼¶Ô½¸ß
    uart_rx_irq(USART_8,1);
		//ÅäÖÃ´®¿Ú½ÓÊÕµÄ»º³åÇø¼°»º³åÇø³¤¶È
		openmv_state.dataSize = 1;
    openmv_state.data = &example_rx_buffer;
    
    //ÉèÖÃÖÐ¶Ïº¯Êý¼°Æä²ÎÊý
    uart_set_handle(USART_8, &openmv_handle, example_uart_callback, NULL, 0, openmv_state.data, 1);
    
    EnableGlobalIRQ(0);
   
		while (1)
			{
		if(global_status==4){
			motor_GOstraight(3500);
				while(temp_color==0){					
					if(openmv_data==50)
						{
							MODE=2;
							motor_GOstraight(500);
							motor_STP();
							systick_delay_ms(200);
							MODE=color_recognition_a(MODE);
							motor_GOstraight(900);
							temp_color=1;
							
						}
					else if(openmv_data==49)
						{
							MODE=1;
							motor_GOstraight(500);
							motor_STP();
							systick_delay_ms(200);
							MODE=color_recognition_a(MODE);
							motor_GOstraight(900);
							temp_color=1;
						}
					else if(openmv_data==52)
						{
							MODE=4;
							motor_GOstraight(500);
							motor_STP();
							systick_delay_ms(200);
							MODE=color_recognition_a(MODE);
							motor_GOstraight(900);
							temp_color=1;
						}
					else
						{
							
							motor_GOstraight(200);
							motor_STP();
							systick_delay_ms(50);
						}
			}
				systick_delay_ms(1000);
			motor_GOstraight(4000);
			while(temp_color==1){
					if(openmv_data==50)
						{
							motor_GOstraight(900);
							motor_STP();
							systick_delay_ms(200);
							color_recognition_b(2);
							temp_color=2;
						}
					else if(openmv_data==49)
						{
							motor_GOstraight(900);
							motor_STP();
							systick_delay_ms(200);
							color_recognition_b(1);
							temp_color=2;
						}
					else if(openmv_data==52)
						{
							motor_GOstraight(900);
							motor_STP();
							systick_delay_ms(200);
							color_recognition_b(4);
							temp_color=2;
						}
					else
						{
							motor_GOstraight(200);
							
							systick_delay_ms(50);
						}
			}
			
			motor_STP();
			systick_delay_ms(2000);
			global_status=5;
			}	
        
				
			
	  
			
	  while(global_status==5){                         // stop before wall and turn left   (patio2)

		  dis1=ave(dis_front());
					
			if(dis1<30){
				motor_STP();systick_delay_ms(1000);
				motor_TLdegree(45);          ////////////////////////////////////////////
				systick_delay_ms(1000);
				motor_TLdegree(45);
				
				motor_STP();systick_delay_ms(1000);
				
				global_status=6;
			}
			else{
				motor_MF(85);
				systick_delay_ms(100);
				motor_STP();
				systick_delay_ms(100);
			}	
				systick_delay_ms(100);
		}

    
		while(global_status==6){                         // move along the handrill righthand       (patio2)
			
			dis2=ave(dis_right());
			dis1=ave(dis_front());	
			dis3=ave(dis_left1());
			dis4=ave(dis_left2());
			
			if (dis4<30){                            //stop before left beacon, then feeding
				motor_STP();systick_delay_ms(1000);
			
				motor_GOstraight(1000);
			  motor_STP();    systick_delay_ms(500);
			  motor_TLdegree(45);            ////////////////////////////////////////////
				systick_delay_ms(1000);
				motor_TLdegree(45);
				systick_delay_ms(1000);
				motor_MB(70);systick_delay_ms(800);
				motor_STP();    systick_delay_ms(100);
				global_status=7;
			}
			
			else if(dis2>250){                                // turn right at coner
				
				//motor_TR4(100);systick_delay_ms(1200);
				motor_TRdegree(-45);				motor_GOstraight(1000);	
				motor_STP();systick_delay_ms(500);					
			}
			
			else if(dis1<60){                                 // turn left before wall
				motor_STP();systick_delay_ms(1000);
				motor_TLdegree(45);            ////////////////////////////////////////////
				systick_delay_ms(500);
				motor_TLdegree(45);
				systick_delay_ms(500);
				motor_STP();systick_delay_ms(100);				
			}
			
			else if(dis2<30){
				motor_TL3(100);
				systick_delay_ms(300);
				motor_TR2(70);
				systick_delay_ms(90);
			}
			else if(dis2>30&&dis2<36){
				motor_MF(80);
				systick_delay_ms(100);
			}
			else if(dis2>36&&dis2<50){
				motor_TR3(100);
				systick_delay_ms(200);
				motor_TL2(80);
				systick_delay_ms(150);
			}
			else if(dis2>50&&dis2<150){
				motor_TR4(100);
				systick_delay_ms(240);
				motor_TL3(85);
				systick_delay_ms(100);
			}
			
		}		
		
		while(global_status==7){                             // feeding
			int i=1;
			
    while(i<2)
    {
        //¸ü¸ÄÕ¼¿Õ±ÈÎª  °Ù·ÖÖ100*2000/PWM_DUTY_MAX  PWM_DUTY_MAXÔÚfsl_pwm.hÎÄ¼þÖÐ Ä¬ÈÏÎª50000
        pwm_duty(PWM1_MODULE1_CHA_D14,5000);
        
        systick_delay_ms(3000);
			  pwm_duty(PWM1_MODULE1_CHA_D14,1250);
				systick_delay_ms(5000);
        i++;
    }
		global_status=8;
		}
		
		while(global_status==8){                             //go through the wtone road
			motor_TRdegree(-45);            ////////////////////////////////////////////
				systick_delay_ms(500);
				motor_TRdegree(-45);
				systick_delay_ms(500);
			 
			while(good_direction==0){
			dis2=ave(dis_right());
			dis1=ave(dis_front());	
				
      if(dis1<60){
				motor_STP();systick_delay_ms(1000);
				motor_TLdegree(45);          ////////////////////////////////////////////
				systick_delay_ms(500);
				motor_TLdegree(45);
				motor_GOstraight(3000);	
				motor_STP();systick_delay_ms(100);	
        good_direction=1;				
			}				
			 else if(dis2<25){
				motor_TL3(100);
				systick_delay_ms(300);
				motor_TR2(70);
				systick_delay_ms(150);
			}
			else if(dis2>25&&dis2<30){
				motor_MF(80);
				systick_delay_ms(100);
			}
			else if(dis2>30&&dis2<50){
				motor_TR3(100);
				systick_delay_ms(200);
				motor_TL2(80);
				systick_delay_ms(120);
			}
			else if(dis2>50&&dis2<150){
				motor_TR4(100);
				systick_delay_ms(240);
				motor_TL3(85);
				systick_delay_ms(100);
			}			
				
		}
			
			while(good_direction==1){                         // stop before wall and turn left   (patio2)
        dis1=ave(dis_front());
					
			if(dis1<50){
				motor_STP();systick_delay_ms(1000);
				motor_TLdegree(45);          ////////////////////////////////////////////
				systick_delay_ms(500);
				motor_TLdegree(45);
				
				motor_STP();systick_delay_ms(1000);
				
				good_direction=2;
			}
			else{
				motor_MF(85);
				systick_delay_ms(200);
				motor_STP();
				systick_delay_ms(100);
			}	
				systick_delay_ms(100);
		}
			
			while(good_direction==2){
			dis2=ave(dis_right());
			dis1=ave(dis_front());	
			dis3=ave(dis_left1());
			dis4=ave(dis_left2());
						
			if(dis2>250){                                // turn right at coner
				
				//motor_TR4(100);systick_delay_ms(1200);
				motor_TRdegree(-45);				systick_delay_ms(500);				motor_GOstraight(800);	
				motor_TRdegree(-45);				systick_delay_ms(500);				motor_GOstraight(800);	
				motor_STP();systick_delay_ms(500);
        good_direction=3;		
			}
			
			else if(dis2<25){
				motor_TL3(100);
				systick_delay_ms(300);
				motor_TR2(70);
				systick_delay_ms(150);
			}
			else if(dis2>25&&dis2<30){
				motor_MF(80);
				systick_delay_ms(100);
			}
			else if(dis2>30&&dis2<50){
				motor_TR3(100);
				systick_delay_ms(200);
				motor_TL2(80);
				systick_delay_ms(120);
			}
			else if(dis2>50&&dis2<150){
				motor_TR4(100);
				systick_delay_ms(240);
				motor_TL3(85);
				systick_delay_ms(100);
			}
		}
			while(good_direction==3){
			dis2=ave(dis_right());
			dis1=ave(dis_front());	
			dis3=ave(dis_left1());
			dis4=ave(dis_left2());
						
			if(dis2>250){                                // turn right at coner
					
				motor_STP();systick_delay_ms(500);
        good_direction=4;				
			}
			
			else if(dis2<25){
				motor_TL3(100);
				systick_delay_ms(300);
				motor_TR2(70);
				systick_delay_ms(150);
			}
			else if(dis2>25&&dis2<30){
				motor_MF(80);
				systick_delay_ms(100);
			}
			else if(dis2>30&&dis2<50){
				motor_TR3(100);
				systick_delay_ms(200);
				motor_TL2(80);
				systick_delay_ms(120);
			}
			else if(dis2>50&&dis2<150){
				motor_TR4(100);
				systick_delay_ms(240);
				motor_TL3(85);
				systick_delay_ms(100);
			}

		  while(good_direction==4){
				motor_TL4(85);
				systick_delay_ms(200);
				motor_STP();
				systick_delay_ms(1000);
				motor_GOstraight(12000);
				motor_STP();
				systick_delay_ms(100);
				global_status=9;
				good_direction=5;
		}
	}}
		while(global_status==9){
		gpio_init(C5, GPO, 1, GPIO_PIN_CONFIG);
		gpio_init(C6, GPO, 1, GPIO_PIN_CONFIG);
		gpio_init(C7, GPO, 1, GPIO_PIN_CONFIG);
		uart_init (USART_4, 9600, UART4_TX_C16, UART4_RX_C17);
		//DS1302_timeWrite(&ds1302, &ds1302_time);
    // Read time from DS1302 and store result in ds1302_time
		DS1302_timeRead(&ds1302, &ds1302_time) ;
		// Initialize the buffer that will be used to store the formatted time string. The initialized value is not important too. So just fuck it. Whatever the value is. Only the length is important
		char time_string[1000];
		// Save the printf result in time_string
sprintf(time_string, "Team-42 Supercalifragilisticexpialidocious\nTime:%4d/%02d/%02d %02d:%02d:%02d\nMember Inf.:\n2429402L-Li Zhouyixian\n2429351L-Li Yixiao\n2429399T-Tu Zhixing\n2357803X-Xu Yihao\n2429666Z-Zhou Ziang\n2429665M-Meng Zhanzhao\n2429658X-Xu Luohao\n2429647L-Liu Shangke\n2429667H-Hu Xuao\n2429663W-Wang Qianli", ds1302_time.year, ds1302_time.month, ds1302_time.date, ds1302_time.hour, ds1302_time.minute+3, ds1302_time.second);
			// Send the string to HC-12 via UART
		uart_putstr(USART_4, time_string);
	break;
   
			
		}
			break;
			}
	return 0;
				

}    

				


    



  