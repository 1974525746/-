#ifndef __DELAY_H__
#define __DELAY_H__

#include "intrins.h"

#define uchar unsigned  char
#define uint unsigned  int 


void delay_ms(int t)//延时ms
{
	int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<110;j++);//延时1ms
	}
}

void delay_us(uchar t)//延时us
{
	while(--t);
}

#endif