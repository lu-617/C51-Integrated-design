#include<STC12C5A60S2.h>
#include<key_scan.h>
#include<LCD1602.h>
#include<intrins.h>
#include<DS18B20.h>


#define ulong   unsigned    long 
#define uint	unsigned	int
#define FSCLK	11059200
#define	LED_PORT	P0	
#define RldTmr(fr) 65536 - (11059200 /12) / (fr << 1)		 


sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;
sbit LED5 = P0^4;
sbit LED6 = P0^5;
sbit LED7 = P0^6;
sbit LED8 = P0^7;


uint TPH;             
uint TPL;                      
uint TP;


void Delay_ms(uint time)
{
	uint i,j;
	for(i = 0;i < time;i ++)
		for(j = 0;j < 930;j ++);
}


void Delay(uint time)
{
	uint i;
	for(i=time;i>0;i--);
}


sbit buzz = P1^4;
 
uint code noteFreq[] = { 
	262, 293, 329, 349, 392, 440, 494,
    523, 586, 659, 698, 784, 880, 980,
    1045, 1171, 1319, 1397, 1568, 1760, 1976 ,
};
uint code tmrRld[] = { 
    RldTmr(523), RldTmr(587), RldTmr(659), RldTmr(698),
	RldTmr(784), RldTmr(880), RldTmr(988),
    RldTmr(1047), RldTmr(1175), RldTmr(1319), RldTmr(1397),
	RldTmr(1568), RldTmr(1760), RldTmr(1976),
};
uchar code musicNote[] = {   
    6,7,8,9,10,13,12,10,6,// 	6-,7-,1,2,3,6,5,3,6-,
	10,9,8,7,6,7,8,9,10,// 	3,2,1,7-,6-,7-,1,2,3,
	9,8,7,6,7,8,7,6,5,7,// 	2,1,7-,6-,7-,1,7-,6-,5-,7-,
	6,7,8,9,10,13,12,10,6,// 	6-,7-,1,2,3,6,5,3,6-,
	10,9,8,7,6,7,8,9,10,// 	3,2,1,7-,6-,7-,1,2,3,
	9,8,7,8,9,10,// 	2,1,7-,1,2,3,
	12,13,10,9,10,9,10,12,13,10,9,10,9,10,//  5,6,3,2,3,2,3,5,6,3,2,3,2,3,
	9,8,7,5,6,5,6,//  2,1,7-,5-,6-,5-,6-,
	7,8,9,10,6,10,12,//  7-,1,2,3,6-,3,5,
	12,13,10,9,10,9,10,12,13,10,9,10,13,14,//  5,6,3,2,3,2,3,5,6,3,2,3,6,7,
	14,14,13,12,10,9,10,//  1+,7,6,5,3,2,3，
	9,8,7,5,6,10,12,//  2,1,7-,5-,6-,3,5,

};
uchar code noteDuration[] = { 
	4,4,4,4,2,4,4,2,2,
	4,4,4,4,4,4,4,4,2,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,2,4,4,2,2,
	4,4,4,4,4,4,4,4,2,
	4,4,2,2,2,2,
	4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,
	4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,4,4,2,4,4,
};
bit enable = 1, tmrFlg = 0;
uchar T0RH = 0XFF, T0RL = 0X00;

void Delay(uint n);
void PlayMusic(uchar speed);
 



void first()
{
	uint f,i,ci;
	LED_PORT=0xFF;
	LCD_1602_Init(); 
	Write_1602_String("NO.1",0X80);
	Write_1602_String("breathing light",0XC0);
for(f=1;f<=3;f++)
{
	for(ci=0;ci<=300;ci++)
		{
			for(i=0;i<10;i++)
			{
			LED1 = 1;
			Delay(ci);		
			LED1 = 0;
			Delay(300-ci);			
			}
		}
	for(ci=300;ci>0;ci--)
		{
			for(i=0;i<10;i++)
			{	
			LED1 = 1;
			Delay(ci);		
			LED1 = 0;
			Delay(300-ci);	
			}			
		}
}		 
 	LED_PORT=0xFF;
}				


void second()
{
	uint e;	
	uchar temp = 0xFE,i = 0,flag = 0;
	LCD_1602_Init(); 		   
	Write_1602_String("NO.2",0X80);
	Write_1602_String("Horse Run Light",0XC0);	
    for(e=1;e<=21;e++)
	{		
		if(flag == 0)
		{
			LED_PORT = temp;
			Delay_ms(500);
			temp=_crol_(temp,1);
			i++;
			if(i == 7)flag = 1;			
		}
		else 
		{
			LED_PORT = temp;
			Delay_ms(500);
			temp=_cror_(temp,1);
			i--;
			if(i == 0)flag = 0;				
		}
	}					
}


void third()
{
 	LED_PORT=0xFF;
	LCD_1602_Init(); 
	Write_1602_String("NO.3",0X80);
	Write_1602_String("countdown",0XC0);
	Delay_ms(1000);
	LED_PORT=0xFF;
		LCD_1602_Init(); 
		Write_1602_String("countdown",0X80);
		Write_1602_String("5seconds",0XC5);
		Delay_ms(1000);
		Write_1602_String("remaining",0X80);
		Write_1602_String("4seconds",0XC5);
		Delay_ms(1000);
		Write_1602_String("remaining",0X80);
		Write_1602_String("3seconds",0XC5);
		Delay_ms(1000);
		Write_1602_String("remaining",0X80);
		Write_1602_String("2seconds",0XC5);
		Delay_ms(1000);
		Write_1602_String("remaining",0X80);
		Write_1602_String("1seconds",0XC5);
		Delay_ms(1000);
		LCD_1602_Init(); 
		Write_1602_String("time is up",0X80);
		Delay_ms(1000);
}


void fourth()
{		
	uint i=0,temp=0,e;
 	LED_PORT=0xFF;
	LCD_1602_Init();
	Write_1602_String("NO.4",0X80);
	Write_1602_String("char movings",0XC0);
	Delay_ms(1000);
	LED_PORT=0xFF;
		LCD_1602_Init(); 
		Write_1602_String("I am moving",0X80);
		Write_1602_String("left to right",0XC3);
		{
		for(e=0;e<=32;e++)
			if(temp == 0)
			{
				i++;
				Delay_ms(500);
				Write_1602_Com(FRAME_SHIFT_LEFT);			
				Write_1602_String("I am moving ",0x80+i);
				if(i == 5)temp = 1;		
			}

			else
			{
				i--;	
				Delay_ms(500);
				Write_1602_Com(FRAME_SHIFT_RIGHT);			
				Write_1602_String("I am moving ",0x80+i);
				if(i == 0)temp = 0;			
			}
		}		
}


void fifth()
{ 
	uint f,i,ci; 
	LED_PORT=0xFF;
	LCD_1602_Init(); 
	Write_1602_String("NO.5",0X80);
	Write_1602_String("twinkling light",0XC0);
	for(f=1;f<=3;f++)
		for(ci=0;ci<=300;ci++)
		{
			for(i=0;i<10;i++)
			{
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			LED4 = 0;
			LED5 = 1;
			LED6 = 0;
			LED7 = 1;
			LED8 = 0;
			Delay(ci);		
			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			LED4 = 1;
			LED5 = 0;
			LED6 = 1;
			LED7 = 0;
			LED8 = 1;
			Delay(300-ci);			
			}
		}
		for(ci=300;ci>0;ci--)
		{
			for(i=0;i<10;i++)
			{	
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			LED4 = 0;
			LED5 = 1;
			LED6 = 0;
			LED7 = 1;
			LED8 = 0;
			Delay(ci);		
			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			LED4 = 1;
			LED5 = 0;
			LED6 = 1;
			LED7 = 0;
			LED8 = 1;
			Delay(300-ci);	
			}			
		}

		LED_PORT=0xFF;	
}


void sixth()
{
	uint i,temp;
	LED_PORT=0xFF;
	LCD_1602_Init(); 
	Write_1602_String("NO.6",0X80);
	Write_1602_String("flowing lights",0XC0);
 	for(i=1;i<=2;i++)
	{
			LED_PORT = temp;
			Delay_ms(500);
			temp=0xFE;
		
			LED_PORT = temp;
			Delay_ms(500);
			temp=0xFC;
  			
			LED_PORT = temp;
			Delay_ms(500);
			temp=0xF8;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xF0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xE0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xC0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0x80;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0x00;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0x80;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xC0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xE0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xF0;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xF8;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xFC;

			LED_PORT = temp;
			Delay_ms(500);
			temp=0xFE;
	}
	LED_PORT=0xFF;			
}


void seventh()
{
	uint i;
	LCD_1602_Init(); 
	Write_1602_String("NO.7",0X80);
	Write_1602_String("music:bad apple",0XC0);
	EA = 1;
    TMOD = 0X01;
    TH0 = T0RH;
    TL0 = T0RL;
    ET0 = 1;
    TR0 = 1;
    for(i=1;i<=1;i++) 
	{
        PlayMusic(55);
      	Delay(40000u);
    }
}

 
void PlayMusic(uchar speed)
 {
    uchar i;
    uchar idx;
    uint cnt = 0;
    uint durationCnt = 0;
    uint soundCnt = 0;	
	LED_PORT=0xFF;
    for (i = 0; i < sizeof (musicNote); ) {
        while (!tmrFlg) ;
        tmrFlg = 0;
        if (cnt == 0) {
            idx = musicNote[i] - 1;
            T0RH = tmrRld[idx] >> 8;
            T0RL = tmrRld[idx];
            durationCnt = (ulong)240 * (ulong)noteFreq[idx] / ((ulong)noteDuration[i] * (ulong)speed);
            soundCnt = durationCnt - (durationCnt >> 2);
            enable = 1;
            cnt++;
			LED1=!LED1;
        }
        else {
            if (cnt == durationCnt) {
                cnt = 0;
                i++;
            }
            else {
                cnt++;
                if (cnt == soundCnt) {
                    enable = 0;
                }
            }
        }
    }
}
 
void InterruptTmr0() interrupt 1 {
    TH0 = T0RH;
    TL0 = T0RL;
    tmrFlg = 1;
    if (enable)
        buzz = ~buzz;
    else
        buzz = 1;
}
	 

void eight()
{  	
	uint e;
	LCD_1602_Init(); 				
   for (e=1;e<=2;e++)
   {
	
		Write_1602_String("NO.8    Temp:",0X80);
	    DS18B20_Reset();               
	    DS18B20_WriteByte(0xCC);        
	    DS18B20_WriteByte(0x44);     	             	
		Delay_ms(1000);				
	
	    DS18B20_Reset();               
	    DS18B20_WriteByte(0xCC);      
	    DS18B20_WriteByte(0xBE);    
	    TPL = DS18B20_ReadByte();    
	    TPH = DS18B20_ReadByte();       
	
		TP=((TPH<<8)|TPL)*0.0625;			

		Write_Num(TP,0x80+13);				
		Write_1602_String("temperature",0x80+0x40);  
		Delay_ms(1000);	 
   }	
}





void check()
{
	uchar key;
	LCD_1602_Init(); 
	Write_1602_String("NO.13",0X80);
	Write_1602_String("check keyboard",0XC0);//只有关机能关闭，键盘检查程序
	Delay_ms(1000);
	LED1=0;
    while(1)
	{

		key = Key_Scan();	 
		if(key != 0)		
		{
			LED1 = !LED1;	
		}
	}
	
		
}



void main()
{
	uchar key; 
	LCD_1602_Init(); 
	Write_1602_String("Hello,",0X80);
	Write_1602_String("World!",0XC5);
	Delay_ms(2000);
	LCD_1602_Init(); 
	Write_1602_String("welcome to C51",0X80);
	Write_1602_String("Microcontroller",0XC5);
	Delay_ms(2000);
	LCD_1602_Init(); 
	Write_1602_String("Lu yi jie",0X80);
	Write_1602_String("ID:20192333014",0XC0);
	Delay_ms(2000);
	LCD_1602_Init(); 
	Write_1602_String("press 1 to 13",0X80);
	Write_1602_String("to continue",0XC0);
	while(1)
	{

		key = Key_Scan();
		if(key == 1)
		{				
		first();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 2)
		{			
		second();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 3)
		{
		third();
		LCD_1602_Init(); 
		Write_1602_String("NO.5",0X80);
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 4)
		{
		fourth();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 5)
		{
		fifth();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 6)
		{
		sixth();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 7)
		{
		seventh();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 8)
		{
		eight();
		LCD_1602_Init(); 
		Write_1602_String("press 1 to 13",0X80);
		Write_1602_String("to continue",0XC0);
		}

		if(key == 9)
		{
		LCD_1602_Init(); 
		Write_1602_String("please press",0X80);
		Write_1602_String("1 to 8",0XC0);
		}

		if(key == 10)
		{
		LCD_1602_Init(); 
		Write_1602_String("nothing here",0X80);
		Write_1602_String("thanks",0XC0);
		}

		if(key == 11)
		{
		LCD_1602_Init(); 
		Write_1602_String("I am not good at",0X80);
		Write_1602_String("doing this QAQ",0XC0);
		}

		if(key == 12)
		{
		LCD_1602_Init(); 
		Write_1602_String("thanks for using",0X80);
		Write_1602_String("I will be better",0XC0);
		}

		if(key == 13)
		{
		check();
		}
	}
	
		
}