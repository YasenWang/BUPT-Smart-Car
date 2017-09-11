#include<reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define t 100
#define light_on 0
#define light_off 1
#define B 1
#define W 0

unsigned short int j = 0;

uchar code seg_data[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff };//0~9????,0x00????
uchar data disp_buf[7] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//?????

sbit IN1 = P1 ^ 3;//0000 0110   1111 1001   41 1011
sbit IN2 = P1 ^ 5;//1 2 right
sbit IN3 = P1 ^ 2;
sbit IN4 = P1 ^ 0;
sbit LED1 = P2 ^ 6;
sbit LED2 = P2 ^ 7;

sbit infrared1 = P3 ^ 6;//?2
sbit infrared2 = P3 ^ 5;//?1
sbit infrared3 = P3 ^ 4;//?
sbit infrared4 = P3 ^ 3;//?1
sbit infrared5 = P3 ^ 2;//?2

void forward()
{
	for (j = 0; j < 900; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;
	}
}
/*low_turning*/
void low_left()
{
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 0;
		IN4 = 0;
	}
	for (j = 0; j < 300; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}
void low_right()
{
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;
	}
	for (j = 0; j < 300; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}

/*常规转向*/
void turn_left()
{
	for (j = 0; j < 500; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 0;
		IN4 = 0;
	}
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}
void turn_right()
{
	for (j = 0; j < 500; j++)
	{
		IN1 = 0;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;
	}
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}
/*偏航修正*/
void slow_left()
{
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 0;
		IN4 = 0;
	}
	for (j = 0; j < 500; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}
void slow_right()
{
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;
	}
	for (j = 0; j < 500; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 1;
		IN4 = 0;
	}
}
/*sharp_turning*/
void sharp_left()
{
	for (j = 0; j < 1000; j++)
	{
		LED2 = light_on;
		IN1 = 0;
		IN2 = 1;
		IN3 = 0;
		IN4 = 1;
		LED2 = light_off;
	}
}
void sharp_right()
{
	for (j = 0; j < 1000; j++)
	{
		LED1 = light_on;
		IN1 = 1;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;
		LED1 = light_off;
	}
}
void turn_back()
{
	for (j = 0; j < 100; j++)
	{
		IN1 = 0;
		IN2 = 1;
		IN3 = 0;
		IN4 = 1;
	}
}
void main()
{
	P0 = 0xff;
	P2 = 0xff;
	P1 = 0xff;
	//display();
	while (1)
	{
		//LED1 = light_on;
		//LED2 = light_on;
		if (infrared3 == W & infrared1 == W & infrared2 == W & infrared4 == W & infrared5 == W)
		{
			turn_back();//全白掉头
		}
		else if (infrared3 == B & infrared1 == B & infrared2 == B & infrared4 == B & infrared5 == B)
		{
			forward();//全黑直行
		}
		/*十字路口234*/
		else if (infrared3 == B & infrared1 == W & infrared2 == B & infrared4 == B & infrared5 == W)
		{
			forward();//234黑直走
		}
		/*转向*/
		else if (infrared3 == W & infrared1 == B & infrared2 == B & infrared4 == W & infrared5 == W)
		{
			turn_left();//12黑左转
		}
		else if (infrared3 == W & infrared1 == W & infrared2 == W & infrared4 == B & infrared5 == B)
		{
			turn_right();//45黑右转
		}
		/*直角弯*/
		else if (infrared3 == B & infrared1 == B & infrared2 == B & infrared4 == W & infrared5 == W)
		{
			sharp_left();//123黑紧急左转
		}
		else if (infrared3 == B & infrared1 == W & infrared2 == W & infrared4 == B & infrared5 == B)
		{
			sharp_right();//345黑紧急右转
		}
		//high speed single light
		else if (infrared3 == W & infrared1 == B & infrared2 == W & infrared4 == W & infrared5 == W)
		{
			sharp_left();//1黑紧急左转
		}
		else if (infrared3 == W & infrared1 == W & infrared2 == W & infrared4 == W & infrared5 == B)
		{
			sharp_right();//5黑紧急右转
		}
		/*偏航微调*/
		else if (infrared3 == W & infrared1 == W & infrared2 == B & infrared4 == W & infrared5 == W)
		{
			low_left();//2黑缓慢左转
		}
		else if (infrared3 == W & infrared1 == W & infrared2 == W & infrared4 == B & infrared5 == W)
		{
			low_right();//4黑缓慢右转
		}
		else if (infrared3 == B & infrared1 == W & infrared2 == B & infrared4 == W & infrared5 == W)
		{
			slow_left();//23黑缓慢左转
		}
		else if (infrared3 == B & infrared1 == W & infrared2 == W & infrared4 == B & infrared5 == W)
		{
			slow_right();//34黑缓慢右转
		}
		//sharp circle
		else if (infrared3 == B & infrared1 == B & infrared2 == W & infrared4 == W & infrared5 == W)
		{
			sharp_left();//13黑紧急左转
		}
		else if (infrared3 == B & infrared1 == W & infrared2 == W & infrared4 == W & infrared5 == B)
		{
			sharp_right();//35黑紧急右转
		}
		/*unnamed condition*/
		else if(infrared3 == B&infrared2 == W&infrared1 == W&infrared4 == W&infrared5 == W)
		{
			forward();//3黑直走
		}
		/*锐角急转*/
		else if (infrared3 == B & infrared1 == B & infrared2 == B & infrared4 == B & infrared5 == W)
		{
			sharp_left();//1234黑紧急左转
		}
		else if (infrared3 == B & infrared1 == W & infrared2 == B & infrared4 == B & infrared5 == B)
		{
			sharp_right();//2345黑紧急右转
		}
		else forward();
	}
}
