#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "reg52.h"
#include "delay.h"

sbit IN1=P3^1;//连接至L293DIN1口
sbit IN2=P3^2;//连接至L293DIN2口
sbit   E=P3^3;//连接至EN1口

void motor_start()//电机启动
{
	IN1=0;
	delay_ms(50);
	IN2=1;
	delay_ms(50);
	E=1;
}

void motor_stop()//电机停止
{
  IN1=0;
	IN2=0;
	E=0;
}
#endif