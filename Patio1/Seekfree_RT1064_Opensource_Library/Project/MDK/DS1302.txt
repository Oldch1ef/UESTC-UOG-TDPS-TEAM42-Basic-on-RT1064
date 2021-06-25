
#include "DS1302.h"
#include "headfile"

/*
DS1302??:
	GPIOA_5 ->DS1302_RST
	GPIOA_6 ->DS1302_DAT
	GPIOA_7 ->DS1302_CLK
*/
struct TIMEData TimeData;

#define DS1302_SEC_ADDR           0x80		//?????
#define DS1302_MIN_ADDR           0x82		//?????
#define DS1302_HOUR_ADDR          0x84		//?????
#define DS1302_DAY_ADDR           0x86		//?????
#define DS1302_MONTH_ADDR         0x88		//?????
#define DS1302_WEEK_ADDR          0x8a		//??????
#define DS1302_YEAR_ADDR          0x8c		//?????
#define DS1302_CONTROL_ADDR       0x8e		//??????
#define DS1302_CHARGER_ADDR       0x90 		//??????			 
#define DS1302_CLKBURST_ADDR      0xbe
 
//??????
uint8_t time_buf[8] = {0x20,0x19,0x04,0x12,0x15,0x07,0x00,0x06};//????2019?4?12?15?07?00? ???
uint8_t readtime[15];//????
uint8_t sec_buf=0;  //???
uint8_t sec_flag=0; //????
 
//DS1302?????
void DS1302_Init() 
{
	/*1.GPIOC??*/
	RCC->APB2ENR |= 1<<2;
	/*2. ??GPIOA_5/6/7??*/
	GPIOA->CRL &= 0X000FFFFF;
	GPIOA->CRL |= 0X33300000;
	GPIOA->ODR |=1<<6;
	//printf("DS1302_Init OK!\n");
 
}
//?DS1302???????
void DS1302_WriteByte(uint8_t addr,uint8_t data) 
{
	uint8_t i;
	DS1302_RST=0; //?????? !!!?????
	DS1302_CLK=0; //??????SCLK????
	DS1302_RST=1;	//??DS1302??	
	DS1302_OutPut_Mode();
	addr=addr&0xFE;  //?????,???0??0??,?1??
	for(i=0;i<8;i++) //??????:addr
	{
		if (addr&0x01) DS1302_OUT=1;
		else DS1302_OUT=0;
		DS1302_CLK=1; //?????????
		DS1302_CLK=0;
		addr=addr>>1;
	}	
	for (i=0;i<8;i++) //????:data
	{
		if(data&0x01) DS1302_OUT=1;
		else DS1302_OUT=0;
		DS1302_CLK=1;    //?????????
		DS1302_CLK=0;
		data = data >> 1;
	}
	DS1302_CLK=1;    // ???????????? ,??????
	DS1302_RST=0;	//??DS1302??
}
 
//?DS1302???????
uint8_t DS1302_ReadByte(uint8_t addr) 
{
	u8 i,temp;	
	DS1302_RST=0; //?????
	DS1302_CLK=0; //??SCLK????,??????SCLK???
	DS1302_RST=1; //??DS1302??
	DS1302_OutPut_Mode();
	//??????:addr
	addr=addr|0x01; //?????,???0??0??,?1??
	for(i=0;i<8;i++) 
	{
		if (addr&0x01) DS1302_OUT=1;
		else DS1302_OUT=0;
		DS1302_CLK=1; //???
		DS1302_CLK=0;
		addr = addr >> 1;
	}	
	//?DS1302????:temp
	DS1302_InPut_Mode();
	for(i=0;i<8;i++)
	{
		temp=temp>>1;
		if (DS1302_IN) temp|=0x80;
		else temp&=0x7F;
		DS1302_CLK=1;
		DS1302_CLK=0;
	}	
	DS1302_CLK=1;  //???????????
	DS1302_RST=0;	//??DS1302??
	return temp;
}
//?DS1302??????,????????
void DS1302_WriteTime() 
{
	DS1302_WriteByte(DS1302_CONTROL_ADDR,0x00);       //????? 
	DS1302_WriteByte(DS1302_SEC_ADDR,0x80);           //???? 
	//DS1302_WriteByte(DS1302_CHARGER_ADDR,0xa9);     //???? 
	DS1302_WriteByte(DS1302_YEAR_ADDR,time_buf[1]);   //? 
	DS1302_WriteByte(DS1302_MONTH_ADDR,time_buf[2]);  //? 
	DS1302_WriteByte(DS1302_DAY_ADDR,time_buf[3]);    //? 
	DS1302_WriteByte(DS1302_HOUR_ADDR,time_buf[4]);   //? 
	DS1302_WriteByte(DS1302_MIN_ADDR,time_buf[5]);    //?
	DS1302_WriteByte(DS1302_SEC_ADDR,time_buf[6]);    //?
	DS1302_WriteByte(DS1302_WEEK_ADDR,time_buf[7]);	  //? 
	DS1302_WriteByte(DS1302_CHARGER_ADDR,0xA5);//?????? ??2K??????
	DS1302_WriteByte(DS1302_CONTROL_ADDR,0x80);//?????     
}

void DS1302_ReadTime(void)  
{
	time_buf[1]=DS1302_ReadByte(DS1302_YEAR_ADDR);         
	time_buf[2]=DS1302_ReadByte(DS1302_MONTH_ADDR);        
	time_buf[3]=DS1302_ReadByte(DS1302_DAY_ADDR);         
	time_buf[4]=DS1302_ReadByte(DS1302_HOUR_ADDR);         
	time_buf[5]=DS1302_ReadByte(DS1302_MIN_ADDR);    
	time_buf[6]=(DS1302_ReadByte(DS1302_SEC_ADDR))&0x7f;   
	time_buf[7]=DS1302_ReadByte(DS1302_WEEK_ADDR);          	
}
 
//???
void DS1302_GetTime()
{ 
    DS1302_ReadTime(); //????
    TimeData.year=(time_buf[0]>>4)*1000+(time_buf[0]&0x0F)*100+(time_buf[1]>>4)*10+(time_buf[1]&0x0F); //????
    TimeData.month=(time_buf[2]>>4)*10+(time_buf[2]&0x0F);  //????
    TimeData.day=(time_buf[3]>>4)*10+(time_buf[3]&0x0F);    //????
    TimeData.hour=(time_buf[4]>>4)*10+(time_buf[4]&0x0F);   //????
    TimeData.minute=(time_buf[5]>>4)*10+(time_buf[5]&0x0F); //????
    TimeData.second=(time_buf[6]>>4)*10+(time_buf[6]&0x0F); //????
    TimeData.week=(time_buf[7]&0x0F);                       //????
  //printf("??:%d-%d-%d %d:%d:%d %d \n",TimeData.year,TimeData.month,TimeData.day,TimeData.hour,TimeData.minute,TimeData.second,TimeData.week);																												
}
