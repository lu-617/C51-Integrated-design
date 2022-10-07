/*********************************************************************************************************
** 文件功能 ：键盘扫描头文件
** 工程作者 ：Blue Sky Teams——ZZL
** 工程版本 ：V1.0
*********************************************************************************************************/

#define KEY_PORT	P3			//定义键盘接口

unsigned char scan,read,key_num;//参考电平；读KEY_PORT口电平；检测到得键盘位数

void Delay_ms(unsigned int time);		//声明延时函数


unsigned char Key_Scan() //键盘扫描程序
{
	key_num=0;
	KEY_PORT=0xfe;//从下面数起第一行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(70);//延迟一段时间，消斗，
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0) // 若真的有键按下，再进行判断哪个按键按下
				{
					switch(scan)
						{
							case 0x70:key_num=16;break;
							case 0xb0:key_num=15;break;
							case 0xd0:key_num=14;break;
							case 0xe0:key_num=13;break;						
						}
					while(scan!=0xf0)//松手检测
					{
						while(scan != 0xf0)//松手消抖检测
						{
							Delay_ms(70);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(70);
						read=KEY_PORT;
						scan=read&0xf0;
					}
				}

		}

	KEY_PORT=0xfd;//从下面数起第二行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(70);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
			{
				switch(scan)
				{
					case 0x70:key_num=12;break;
					case 0xb0:key_num=11;break;
					case 0xd0:key_num=10;break;
					case 0xe0:key_num=9;break;						
				}
					while(scan!=0xf0)
					{
						while(scan != 0xf0)
						{
							Delay_ms(70);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(70);
						read=KEY_PORT;
						scan=read&0xf0;
					}
		    }

		}


    KEY_PORT=0xfb;//从下面数起第三行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(70);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
				{
					switch(scan)
						{
							case 0x70:key_num=8;break;
							case 0xb0:key_num=7;break;
							case 0xd0:key_num=6;break;
							case 0xe0:key_num=5;break;						
						}
						while(scan!=0xf0)
						{
							while(scan != 0xf0)
							{
								Delay_ms(70);
								read=KEY_PORT;
								scan=read&0xf0;				
							}
							Delay_ms(70);
							read=KEY_PORT;
							scan=read&0xf0;
						}
				}

		}


    KEY_PORT=0xf7;//从下面数起第四行
	read=KEY_PORT;
	scan=0xf0;
	scan=scan&read;
	if(scan!=0xf0)
		{
			Delay_ms(70);
			read=KEY_PORT;
			scan=read&0xf0;	
			if(scan!=0xf0)
				{
					switch(scan)
						{
							case 0x70:key_num=4;break;
							case 0xb0:key_num=3;break;
							case 0xd0:key_num=2;break;
							case 0xe0:key_num=1;break;						
						}
					while(scan!=0xf0)
					{
						while(scan != 0xf0)
						{
							Delay_ms(70);
							read=KEY_PORT;
							scan=read&0xf0;				
						}
						Delay_ms(70);
						read=KEY_PORT;
						scan=read&0xf0;
					}
				}

		}
	return(key_num);
}
